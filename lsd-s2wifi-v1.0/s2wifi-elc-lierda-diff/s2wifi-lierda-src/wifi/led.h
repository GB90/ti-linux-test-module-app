//-----------------------------------------------------------------------------
//
//                                        
//                                  Դ�ļ�(*.h)
//
//
//                    ��Ȩ����(C)2005-2010 ������Ƽ����޹�˾
//
//
// �ļ���    : led.h 
// ����      : nmy
// ��������  : 2010-09-11
//
// arm gcc   : arm-none-linux-gnueabi-gcc 4.5.3
//
// �汾��¼  : V1.00  ������һ��   2010-09-11 15:30
//
//-----------------------------------------------------------------------------


#ifndef __LED_H__
#define __LED_H__

#define LED_RUN		"/dev/led0"
#define LED_MODE	"/dev/led1"
#define LED_LINK		"/dev/led3"
#define LED_TXD		"/dev/led2"
#define LED_RXD		"/dev/led4"

#define M_LED_UART_ON_CNT   3
#define M_LED_UART_OFF_CNT   3

extern int fn_led_set (char* led_name,int value);

#endif
