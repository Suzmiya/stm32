#include "menu.h"
#include "SysTick.h"
#include "key.h"
#include "dc_motor.h"
#include "usart.h"
#include "lcd1602.h"
#include "beep.h"
#include "sr04.h"

u8 space = 0;
u8 laba = 0;
u8 bz=0;
u16 dis1;
u16 dis2;

void ctrl_pin_init()
{
	GPIO_InitTypeDef GPIO_InitStructure;//����ṹ�����
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
	
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_0|GPIO_Pin_4|GPIO_Pin_5|GPIO_Pin_7|
								GPIO_Pin_8|GPIO_Pin_11|GPIO_Pin_12;  //ѡ����Ҫ���õ�IO��
	
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_IPU;	 //��������
	
	GPIO_Init(GPIOA,&GPIO_InitStructure); 	   /* ��ʼ��GPIO */
}

void show(u8 flag)	//lcd��ʾ
{
	lcd1602_show_string(0,0,"MODE:"); 
	lcd1602_show_string(0,1,"STATE:");
	if(PAin(11)==1)
	{
		lcd1602_show_string(12,1,"HIGH");
	}
	else
	{
		lcd1602_show_string(12,1,"LOW");
	}
	if(flag==5)
	{
		lcd1602_show_string(5,0,"Btooth");
		if(USART1_RX_BUF[0]==0X01)
		{
			lcd1602_show_string(6,1,"Fward");
		}
		else if(USART1_RX_BUF[0]==0X02)
		{
			lcd1602_show_string(6,1,"Back ");
		}
		else if(USART1_RX_BUF[0]==0X03)
		{
			lcd1602_show_string(6,1,"Left ");
		}
		else if(USART1_RX_BUF[0]==0X04)
		{
			lcd1602_show_string(6,1,"Right");
		}
		if(USART1_RX_BUF[0]==0X05)
		{
			lcd1602_show_string(12,0,"BEEP");
		}
		else
		{
			lcd1602_show_string(12,0,"    ");
		}
	}
	else
	{
		lcd1602_show_string(5,0,"Button");
		if(flag==0)
		{
			lcd1602_show_string(6,1,"Stop ");
		}
		else if(flag==1)
		{
			lcd1602_show_string(6,1,"Fward");
		}
		else if(flag==2)
		{
			lcd1602_show_string(6,1,"Back ");
		}
		else if(flag==3)
		{
			lcd1602_show_string(6,1,"Left ");
		}
		else if(flag==4)
		{
			lcd1602_show_string(6,1,"Right");
		}
		if(laba==0)
		{
			lcd1602_show_string(12,0,"BEEP");
		}
		else
		{
			lcd1602_show_string(12,0,"    ");
		}
	}
}

void scan_space() //�ߵ���ģʽ
{
	if(PAin(11)==1)
	{
		car_space_high();
	}
	else
	{
		car_space_low();
		space++;
		if(space==2)
		{
			space=0;
			car_space_high();
		}
	}
}

void scan_didi() //����
{
	if(PAin(12))
	{
		GPIO_SetBits(GPIOB,GPIO_Pin_3); //��������
		laba=1; //��־
	}
	else
	{
		GPIO_ResetBits(GPIOB,GPIO_Pin_3); //������ͣ
		laba=0; //��־
	}
}

void chuankou()
{
	if(USART1_RX_BUF[0]==0X01)//ǰ��
		{
			USART1_RX_BUF[0]=0;
			
			if(bz==0 || bz==1) car_forward();	//ǰ��
			else if(bz==2) car_right(); //��ת
			else if(bz==3) car_left();	//��ת
			else if(bz==4) car_stop(); //ֹͣ
			
		}
		else if(USART1_RX_BUF[0]==0X02)//����
		{
			USART1_RX_BUF[0]=0;
			
			car_back();	//����
		}
		else if(USART1_RX_BUF[0]==0X03)//��ת
		{
			USART1_RX_BUF[0]=0;
			
			if(bz==2 || bz==4) car_stop(); //ֹͣ
			else car_left();
			
		}
		else if(USART1_RX_BUF[0]==0X04)//��ת
		{
			USART1_RX_BUF[0]=0;
			
			if(bz==3 || bz==4) car_stop(); //ֹͣ
			else car_right();	//��ת
			
		}
		else if(USART1_RX_BUF[0]==0X05)//����
		{
			USART1_RX_BUF[0]=0;
			
			GPIO_ResetBits(GPIOB,GPIO_Pin_3); //��������
			
			delay_ms(3000);
			
			GPIO_SetBits(GPIOB,GPIO_Pin_3);	//������ͣ
		}
		else
		{
			car_stop();	//ֹͣ
		}
}

void get_csb()
{
		USART_Cmd(USART1, DISABLE); 
		dis1=csb1();
		USART_Cmd(USART1, ENABLE); 
		
		USART_Cmd(USART1, DISABLE); 
		dis2=csb2();
		USART_Cmd(USART1, ENABLE); 
	
		if(csb_key()==1)
		{
			if(dis1>=10 && dis2>=10)
			{
				bz=1;
			}
			else if(dis1<10 && dis2>=10)
			{
				bz=2;
			}
			else if(dis1>=10 && dis2<10)
			{
				bz=3;
			}
			else bz=4;
		}
		else bz=0;
}


void car_menu()
{
	
	u8 key=0;
	
	get_csb();
	
	scan_space(); //ɨ���ٶ�ģʽ
	
	scan_didi(); //ɨ�����Ȱ�ť
	
	key=KEY_Scan(); //ɨ�跽��ť
	
	show(key); //lcd��ʾ
	
	if(key==5) // ����ģʽ
	{
		chuankou();
	}
	else
	{
		switch(key)
		{
			case 0: car_stop();break; //ֹͣ
			
			case 1: if(bz==0 || bz==1) car_forward();	//ǰ��
							else if(bz==2) car_right(); //��ת
							else if(bz==3) car_left();	//��ת
							else if(bz==4) car_stop(); //ֹͣ
							break;
			
			case 2: car_back();break; //����
			
			case 3: if(bz==2 || bz==4) car_stop(); //ֹͣ
							else car_left()
							;break; //��ת
							
			
			case 4: if(bz==3 || bz==4) car_stop(); //ֹͣ
							else car_right();	//��ת
							break;
		}
	}
}
