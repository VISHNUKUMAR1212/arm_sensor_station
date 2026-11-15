#include"header.h"
unsigned int m_second=0;

void timer0_intr_init()
{
        unsigned int pclk;
        if(VPBDIV==0)
pclk=15000;
else if(VPBDIV==1)
pclk=60000;
else if(VPBDIV==2)
pclk=30000;
T0TCR=0X02;
T0PC=0;
T0PR=pclk-1;
T0MR0=1;
T0MCR=0X03;
T0IR=0xff;
T0TCR=0X01;
}

void TIMER0_HANDLER()__irq
{
        m_second++;
        T0IR=0X01;
        VICVectAddr=0;
}
void config_vic_for_TIMER0()
{
        VICIntSelect=0;
        VICVectCntl0=(1<<5)|4;
        VICVectAddr0=(unsigned int)TIMER0_HANDLER;
        VICIntEnable=1<<4;

}/*
int m_second=0;
void timer_init()  
{
	  int pclk;
    if(VPBDIV==0)
				pclk=15000;
		else if(VPBDIV==1)
				pclk=60000;
		else if(VPBDIV==2)
				pclk=30000;
		T0TCR=0X02;
		T0PC=0;
		T0PR=0;
		T0MR0=pclk*1;
		T0MCR=0X03;
		T0IR=0xff;
		T0TCR=0X01;
		
}

void timer_handler() __irq
{
  T0IR=1;
	m_second=1;

	 VICVectAddr=0;
}

void timer_config()
{
		 VICIntSelect=0;
		 VICVectAddr0=(unsigned int)timer_handler;
		 VICVectCntl0=0x20 | 4;
		 VICIntEnable=1<<4;
		 
		 
}*/
