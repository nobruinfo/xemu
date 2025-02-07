/* A work-in-progess MEGA65 (Commodore 65 clone origins) emulator
   Part of the Xemu project, please visit: https://github.com/lgblgblgb/xemu
   Copyright (C)2016-2022 LGB (Gábor Lénárt) <lgblgblgb@gmail.com>

This program is free software; you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation; either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program; if not, write to the Free Software
Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA */

#ifndef XEMU_MEGA65_SDCARD_H_INCLUDED
#define XEMU_MEGA65_SDCARD_H_INCLUDED

#define SD_ST_EXT_BUS	0x80
#define SD_ST_ERROR	0x40
#define SD_ST_FSM_ERROR	0x20
// 0x10 was the SDHC bit, but now MEGA65 does not support non-SDHC cards!
#define SD_ST_MAPPED	0x08
#define SD_ST_RESET	0x04
#define SD_ST_BUSY1	0x02
#define SD_ST_BUSY0	0x01

extern int    sdcard_init           ( const char *fn, const int virtsd_flag, const int default_d81_is_from_sd_in );
extern Uint32 sdcard_get_size       ( void );
extern void   sdcard_write_register ( const int reg, const Uint8 data );
extern Uint8  sdcard_read_register  ( const int reg  );

extern int    sdcard_read_block     ( const Uint32 block, Uint8 *buffer );
extern int    sdcard_write_block    ( const Uint32 block, Uint8 *buffer );

extern int    sdcard_force_external_mount ( const int unit, const char *filename, const char *cry );
extern int    sdcard_force_external_mount_with_image_creation ( const int unit, const char *filename, const int do_overwrite, const char *cry );
extern int    sdcard_unmount ( const int unit );
extern int    sdcard_default_d81_mount ( const int unit );
extern const char *sdcard_get_mount_info ( const int unit, int *is_internal );

extern void   sdcard_notify_system_start_begin ( void );
extern void   sdcard_notify_system_start_end   ( void );

// disk buffer for SD (can be mapped to I/O space too), F011, and some "3.5K scratch space"
extern Uint8  disk_buffers[0x1000];
extern Uint8  *disk_buffer_cpu_view;
extern Uint8  *disk_buffer_io_mapped;
extern Uint8  sd_status;

extern const char xemu_external_d81_signature[];

static inline int has_block_nonzero_byte ( const Uint8 *p )
{
	for (register unsigned int a = 0; a < 512; a++)
		if (p[a])
			return 1;
	return 0;
}

#ifdef XEMU_SNAPSHOT_SUPPORT
#include "xemu/emutools_snapshot.h"
extern int sdcard_snapshot_load_state ( const struct xemu_snapshot_definition_st *def , struct xemu_snapshot_block_st *block );
extern int sdcard_snapshot_save_state ( const struct xemu_snapshot_definition_st *def );
#endif

#endif
