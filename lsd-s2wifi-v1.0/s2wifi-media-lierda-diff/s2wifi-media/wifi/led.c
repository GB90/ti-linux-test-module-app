//-----------------------------------------------------------------------------
//
//                                 timer�жϳ���         
//                                  Դ�ļ�(*.c)
//
//
//                    ��Ȩ����(C)2005-2010 ������Ƽ����޹�˾
//
//
// �ļ���    : template.c
// ����      : nmy
// ��������  : 2011-09-21
//
// arm gcc   : arm-none-linux-gnueabi-gcc 4.5.3
//
// �汾��¼  : V1.00  ������һ��   2010-09-11 15:30
//
//-----------------------------------------------------------------------------

#include <stdio.h> 
#include <stdlib.h> 
#include <unistd.h> 
#include <sys/ioctl.h> 
#include <led.h>
#include <debug.h>

#define MOTOR_MAGIC 'L'
#define SET_LED              _IOW(MOTOR_MAGIC, 1,int)

//-----------------------------------------------------------------------------
//
// ��������  :   
// ��������  :  
//
// �������  :  char* led_name   ָ��led����
//			int value   1 ��ʾled��  0 ��ʾ��
//
// ���ز���  :  ���ִ�гɹ�����0,���򷵻�-1
// 
//-----------------------------------------------------------------------------
int fn_led_set (char* led_name,int value)
{
	int fd;	
	fd = open(led_name, 0);    
	if (fd < 0) 
	{ 
		#if(LED_DEBUG >= 3)
		debug_out("led:open dev %s failed \n",led_name);
		#endif		
		return -1;
        } 
	if(value == 0)
	{
		ioctl(fd, SET_LED,1); 
	}
	else
	{
		ioctl(fd, SET_LED,0); 
	}
	close(fd); 
	return 0;
}
