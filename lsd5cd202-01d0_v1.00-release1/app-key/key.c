#include <stdio.h> 
#include <stdlib.h> 
#include <unistd.h> 
#include <sys/ioctl.h> 
#include <sys/types.h> 
#include <sys/stat.h> 
#include <fcntl.h> 
#include <sys/select.h> 
#include <sys/time.h> 
#include <errno.h> 

#define M_BTN_UP		(1 << 0)
#define M_BTN_DOWN		(1 << 1)
#define M_BTN_LEFT		(1 << 2)
#define M_BTN_RIGHT		(1 << 3)
#define M_BTN_ENTER		(1 << 4)
#define M_BTN_CANCEL	(1 << 5)
unsigned char key; 

int main(void) 
{ 
     int  buttons_fd;  
	 int i;
 
     // �򿪰����豸/dev/buttons  
     buttons_fd = open("/dev/key", 0); 
     if (buttons_fd < 0) { 
         // ��ʧ�����˳�  
         perror("open device buttons"); 
         exit(1); 
     } 
 
	while(1)
	{
		 // ʹ�� read ������ȡһ�鰴��ֵ��6 ����  
		i = read(buttons_fd, &key, 1);
		//printf("i=%d\n",i);
		if (i != 1) 
		{ 
		    perror("read buttons:"); 
		    exit(1); 
		} 	
		else
		{
			if(key != 0)			
				printf("key = %02x\n",key);
			if((key & M_BTN_UP) != 0)
			{
				printf("detect UP key\n");
			}
			if((key & M_BTN_DOWN) != 0)
			{
				printf("detect DOWN key\n");
			}
			if((key & M_BTN_LEFT) != 0)
			{
				printf("detect LEFT key\n");
			}
			if((key & M_BTN_RIGHT) != 0)
			{
				printf("detect RIGHT key\n");
			}
			if((key & M_BTN_ENTER) != 0)
			{
				printf("detect ENTER key\n");
			}
			if((key & M_BTN_CANCEL) != 0)
			{
				printf("detect CANCEL key\n");
			}
		}
		usleep(1000*100);
	}

     // �رհ����豸�ļ�  
     close(buttons_fd); 
     return 0; 
} 


