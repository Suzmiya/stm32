#include "sr04.h"
#include "SysTick.h"


void TIM2_Init(u16 per,u16 psc)
{
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2,ENABLE);//ʹ��TIM4ʱ��
	
	TIM_TimeBaseInitStructure.TIM_Period=per;   //�Զ�װ��ֵ
	TIM_TimeBaseInitStructure.TIM_Prescaler=psc; //��Ƶϵ��
	TIM_TimeBaseInitStructure.TIM_ClockDivision=TIM_CKD_DIV1;
	TIM_TimeBaseInitStructure.TIM_CounterMode=TIM_CounterMode_Up; //�������ϼ���ģʽ
	TIM_TimeBaseInit(TIM2,&TIM_TimeBaseInitStructure);
	
	TIM_Cmd(TIM2,DISABLE); //ʧ�ܶ�ʱ��	
}

//�������ܽų�ʼ��
void sr04_gpio_init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;	//����һ���ṹ�������������ʼ��GPIO

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);   /* ����GPIOʱ�� */

	/*  ����GPIO��ģʽ��IO�� */
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_13;		//ѡ����Ҫ���õ�IO��
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_Out_PP;		  //�����������ģʽ
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;	  //���ô�������
	GPIO_Init(GPIOB,&GPIO_InitStructure); 	 /* ��ʼ��GPIO */
	
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_14;		//ѡ����Ҫ���õ�IO��
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_IPU;	
	GPIO_Init(GPIOB,&GPIO_InitStructure); 	 /* ��ʼ��GPIO */
	
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC,ENABLE);   /* ����GPIOʱ�� */

	/*  ����GPIO��ģʽ��IO�� */
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_8;		//ѡ����Ҫ���õ�IO��
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_Out_PP;		  //�����������ģʽ
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;	  //���ô�������
	GPIO_Init(GPIOC,&GPIO_InitStructure); 	 /* ��ʼ��GPIO */
	
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_9;		//ѡ����Ҫ���õ�IO��
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_IPU;	
	GPIO_Init(GPIOC,&GPIO_InitStructure); 	 /* ��ʼ��GPIO */
}

//��������ʼ��
void ultrasonicwave_init(void)
{
	sr04_gpio_init();
	PBout(13)=0;
	PBin(14)=1;
	TIM2_Init(0xffff,7);//��ʱ1us����1��
}

//���������
//����ֵ����������cm
float csb1(void)
{
	u16 temp=0;
	
	PBout(13)=1;	//����
	delay_10us(2);//��Լ20us
	PBout(13)=0;	//����
	while(PBin(14)==0);	//�ȴ��ߵ�ƽ����
	TIM_SetCounter(TIM2,0);//���������ֵ
	TIM_Cmd(TIM2,ENABLE);//������ʱ������ʼ����
	while(PBin(14)==1);	//�ȴ��ߵ�ƽ����
	TIM_Cmd(TIM2,DISABLE);//�رն�ʱ��
	temp=TIM_GetCounter(TIM2);
	delay_ms(20);
	
	return ((float)temp*0.00034/2)*100;//��λת��Ϊcm
}

float csb2(void)
{
	u16 temp=0;
	
	PCout(8)=1;	//����
	delay_10us(2);//��Լ20us
	PCout(8)=0;	//����
	while(PCin(9)==0);	//�ȴ��ߵ�ƽ����
	TIM_SetCounter(TIM2,0);//���������ֵ
	TIM_Cmd(TIM2,ENABLE);//������ʱ������ʼ����
	while(PCin(9)==1);	//�ȴ��ߵ�ƽ����
	TIM_Cmd(TIM2,DISABLE);//�رն�ʱ��
	temp=TIM_GetCounter(TIM2);
	delay_ms(20);
	
	return ((float)temp*0.00034/2)*100;//��λת��Ϊcm
}