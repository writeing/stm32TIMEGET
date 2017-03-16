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
		if(count == 0xffffffff)
			count = 0;
		StartAddress += count*0x800;
		printf("aaaaaaaaa:%d\r\n",count);
}
void printTime(int mirc,struct tm time)
{
	char buff[50];
	strftime(buff,sizeof(buff),"aaa:%Y-%m-%d %H:%M:%S",&time);					
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
	int i=count;
	//StartAddress-=count * 0x800;
	while(i)
	{
		printf("i = %d\r\n",i);
		for(int i=0; i< SAVECOUNT ;i++)
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
		}
		ReadAddress+=0x800;		
		j=0;
		i --;
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
		for(j =1 ; j <= SAVECOUNT ; j++)
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
		count += 1;
		printf("wxc count = %d\r\n",count);
		StartAddress += 0x800;
//		FLASHStatus = FLASH_ProgramWord(StartAddress+4, data[1]);
//		FLASHStatus = FLASH_ProgramWord(StartAddress+8, data[2]);
	}
	WriteflashCount();
}





















