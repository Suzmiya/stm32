#ifndef _key_H
#define _key_H


#include "system.h"
 	

//使用位操作定义
#define KEY1 	PAin(0)
#define KEY2 	PAin(4)
#define KEY3 	PAin(5)
#define KEY4 	PAin(7)
#define KEY5 	PBin(15)
#define KEY6 	PAin(8)

//定义各个按键值  
#define KEY1_PRESS 		1
#define KEY2_PRESS		2
#define KEY3_PRESS		3
#define KEY4_PRESS		4
#define KEY5_PRESS		5

#define KEY6_PRESS		1
 
void KEY_Init(void);
u8 KEY_Scan();
u8 csb_key();
#endif
