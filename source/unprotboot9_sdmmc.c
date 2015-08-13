#include <stdlib.h>
#include <stdint.h>
#include <string.h>

#include <3ds.h>

#include "unprotboot9_sdmmc.h"

s32 unprotboot9_sdmmc_initialize()
{
	void (*funcptr_cleardtcm)() = (void*)0xffff01b0;
	void (*funcptr_boot9init)() = (void*)0xffff1ff9;
	s32 (*funcptr_mmcinit)() = (void*)0xffff56c9;

	*((u16*)0x10000020) |= 0x200;//If not set, the hardware will not detect any inserted card on the sdbus.
	*((u16*)0x10000020) &= ~0x1;//If set while bitmask 0x200 is set, a sdbus command timeout error will occur during sdbus init.

	funcptr_cleardtcm();
	*((u32*)(0xfff0009c+0x1c)) = 1;//Initialize the sdmmc busid.

	funcptr_boot9init();//General boot9 init function.

	return funcptr_mmcinit();
}

s32 unprotboot9_sdmmc_initdevice(unprotboot9_sdmmc_deviceid deviceid)
{
	s32 (*funcptr)(u32) = (void*)0xffff5775;
	return funcptr(deviceid);
}

s32 unprotboot9_sdmmc_selectdevice(unprotboot9_sdmmc_deviceid deviceid)
{
	s32 (*funcptr)(u32) = (void*)0xffff5c11;
	return funcptr(deviceid);
}

s32 unprotboot9_sdmmc_readrawsectors(u32 sector, u32 numsectors, u32 *buf)
{
	u32 original_deviceid;
	s32 ret;
	s32 (*funcptr)(u32, u32, u32*) = (void*)0xffff55f9;

	original_deviceid = *((u32*)(0xfff0009c+0x20));

	*((u32*)(0xfff0009c+0x20)) = 0x201;//The boot9 sector reading code calls the deviceselect code with deviceid=nand. Overwrite the current_deviceid value in memory with the nand value, so that the deviceselect function does nothing there.

	ret = funcptr(sector, numsectors, buf);

	*((u32*)(0xfff0009c+0x20)) = original_deviceid;

	return ret;
}

