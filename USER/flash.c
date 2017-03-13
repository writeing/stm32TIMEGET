#include "flash.h"
uint32_t StartAddress = 0x08037000;
uint32_t countAddress = 0x08036000;
volatile FLASH_Status FLASHStatus = FLASH_COMPLETE;
int count = 0;
void readFlashInit()
{
		uint32_t *p;		
		p = (uint32_t*)(countAddress);
		count = *p;
}
void printTime(int mirc,struct tm time)
{
	char buff[50];
	strftime(buff,sizeof(buff),"%Y-%m-%d %H:%M:%S",&time);					
	printf("%s.%06.2f\r\n",buff,((float)mirc)/100);
}
void Readflash()
{
//	uint32_t data;
	uint32_t *p;
	uint32_t ReadAddress = 0x08037000;
	struct tm time;	
	int mirc = 0;	
	int j=0;
	for(int i=0; i< 32 ;i++)
	{						
		p = (uint32_t*)(ReadAddress+j*4);
		time.tm_year = *p;
		j++;
		p = (uint32_t*)(ReadAddress+j*4);
		time.tm_mon = *p;
		j++;
		p = (uint32_t*)(ReadAddress+j*4);
		time.tm_mday = *p;
		j++;
		p = (uint32_t*)(ReadAddress+j*4);
		time.tm_hour = *p;
		j++;
		p = (uint32_t*)(ReadAddress+j*4);
		time.tm_min = *p;
		j++;
		p = (uint32_t*)(ReadAddress+j*4);
		time.tm_sec = *p;
		j++;
		p = (uint32_t*)(ReadAddress+j*4);
		mirc = *p;		
		j++;
		printTime(mirc,time);
		if(j == 32)
		{
			ReadAddress+=400;
			j=0;
		}
	}
//	uint32_t data;
//	uint32_t *p = (uint32_t*)(StartAddress+i);
//	data = *p;
	
}
void WriteflashCount(void)
{
	FLASH_Unlock();
	FLASH_ClearFlag(FLASH_FLAG_EOP | FLASH_FLAG_PGERR | FLASH_FLAG_WRPRTERR); 
  FLASHStatus = FLASH_ErasePage(countAddress);

	if(FLASHStatus == FLASH_COMPLETE)
	{
		FLASHStatus = FLASH_ProgramWord(countAddress, count);
	}
}

void Writeflash(struct pliuTime *data)
{
	FLASH_Unlock();
	FLASH_ClearFlag(FLASH_FLAG_EOP | FLASH_FLAG_PGERR | FLASH_FLAG_WRPRTERR); 
	
  FLASHStatus = FLASH_ErasePage(StartAddress);

	if(FLASHStatus == FLASH_COMPLETE)
	{
		int i=0;
		int j=0;
		for(j =0 ; j < 32 ; j++)
		{			
			FLASHStatus = FLASH_ProgramWord(StartAddress+i*4, data[j].time.tm_year);			
			i++;
			FLASHStatus = FLASH_ProgramWord(StartAddress+i*4, data[j].time.tm_mon);			
			i++;
			FLASHStatus = FLASH_ProgramWord(StartAddress+i*4, data[j].time.tm_mday);			
			i++;
			FLASHStatus = FLASH_ProgramWord(StartAddress+i*4, data[j].time.tm_hour);			
			i++;
			FLASHStatus = FLASH_ProgramWord(StartAddress+i*4, data[j].time.tm_min);			
			i++;
			FLASHStatus = FLASH_ProgramWord(StartAddress+i*4, data[j].time.tm_sec);			
			i++;
			FLASHStatus = FLASH_ProgramWord(StartAddress+i*4, data[j].micros*100);			
			i++;
		}	
		count += j;
		StartAddress += 0x400;
//		FLASHStatus = FLASH_ProgramWord(StartAddress+4, data[1]);
//		FLASHStatus = FLASH_ProgramWord(StartAddress+8, data[2]);
	}
	WriteflashCount();
}





















