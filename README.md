This is a library for using the mmc code in the 3DS arm9-bootrom. This only uses the code in the unprotected arm9-bootrom. Boot9 only supports sector reading, not writing. Also note that boot9 reads each sector with command 18 not 25: each sector is read seperately with a dedicated command. Here the data is read from FIFO to the output buffer via CPU mem-copy. No crypto is used with this.  

SD(HC) and NAND are all supported by this arm9-bootrom sdmmc code.  

