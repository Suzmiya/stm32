#ifndef _dc_motor_H
#define _dc_motor_H

#include "system.h"

//MOTOR1管脚定义
#define MOTOR1_IN1_PORT 			GPIOB   
#define MOTOR1_IN1_PIN 				GPIO_Pin_5
#define MOTOR1_IN1_PORT_RCC			RCC_APB2Periph_GPIOB

#define MOTOR1_IN2_PORT 			GPIOB   
#define MOTOR1_IN2_PIN 				GPIO_Pin_6
#define MOTOR1_IN2_PORT_RCC			RCC_APB2Periph_GPIOB

#define MOTOR1_ENA_PORT 			GPIOA   
#define MOTOR1_ENA_PIN 				GPIO_Pin_1
#define MOTOR1_ENA_PORT_RCC			RCC_APB2Periph_GPIOA

//MOTOR2管脚定义
#define MOTOR2_IN1_PORT 			GPIOB   
#define MOTOR2_IN1_PIN 				GPIO_Pin_7
#define MOTOR2_IN1_PORT_RCC			RCC_APB2Periph_GPIOB

#define MOTOR2_IN2_PORT 			GPIOB   
#define MOTOR2_IN2_PIN 				GPIO_Pin_8
#define MOTOR2_IN2_PORT_RCC			RCC_APB2Periph_GPIOB

#define MOTOR2_ENA_PORT 			GPIOA   
#define MOTOR2_ENA_PIN 				GPIO_Pin_2
#define MOTOR2_ENA_PORT_RCC			RCC_APB2Periph_GPIOA

//MOTOR3管脚定义
#define MOTOR3_IN1_PORT 			GPIOB   
#define MOTOR3_IN1_PIN 				GPIO_Pin_9
#define MOTOR3_IN1_PORT_RCC			RCC_APB2Periph_GPIOB

#define MOTOR3_IN2_PORT 			GPIOB   
#define MOTOR3_IN2_PIN 				GPIO_Pin_10
#define MOTOR3_IN2_PORT_RCC			RCC_APB2Periph_GPIOB

#define MOTOR3_ENA_PORT 			GPIOA   
#define MOTOR3_ENA_PIN 				GPIO_Pin_3
#define MOTOR3_ENA_PORT_RCC			RCC_APB2Periph_GPIOA

//MOTOR4管脚定义
#define MOTOR4_IN1_PORT 			GPIOB   
#define MOTOR4_IN1_PIN 				GPIO_Pin_11
#define MOTOR4_IN1_PORT_RCC			RCC_APB2Periph_GPIOB

#define MOTOR4_IN2_PORT 			GPIOB   
#define MOTOR4_IN2_PIN 				GPIO_Pin_12
#define MOTOR4_IN2_PORT_RCC			RCC_APB2Periph_GPIOB

#define MOTOR4_ENA_PORT 			GPIOA   
#define MOTOR4_ENA_PIN 				GPIO_Pin_6
#define MOTOR4_ENA_PORT_RCC			RCC_APB2Periph_GPIOA


#define MOTOR1_IN1 	PBout(5)
#define MOTOR1_IN2 	PBout(6) 
#define MOTOR1_ENA 	PAout(1)

#define MOTOR2_IN1 	PBout(7)
#define MOTOR2_IN2 	PBout(8) 
#define MOTOR2_ENA 	PAout(2)

#define MOTOR3_IN1 	PBout(9)
#define MOTOR3_IN2 	PBout(10) 
#define MOTOR3_ENA 	PAout(3)

#define MOTOR4_IN1 	PBout(11)
#define MOTOR4_IN2 	PBout(12) 
#define MOTOR4_ENA 	PAout(6)


//函数声明
void dc_motor_init(void);
void car_forward(void);
void car_back(void);
void car_left(void);
void car_right(void);
void car_stop(void);
void car_space_high(void);
void car_space_low(void);
#endif
