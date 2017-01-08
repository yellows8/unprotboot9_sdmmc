.arm
.text

.global unprotboot9_sdmmc_initialize_asm

unprotboot9_sdmmc_initialize_asm:
@ Setup the DTCM region register.
ldr r0, =0xfff0000a
mcr 15, 0, r0, cr9, cr1, 0

@ Enable DTCM.
mrc 15, 0, r0, cr1, cr0, 0 @
orr r0, r0, #0x10000
mcr 15, 0, r0, cr1, cr0, 0
bx lr
.pool

