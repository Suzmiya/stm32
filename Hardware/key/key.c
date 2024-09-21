#include "key.h"
#include "SysTick.h"

/*******************************************************************************
* 函 数 名         : KEY_Init
* 函数功能		   : 按键初始化
* 输    入         : 无
* 输    出         : 无
*******************************************************************************/
void KEY_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure; //定义结构体变量	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);
	
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_15;
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_IPU;	//上拉输入
	GPIO_Init(GPIOB,&GPIO_InitStructure);
	
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
	
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_8;
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_IPU;	//上拉输入
	GPIO_Init(GPIOA,&GPIO_InitStructure);
	
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
	
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_0|GPIO_Pin_4|GPIO_Pin_5|GPIO_Pin_7
								|GPIO_Pin_11|GPIO_Pin_12;  //选择你要设置的IO口
	
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_IPU;	 //上拉输入
	
	GPIO_Init(GPIOA,&GPIO_InitStructure); 	   /* 初始化GPIO */
	
}

u8 KEY_Scan() //扫描按钮
{

	if(KEY5==0) //蓝牙和按键的模式转换
	{
		delay_ms(1000);  //消抖
		if(KEY5==0)
			return KEY5_PRESS;
	}
	else if(KEY1==0) //前进
	{
		delay_ms(1);  //消抖
		if(KEY1==0)
			return KEY1_PRESS;
	}
	else if(KEY2==0) //后退
	{
		delay_ms(1);  //消抖
		if(KEY2==0)
			return KEY2_PRESS;
	}
	else if(KEY3==0)
	{
		delay_ms(1);  //消抖
		if(KEY3==0)
			return KEY3_PRESS;
	}
	else if(KEY4==0)
	{
		delay_ms(1);  //消抖
		if(KEY4==0)
			return KEY4_PRESS;
	}
	else
	{
		return 0;
	}
}
u8 csb_key()
{
	if(KEY6==0)
	{
		delay_ms(1);  //消抖
		if(KEY6==0)
			return 1;
	}
	else
	{
		return 0;
	}
}
