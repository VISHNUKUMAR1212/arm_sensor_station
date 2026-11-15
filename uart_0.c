#include<lpc21xx.h>
void uart_init(int baud)
{
     int pclk=0,data=0;
	 if(VPBDIV==0)
	    pclk=15000000;
	else if(VPBDIV==2)
	    pclk=60000000;
	else if(VPBDIV==2)
	    pclk=30000000;
	
    PINSEL0=0X05;
    data=pclk/(16*baud);
    U0LCR=0X83;
    U0DLL=data & 0XFF;
    U0DLM=(data >> 8) & 0XFF;
    U0LCR=0X03;

}
void  uart_tx(char data)
{

   U0THR=data;
   while(((U0LSR>>5)&1)==0);
   
}
char  uart_rx()
{

   while(((U0LSR>>0)&1)==0);
   return U0RBR;
   
}
void uart_string(char *p)
{
   while(*p)
   {
      uart_tx(*p);
	  p++;
   }
}
int int_data_uart()
{
    char data;
	int num=0;
    while(1)
	{
	   data=uart_rx();
	   uart_tx(data);
	   if(data==13)
	      break;
	   num=num*10+(data-48);
	}
	return num;
}		  
void uart_int_con(int num)
{
    char s[20];
	  int i=0,n=num;
	while(n)
	{
	   s[i]=(n%10)+48;
	   i++;
	   n=n/10;
	}
	while(i>=0)
	{
	   uart_tx(s[i]);
	   i--;
	}
}