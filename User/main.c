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
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);  //中断优先级分组
	RCC_SYSCLKConfig(RCC_SYSCLKSource_HSI);
	
	KEY_Init();	//初始化按钮
	
	dc_motor_init();	//初始化直流电机
	
	lcd1602_init();	//初始化蜂鸣器
	
	BEEP_Init();	//初始化蜂鸣器
	
	ultrasonicwave_init();//初始化超声波
	
	USART1_Init(115200); //定义波特率
	
	while(1)
	{
			car_menu();
	}
}
