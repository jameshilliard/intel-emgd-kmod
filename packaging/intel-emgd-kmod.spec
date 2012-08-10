#----------------------------------------------------------------------------
# Copyright (c) 2002-2010, Intel Corporation.
#
# Permission is hereby granted, free of charge, to any person obtaining a copy
# of this software and associated documentation files (the "Software"), to deal
# in the Software without restriction, including without limitation the rights
# to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
# copies of the Software, and to permit persons to whom the Software is
# furnished to do so, subject to the following conditions:
#
# The above copyright notice and this permission notice shall be included in
# all copies or substantial portions of the Software.
#
# THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
# IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
# FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
# AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
# LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
# OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
# THE SOFTWARE.
#----------------------------------------------------------------------------

%define debug_package %{nil}
%define modpath %(ls -d /lib/modules/*/kernel)/drivers/gpu/drm/emgd

Name: intel-emgd-kmod
Summary: Intel EMGD kernel module
Version: 2667
Release: 1%{?dist}
License: GPL v2
Vendor: Intel
Group: System Environment/Kernel
BuildRoot: %{_tmppath}/%{name}-%{version}
Source0: %{name}-%{version}.tar.gz
Source1: intel-emgd-kmod.service
Source2: intel-emgd-kmod.init
BuildRequires: kernel-adaptation-intel-automotive-devel, kmod


%description
Intel EMGD kernel module for kernel

%prep
%setup -q

%build
make

%install

mkdir -p $RPM_BUILD_ROOT/usr/lib/systemd/system/
mkdir -p $RPM_BUILD_ROOT/usr/libexec/
install -m 755 -d $RPM_BUILD_ROOT%{modpath}
install -m 744 emgd.ko $RPM_BUILD_ROOT%{modpath}
install -m 755 -D %{SOURCE1} $RPM_BUILD_ROOT/usr/lib/systemd/system/
install -m 755 -D %{SOURCE2} $RPM_BUILD_ROOT/usr/libexec/

%clean  
rm -Rf $RPM_BUILD_ROOT

%post 
## create the dependency of kernel modules
/sbin/depmod -a >/dev/null 2>&1 

mkdir -p /usr/lib/systemd/system/basic.target.wants/
pushd /usr/lib/systemd/system/basic.target.wants/
ln -sf ../intel-emgd-kmod.service intel-emgd-kmod.service
popd

if [ -x /bin/systemctl ]; then
    /bin/systemctl daemon-reload >/dev/null 2>&1 || :
    /bin/systemctl start intel-emgd-kmod.service > /dev/null 2>&1 || :
fi

%postun
/sbin/depmod -a >/dev/null 2>&1 
rm -f /usr/lib/systemd/system/basic.target.wants/intel-emgd-kmod.service
if [ -x /bin/systemctl ]; then
    systemctl daemon-reload >/dev/null 2>&1 || :
fi

%preun
if [ -x /bin/systemctl ]; then
    sytemctl stop intel-emgd-kmod.service >/dev/null 2>&1 || :
fi

%files 
%defattr(-,root,root,-)
%{modpath}/emgd.ko
%{_libdir}/systemd/system/intel-emgd-kmod.service
/usr/libexec/intel-emgd-kmod.init
