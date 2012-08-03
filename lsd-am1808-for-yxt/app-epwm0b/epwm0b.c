#include <stdio.h> 
#include <stdlib.h> 
#include <unistd.h> 
#include <sys/ioctl.h> 
#include "epwm0b.h"
 
#define MOTOR_MAGIC 'W'
#define SET_PWM1_ON	_IOW(MOTOR_MAGIC, 2,int)
#define SET_PWM1_OFF 	_IOW(MOTOR_MAGIC, 3,int)

// PWM �������,���趨PWM��ֵ
int fn_pwm_output_on(unsigned long u32_freq)
{ 
	int fd; 	
	fd = open("/dev/pwm1", 0); 
        if (fd < 0) 
	{ 
           perror("open device error"); 
          return 0;
        } 
       ioctl(fd, SET_PWM1_ON,u32_freq); 
       close(fd); 
}

// PWM����ر�
int fn_pwm_output_off(void)
{ 
	int fd; 	
	fd = open("/dev/pwm1", 0); 
        if (fd < 0) 
	{ 
           perror("open device error"); 
           return 0;
        } 
       ioctl(fd, SET_PWM1_OFF,0); 
       close(fd); 
}


// ������
int main(int argc, char **argv) 
{ 
        int data; 
        int cmd; 
        if ((sscanf(argv[1], "%d", &cmd) != 1))
        {
           fprintf(stderr, "Usage: pwm on/off\n"); 
           exit(1); 
        }
	if(cmd == 1)
	{
		fn_pwm_output_on(38000);
	}
	if(cmd == 0)
	{
		fn_pwm_output_off();
	}
    return 0;
} 

