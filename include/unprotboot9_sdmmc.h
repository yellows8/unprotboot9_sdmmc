#pragma once

//These return 0 for success, non-zero for error.

//Using this requires that the DTCM at 0xfff00000 is accessible. You can either disable MPU, or setup a MPU region for it.

typedef enum {
	unprotboot9_sdmmc_deviceid_sd = 0x200,
	unprotboot9_sdmmc_deviceid_nand = 0x201
} unprotboot9_sdmmc_deviceid;

s32 unprotboot9_sdmmc_initialize();//This must be used first.
s32 unprotboot9_sdmmc_initdevice(unprotboot9_sdmmc_deviceid deviceid);//This must be used before doing anything with the device.
s32 unprotboot9_sdmmc_selectdevice(unprotboot9_sdmmc_deviceid deviceid);//Only use this if the device was already initialized, and if the device isn't already selected(the latter is checked for by the boot9 code anyway).

s32 unprotboot9_sdmmc_readrawsectors(u32 sector, u32 numsectors, u32 *buf);//Only use this after the above initialization is done. This reads raw sectors from the currently selected device.

