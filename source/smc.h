
/*
* Apple System Management Control (SMC) Tool
* Copyright (C) 2006 devnull
* Portions Copyright (C) 2013 Michael Wilber
*
* This program is free software; you can redistribute it and/or
* modify it under the terms of the GNU General Public License
* as published by the Free Software Foundation; either version 2
* of the License, or (at your option) any later version.
* This program is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
* GNU General Public License for more details.
* You should have received a copy of the GNU General Public License
* along with this program; if not, write to the Free Software
* Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
*/

#ifndef smc_h
#define smc_h

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <IOKit/IOKitLib.h>
#include <libkern/OSAtomic.h>

#define SMC_CMD_READ_KEYINFO  9
#define KERNEL_INDEX_SMC      2
#define SMC_CMD_READ_BYTES    5

#define SMC_CMD_WRITE_BYTES   6

typedef char              UInt32Char_t[5];
typedef unsigned char     SMCBytes_t[32];

typedef struct {
	UInt32Char_t            key;
	UInt32                  dataSize;
	UInt32Char_t            dataType;
	SMCBytes_t              bytes;
} SMCVal_t;

typedef struct {
	char                  major;
	char                  minor;
	char                  build;
	char                  reserved[1];
	UInt16                release;
} SMCKeyData_vers_t;

typedef struct {
	UInt16                version;
	UInt16                length;
	UInt32                cpuPLimit;
	UInt32                gpuPLimit;
	UInt32                memPLimit;
} SMCKeyData_pLimitData_t;

typedef struct {
	UInt32                dataSize;
	UInt32                dataType;
	char                  dataAttributes;
} SMCKeyData_keyInfo_t;

typedef struct {
	UInt32                  key;
	SMCKeyData_vers_t       vers;
	SMCKeyData_pLimitData_t pLimitData;
	SMCKeyData_keyInfo_t    keyInfo;
	char                    result;
	char                    status;
	char                    data8;
	UInt32                  data32;
	SMCBytes_t              bytes;
} SMCKeyData_t;

float getSmcValue(char *key);
float *getSmcValues(char *keys[], size_t n);

void allFans(void);

#endif /* smc_h */