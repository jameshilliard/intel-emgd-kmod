/*
 *-----------------------------------------------------------------------------
 * Filename: emgd_shared.h
 * $Revision: 1.14.102.1 $
 *-----------------------------------------------------------------------------
 * Copyright (c) 2002-2010, Intel Corporation.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 *
 *-----------------------------------------------------------------------------
 * Description:
 *  This include file contains information that is shared between the various
 *  EMGD driver components.
 *-----------------------------------------------------------------------------
 */

#ifndef _EMGD_SHARED_H
#define _EMGD_SHARED_H

/*
 * Module name is the name of the drm kernel module. This is used by
 * user space components to open a connection to the module. A typical
 * call would look like  -- drmOpen(EMGD_MODULE_NAME, NULL);
 */
#define EMGD_MODULE_NAME "emgd"

#define EMGD_DRIVER_NAME "emgd"

/*
 * EMGD-specific numbering of the PVR DRM ioctls.  The EMGD DRM module is in
 * charge, and includes the PVR DRM code.  As such, the PVR ioctls are included
 * in with the EMGD ioctls ("emgd_drm.h"), and must be kept in sync.  Both sets
 * of these ioctls are mapped to the device specific range between 0x40 and
 * 0x79.
 *
 * Client driver must use these values!
 */
#define DRM_PVR_RESERVED1	0x12
#define DRM_PVR_RESERVED2	0x13
#define DRM_PVR_RESERVED3	0x14
#define DRM_PVR_RESERVED4	0x15
#define DRM_PVR_RESERVED5	0x16
#define DRM_PVR_RESERVED6	0x1E


/*!
 * @name Surface Alignment Flags
 * @anchor surface_info_flags
 *
 * Surface Alignment Flags are passed to the _igd_dispatch::gmm_alloc_surface()
 * function as an indicator for how the surface will be used.
 *
 * - IGD_SURFACE_RENDER The surface may be used as a rendering target,
 *     this must be set for all color buffers.
 * - IGD_SURFACE_TEXTURE The surface may be used as a texture input.
 * - IGD_SURFACE_CURSOR Surface may be used as a cursor
 * - IGD_SURFACE_OVERLAY Surface may be used with the overlay
 * - IGD_SURFACE_DISPLAY This surface is suitable for use with the display
 *   engine. This flag must be set for any render target that may later
 *   be flipped to the front buffer.
 * - IGD_SURFACE_DEPTH The surface may be used as a depth (Z) buffer.
 *
 * - IGD_SURFACE_YMAJOR If the surface is tiled, it is tiled with the
 *     walk in the YMajor direction. This flag is output only unless the
 *     allocation type is Fixed TF.
 * - IGD_SURFACE_XMAJOR If the surface is tiled, it is tiled with the
 *     walk in the YMajor direction. This flag is output only unless the
 *     allocation type is Fixed TF.
 * - IGD_SURFACE_TILED Surface is tiled. This flag is output only unless
 *     the allocation type is Fixed TF.
 * - IGD_SURFACE_FENCED Surface is fenced. This flaf is output only unless
 *     the allocation type is Fixed TF.
 *
 * Additionally all FB flags can be populated
 * See: @ref fb_info_flags
 *
 * @{
 */
#define IGD_SURFACE_RENDER    0x00000001
#define IGD_SURFACE_TEXTURE   0x00000002
#define IGD_SURFACE_CURSOR    0x00000004
#define IGD_SURFACE_OVERLAY   0x00000008
#define IGD_SURFACE_DISPLAY   0x00000010
#define IGD_SURFACE_DEPTH     0x00000020
#define IGD_SURFACE_VIDEO     0x00000040
#define IGD_SURFACE_VIDEO_ENCODE     0x00000080

#define IGD_SURFACE_WALK_MASK 0x00001000
#define IGD_SURFACE_YMAJOR    0x00001000
#define IGD_SURFACE_XMAJOR    0x00000000
#define IGD_SURFACE_TILED     0x00002000
#define IGD_SURFACE_FENCED    0x00004000
#define IGD_SURFACE_SYS_MEM   0x00008000
#define IGD_SURFACE_PHYS_PTR  0x00010000
#define IGD_SURFACE_DRM_OWN   0x00020000
#define IGD_SURFACE_X_OWN     0x00040000

#define IGD_DONT_REINIT_PVR   0x00000001

/*
 * The following typedefs support the ability of non-HAL software to have a
 * function called when a VBlank interrupt occurs.
 */

/**
 * A pointer to a non-HAL-provided function that processes a VBlank interrupt.
 */
typedef int (*emgd_process_vblank_interrupt_t)(void *priv);

/**
 * This structure allows the HAL to track a non-HAL callback (and its
 *  parameter) to call when a VBlank interrupt occurs for a given port.  An
 *  opaque pointer to this structure serves as a unique identifier for the
 *  callback/port combination.
 */
typedef struct _emgd_vblank_callback {
	/** Non-HAL callback function to process a VBlank interrupt. */
	emgd_process_vblank_interrupt_t callback;
	/** An opaque pointer to a non-HAL data structure (passed to callback). */
	void *priv;
	/** Which HAL port number is associated with this interrupt callback. */
	unsigned long port_number;
} emgd_vblank_callback_t;

/**
 * An opaque pointer to a emgd_vblank_callback_t.  This pointer serves as a
 * unique identifier for the callback/port combination.
 */
typedef void *emgd_vblank_callback_h;

/**
 * A special value of a emgd_vblank_callback_h, meaning ALL devices/displays.
 */
#define ALL_PORT_CALLBACKS	((void *) 1001)

#endif
