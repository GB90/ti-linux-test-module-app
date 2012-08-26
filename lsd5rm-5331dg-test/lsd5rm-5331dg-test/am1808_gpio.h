#ifndef _AM1808_GPIO_H_
#define _AM1808_GPIO_H_

#define M_GPIO_OUTPUT  	0
#define M_GPIO_INPUT	1
#define M_GPIO_OUTPUT_HIGH  	1
#define M_GPIO_OUTPUT_LOW		0

#define DEVICE_NAME "/dev/am335x-gpio" //�豸��(/dev/led) 
#define MOTOR_MAGIC 'g'
#define SET_GPIO_DIRECT                 (_IOW(MOTOR_MAGIC, 0,int))     // cmd�����ֵ  arg��ֵ 1=����  0=��� 
#define SET_GPIO_VALUE_BASE 		(_IOW(MOTOR_MAGIC, 0,int)+200)   // cmd�����ֵ  arg��ֵ 1=�ߵ�ƽ  0=�ߵ�ƽ 
#define GET_GPIO_VALUE_BASE 		(_IOW(MOTOR_MAGIC, 0,int)+400)   // cmd�����ֵ  arg��ֵ��ʾ����ֵ��ָ��

extern int fn_am1808_gpio_init(void);
extern int fn_get_am1808_gpio_value(int gpio_num);
extern int fn_set_am1808_gpio_value(int gpio_num,int value);
extern int fn_set_am1808_gpio_direct(int gpio_num,int direct);
extern int fn_am1808_gpio_exit(void);

#endif
