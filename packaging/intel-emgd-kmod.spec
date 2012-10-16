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
%define kernel_number_str "%(/bin/rpm -q kernel-adaptation-intel-automotive --queryformat \"%{VERSION}-%{RELEASE}\"|grep -iv 'installed')"
%define kernel_number %(echo %{kernel_number_str})
%define kernel_version %{kernel_number}-adaptation-intel-automotive
%define modpath /lib/modules/%{kernel_version}/kernel/drivers/gpu/drm/emgd

Name: intel-emgd-kmod
Summary: Intel EMGD kernel module
Version: 3104
Release: 1%{?dist}
License: GPL v2
Vendor: Intel
Group: System Environment/Kernel
Source0: %{name}-%{version}.tar.gz
BuildRequires: kernel-adaptation-intel-automotive-devel
BuildRequires: kmod
Requires: pciutils
Requires: kmod
Requires(post): /bin/ln
%if %{kernel_number_str} != ""
Requires: kernel-adaptation-intel-automotive = %{kernel_number}
%else
Requires: kernel-adaptation-intel-automotive
%endif

%description
Intel EMGD kernel module for kernel

%prep
%setup -q

%build
make -C drivers %{?_smp_mflags}

%install
mkdir -p $RPM_BUILD_ROOT%{_libdir}/systemd/system/basic.target.wants/
mkdir -p $RPM_BUILD_ROOT%{_libexecdir}
install -m 755 -d $RPM_BUILD_ROOT%{modpath}
install -m 744 drivers/emgd.ko $RPM_BUILD_ROOT%{modpath}
install -m 755 -D service/%{name}.service $RPM_BUILD_ROOT%{_libdir}/systemd/system/
install -m 755 -D service/%{name}.init $RPM_BUILD_ROOT%{_libexecdir}

ln -sf ../%{name}.service $RPM_BUILD_ROOT/%{_libdir}/systemd/system/basic.target.wants/%{name}.service

%clean  
rm -Rf $RPM_BUILD_ROOT

%post
## create the dependency of kernel modules
/sbin/depmod -av %{kernel_version} >/dev/null 2>&1 

if [ -x /bin/systemctl ]; then
    /bin/systemctl daemon-reload >/dev/null 2>&1 || :
    /bin/systemctl start %{name}.service > /dev/null 2>&1 || :
fi

%postun
/sbin/depmod -av %{kernel_version} >/dev/null 2>&1 
if [ -x /bin/systemctl ]; then
    systemctl daemon-reload >/dev/null 2>&1 || :
fi

%preun
if [ -x /bin/systemctl ]; then
    sytemctl stop %{name}.service >/dev/null 2>&1 || :
fi

%files
%defattr(-,root,root,-)
%{modpath}/emgd.ko
%{_libdir}/systemd/system/%{name}.service
%{_libdir}/systemd/system/basic.target.wants/%{name}.service
%{_libexecdir}/%{name}.init
