#include "key.h"
#include "SysTick.h"

/*******************************************************************************
* �� �� ��         : KEY_Init
* ��������		   : ������ʼ��
* ��    ��         : ��
* ��    ��         : ��
*******************************************************************************/
void KEY_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure; //����ṹ�����	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);
	
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_15;
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_IPU;	//��������
	GPIO_Init(GPIOB,&GPIO_InitStructure);
	
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
	
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_8;
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_IPU;	//��������
	GPIO_Init(GPIOA,&GPIO_InitStructure);
	
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
	
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_0|GPIO_Pin_4|GPIO_Pin_5|GPIO_Pin_7
								|GPIO_Pin_11|GPIO_Pin_12;  //ѡ����Ҫ���õ�IO��
	
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_IPU;	 //��������
	
	GPIO_Init(GPIOA,&GPIO_InitStructure); 	   /* ��ʼ��GPIO */
	
}

u8 KEY_Scan() //ɨ�谴ť
{

	if(KEY5==0) //�����Ͱ�����ģʽת��
	{
		delay_ms(1000);  //����
		if(KEY5==0)
			return KEY5_PRESS;
	}
	else if(KEY1==0) //ǰ��
	{
		delay_ms(1);  //����
		if(KEY1==0)
			return KEY1_PRESS;
	}
	else if(KEY2==0) //����
	{
		delay_ms(1);  //����
		if(KEY2==0)
			return KEY2_PRESS;
	}
	else if(KEY3==0)
	{
		delay_ms(1);  //����
		if(KEY3==0)
			return KEY3_PRESS;
	}
	else if(KEY4==0)
	{
		delay_ms(1);  //����
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
		delay_ms(1);  //����
		if(KEY6==0)
			return 1;
	}
	else
	{
		return 0;
	}
}
