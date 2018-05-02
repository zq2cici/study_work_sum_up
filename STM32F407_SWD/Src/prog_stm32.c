/**
  ******************************************************************************
  * @file           : prog_stm32.c
  * @brief          : 
  *                   This file programs stm32 use fatfs .
  ******************************************************************************
  */
/* Includes ------------------------------------------------------------------*/
//#include "main.h"
#include "stm32f4xx_hal.h"
#include "fatfs.h"
#include "usb_device.h"

/* USER CODE BEGIN Includes */
#include "sfud.h"
#include "command.h"
#include "target_internal.h"
#include "cortexm.h"
/* USER CODE END Includes */

uint8_t prog_stm32_use_fatfs(uint32_t onceProgSize)
{
	
	FATFS *fs = &USERFatFS;
	FRESULT res;
	DWORD fre_clust;	
	FIL fwfile;
	FILINFO fwfileinfo;
	DIR dir;
	char fwfilepath[16];
	UINT fwReadByte;
	
	uint8_t returnvalue = 0;
	
	res = f_mount(fs, USERPath, 1);
	if (res != FR_OK)
	{
		printf("FAILED: %d\n",res);
	}
	else
		printf("MOUNT OK\n");

	res = f_getfree(USERPath,&fre_clust,&fs);         /* Get Number of Free Clusters */
	if (res == FR_OK) 
	{
	                                             /* Print free space in unit of MB (assuming 512 bytes/sector) */
	    printf("%.1f KB Total Drive Space.\n"
	           "%.1f KB Available Space.\n",
	           ((fs->n_fatent-2)*fs->csize)/2.0,(fre_clust*fs->csize)/2.0);
	}
	else
	{
		printf("get disk info error\n");
		printf("error code: %d\n",res);
	}

	res = f_opendir(&dir, "/");                       /* Open the directory */
	if (res == FR_OK) {
		for (;;) {
				res = f_readdir(&dir, &fwfileinfo);                   /* Read a directory item */
				if (res != FR_OK || fwfileinfo.fname[0] == 0) {
					printf(".BIN File Not Found\n");
					break;  /* Break on error or end of dir */
				}
				if (fwfileinfo.fattrib & AM_DIR) {                    /* It is a directory */
					
				} else {                                       /* It is a file. */
						printf("%s%s  %lu Bytes\n", USERPath, fwfileinfo.fname, fwfileinfo.fsize); 
						if(strstr(fwfileinfo.fname, ".BIN") != NULL) /* Find .HEX File */
							break;
				}
		}
		res = f_open(&fwfile, fwfileinfo.fname, FA_READ);

	} else {
		printf("open path ERROR\n");
	}
	
	printf("Start program target device.\n");
		
	cmd_swdp_scan();
	
	if(fwfileinfo.fname[0] != 0)
	{
		if(target_list != NULL)
		{
			cortexm_halt_request(target_list);
			cortexm_halt_on_reset_request(target_list);
			cortexm_reset(target_list);
			
			f_lseek(&fwfile, 0);
			uint8_t *fwbuff = malloc(onceProgSize);
			uint8_t *fwVerifyBuff = malloc(onceProgSize);
			uint8_t chkres;
			
				
//			target_flash_erase(target_list,0x08000000, (fwfileinfo.fsize + 0x7FF) & ~0x7FF);
			target_flash_erase(target_list,0x08000000, 0x4000);
		
	
			uint32_t targetWriteOffset = 0;
			for(;;)
			{
				f_read(&fwfile, fwbuff, onceProgSize, &fwReadByte);
				
				if(fwReadByte == 0) 
					break;
				if((fwReadByte & 0x03) !=0)
				{
					uint32_t AlignedByte = ((fwReadByte + 0x03) & ~0x03);
					for(;fwReadByte < AlignedByte;fwReadByte++)
						fwbuff[fwReadByte] = 0xFF;
				}
				target_flash_write(target_list,0x08000000 + targetWriteOffset, (const void *)fwbuff, fwReadByte);
				
				target_mem_read(target_list, (void *)fwVerifyBuff, 0x08000000 + targetWriteOffset, fwReadByte);
				chkres = strncmp(fwbuff, fwVerifyBuff, fwReadByte); 
				if(chkres != 0)
					break;
				targetWriteOffset += fwReadByte;
			}
			free(fwbuff);
			free(fwVerifyBuff);
			
			cortexm_halt_on_reset_clear(target_list);
			cortexm_reset(target_list);
			if(chkres == 0)
			{
				printf("Program target device Complete!\n");
				returnvalue = 0;
			} else {
				printf("Traget Device Verify ERROR.\n");
				returnvalue = 1;
				}
		} else {
		printf("Connect to target Fail.\n");
		returnvalue = 2;	
		}
	}	else {
		printf("Can't find bin file.\n");
		returnvalue = 3;	
	}
	f_close(&fwfile);
	f_closedir(&dir);
	return returnvalue;
}

uint8_t gen_bin_file(void)
{
	FATFS *fs = &USERFatFS;
	FRESULT res;
	DWORD fre_clust;	
	FIL fwfile;
	FIL fwbinfile;
	FILINFO fwfileinfo;
	DIR dir;
	char fwfilepath[16];
	UINT fwReadByte;
	

	res = f_mount(fs, USERPath, 1);

	res = f_opendir(&dir, "/");                       /* Open the directory */
	for (;;) {
		res = f_readdir(&dir, &fwfileinfo);                   /* Read a directory item */
		if (res != FR_OK || fwfileinfo.fname[0] == 0) {
			printf(".HEX File Not Found\n");
			break;  /* Break on error or end of dir */
		}
		if (fwfileinfo.fattrib & AM_DIR) {                    /* It is a directory */
			
		} else {                                       /* It is a file. */
				printf("%s%s  %lu Bytes\n", USERPath, fwfileinfo.fname, fwfileinfo.fsize); 
				if(strstr(fwfileinfo.fname, ".HEX") != NULL) /* Find .HEX File */
					break;
		}
	}
	if(fwfileinfo.fname[0] != 0)
		{
		f_open(&fwfile, fwfileinfo.fname, FA_READ);
		f_open(&fwbinfile, "TAR.BIN", FA_CREATE_ALWAYS | FA_WRITE);
		
		char buf[64];
		char fir[4]="   \n";
		char len, flag;
		
		while(f_gets(buf,64,&fwfile) != NULL)
		{
			len = strlen(buf);
			if (len < 21)
			{
				continue;
			}
			buf[len-1] = '\0';	
			for (int i = 9; i < len-3; i+=2)
			{
				fir[0] = buf[i];
				fir[1] = buf[i+1];
				
				sscanf(fir,"%x",&flag);
				
				unsigned int writebyte;
				f_write (&fwbinfile,	(const void *)&flag,	1, &writebyte);
				
				//f_putc( (const char)flag, &fwbinfile); //use f_write inside of f_putc to avoid LF->CRLF conv.
				

			}
			//f_printf(&fwbinfile, "%016b", 0x550F);       /* "0101010100001111" */
			
			printf("%s %d \n",buf,len - 1);
		}
		
		f_close(&fwfile);
		f_close(&fwbinfile);
	}
	f_closedir(&dir);
	
}
