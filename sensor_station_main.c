#include"header.h"

#define FLAME  ((IOPIN0>>14)&1)
#define PIR 	 ((IOPIN0>>15)&1)
#define LED  	 (1<<5)

extern unsigned int m_second;
int main(){

	unsigned int data=0,c_data=0;
	IODIR0=LED;

	uart_init(9600);
	timer0_intr_init();
	config_vic_for_TIMER0();
	adc_init();

	while(1){

		//============ TEMP ==========
		if(m_second==400){	
			data=0,c_data=0;		
			uart_string("--:Sensor Station:--");			
			data=adc_read(1);
			c_data=(data*3.3*100)/1023;
			uart_string("\r\nTEMPRATURE : ");
			uart_int_con(c_data);
			(c_data>35)?(IOCLR0=LED):(IOSET0=LED);
		}
		//============ POT ===========
		else if(m_second==800){
			data=0,c_data=0;
			data=adc_read(2);
			c_data=(data*3.3)/1023;
			uart_string("\r\nVTG : ");
			uart_int_con(c_data);
		}
		//============ LDR ===========
		else if(m_second==1200){
			data=0,c_data=0;
			data=adc_read(3);
			c_data=(data*100)/1023;
			uart_string("\r\nLDR : ");
			uart_int_con(c_data);
		}
		//============ FIR =================
		else if(m_second==1600){
		     data=0,c_data=0;
			if(FLAME==0){							  				//Active LOw
			uart_string("\r\nFlame : Detected");
				
			}
			else{
			uart_string("\r\nFlame : Not Detected");
		
			}
		}
		//============ PIR =================  
		else if(m_second==2000){	
		data=0,c_data=0;			
			if(PIR==1){													//Active High
				uart_string("\r\nVibration: Detected\r\n\r\n");
				
			}
			else{
				uart_string("\r\nVibretion: Not Detected\r\n\r\n");
				
			}
		}
		else if(m_second==2400)
    {
		    data=0,c_data=0;
				m_second=0;
		}
		 }
}