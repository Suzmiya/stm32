#include "sr04.h"
#include "SysTick.h"


void TIM2_Init(u16 per,u16 psc)
{
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2,ENABLE);//使能TIM4时钟
	
	TIM_TimeBaseInitStructure.TIM_Period=per;   //自动装载值
	TIM_TimeBaseInitStructure.TIM_Prescaler=psc; //分频系数
	TIM_TimeBaseInitStructure.TIM_ClockDivision=TIM_CKD_DIV1;
	TIM_TimeBaseInitStructure.TIM_CounterMode=TIM_CounterMode_Up; //设置向上计数模式
	TIM_TimeBaseInit(TIM2,&TIM_TimeBaseInitStructure);
	
	TIM_Cmd(TIM2,DISABLE); //失能定时器	
}

//超声波管脚初始化
void sr04_gpio_init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;	//声明一个结构体变量，用来初始化GPIO

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);   /* 开启GPIO时钟 */

	/*  配置GPIO的模式和IO口 */
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_13;		//选择你要设置的IO口
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_Out_PP;		  //设置推挽输出模式
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;	  //设置传输速率
	GPIO_Init(GPIOB,&GPIO_InitStructure); 	 /* 初始化GPIO */
	
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_14;		//选择你要设置的IO口
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_IPU;	
	GPIO_Init(GPIOB,&GPIO_InitStructure); 	 /* 初始化GPIO */
	
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC,ENABLE);   /* 开启GPIO时钟 */

	/*  配置GPIO的模式和IO口 */
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_8;		//选择你要设置的IO口
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_Out_PP;		  //设置推挽输出模式
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;	  //设置传输速率
	GPIO_Init(GPIOC,&GPIO_InitStructure); 	 /* 初始化GPIO */
	
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_9;		//选择你要设置的IO口
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_IPU;	
	GPIO_Init(GPIOC,&GPIO_InitStructure); 	 /* 初始化GPIO */
}

//超声波初始化
void ultrasonicwave_init(void)
{
	sr04_gpio_init();
	PBout(13)=0;
	PBin(14)=1;
	TIM2_Init(0xffff,7);//定时1us计数1次
}

//超声波测距
//返回值：测量距离cm
float csb1(void)
{
	u16 temp=0;
	
	PBout(13)=1;	//拉高
	delay_10us(2);//大约20us
	PBout(13)=0;	//拉低
	while(PBin(14)==0);	//等待高电平到来
	TIM_SetCounter(TIM2,0);//清零计数器值
	TIM_Cmd(TIM2,ENABLE);//开启定时器，开始计数
	while(PBin(14)==1);	//等待高电平结束
	TIM_Cmd(TIM2,DISABLE);//关闭定时器
	temp=TIM_GetCounter(TIM2);
	delay_ms(20);
	
	return ((float)temp*0.00034/2)*100;//单位转换为cm
}

float csb2(void)
{
	u16 temp=0;
	
	PCout(8)=1;	//拉高
	delay_10us(2);//大约20us
	PCout(8)=0;	//拉低
	while(PCin(9)==0);	//等待高电平到来
	TIM_SetCounter(TIM2,0);//清零计数器值
	TIM_Cmd(TIM2,ENABLE);//开启定时器，开始计数
	while(PCin(9)==1);	//等待高电平结束
	TIM_Cmd(TIM2,DISABLE);//关闭定时器
	temp=TIM_GetCounter(TIM2);
	delay_ms(20);
	
	return ((float)temp*0.00034/2)*100;//单位转换为cm
}