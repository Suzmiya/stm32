#include "stdio.h"
#include "system.h"
#include "SysTick.h"
#include "usart.h"
#include "dc_motor.h"
#include "key.h"
#include "lcd1602.h"
#include "beep.h"
#include "sr04.h"

#include "menu.h"


int main()
{
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);  //�ж����ȼ�����
	RCC_SYSCLKConfig(RCC_SYSCLKSource_HSI);
	
	KEY_Init();	//��ʼ����ť
	
	dc_motor_init();	//��ʼ��ֱ�����
	
	lcd1602_init();	//��ʼ��������
	
	BEEP_Init();	//��ʼ��������
	
	ultrasonicwave_init();//��ʼ��������
	
	USART1_Init(115200); //���岨����
	
	while(1)
	{
			car_menu();
	}
}
