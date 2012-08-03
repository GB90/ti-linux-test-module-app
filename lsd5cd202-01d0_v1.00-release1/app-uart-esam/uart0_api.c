#include <stdio.h> 
#include <unistd.h> 
#include <termios.h> 
#include <fcntl.h> 
#include <sys/ioctl.h> 
#include "uart0_api.h"

// �趨������
/** 
*@brief  ���ô���ͨ������ 
*@param  fd     ���� int  �򿪴��ڵ��ļ���� 
*@param  speed  ���� int  �����ٶ� 
*@return  void 
*/ 
static int speed_arr[] = {  B57600,B38400, B19200, B9600, B4800, B2400, B1200, B300, 
          B57600,B38400, B19200, B9600, B4800, B2400, B1200, B300, }; 
static int name_arr[] = { 57600,38400,  19200,  9600,  4800,  2400,  1200,  300, 57600,38400,   
          19200,  9600, 4800, 2400, 1200,  300, }; 
static void set_speed(int fd, int speed)
{ 
  int   i;  
  int   status;  
  struct termios Opt; 
  tcgetattr(fd, &Opt);  
  for ( i= 0;  i < sizeof(speed_arr) / sizeof(int);  i++) {  
    if  (speed == name_arr[i]) {      
      tcflush(fd, TCIOFLUSH);      
      cfsetispeed(&Opt, speed_arr[i]);   
      cfsetospeed(&Opt, speed_arr[i]);    
      status = tcsetattr(fd, TCSANOW, &Opt);   
      if  (status != 0) {         
        perror("tcsetattr fd");   
        return;      
      }     
      tcflush(fd,TCIOFLUSH);    
    }   
  } 
} 

// ���ô�������λ��ֹͣλ��Ч��λ
/** 
*@brief   ���ô�������λ��ֹͣλ��Ч��λ 
*@param  fd     ����  int  �򿪵Ĵ����ļ���� 
*@param  databits ����  int ����λ   ȡֵ Ϊ 7 ����8 
*@param  stopbits ����  int ֹͣλ   ȡֵΪ 1 ����2 
*@param  parity  ����  int  Ч������ ȡֵΪN,E,O,,S 
*/ 
static int set_Parity(int fd,int databits,int stopbits,int parity) 
{  
	struct termios options;  
	if (tcgetattr(fd,&options) != 0) 
	{  
		perror("SetupSerial 1");      
    		return(-1);   
  	} 
  	options.c_cflag &= ~CSIZE;  
  	switch (databits) /*��������λ��*/ 
  	{    
  		case 7:    
    		options.c_cflag |= CS7;  
    		break; 
  		case 8:      
    		options.c_cflag |= CS8; 
    		break;    
  		default:     
    		fprintf(stderr,"Unsupported data size\n"); 
		return (-1);   
  	} 
	switch (parity)  
	{    
		case 'n': 
		case 'N':     
		options.c_cflag &= ~PARENB;   /* Clear parity enable */ 
		options.c_iflag &= ~INPCK;     /* Enable parity checking */  
		break;   
		case 'o':    
		case 'O':      
		options.c_cflag |= (PARODD | PARENB); /* ����Ϊ��Ч��*/   
		options.c_iflag |= INPCK;             /* Disnable parity checking */  
		break;   
		case 'e':   
		case 'E':    
		options.c_cflag |= PARENB;     /* Enable parity */     
		options.c_cflag &= ~PARODD;   /* ת��ΪżЧ��*/      
		options.c_iflag |= INPCK;       /* Disnable parity checking */ 
		break; 
		case 'S':  
		case 's':  /*as no parity*/    
		options.c_cflag &= ~PARENB; 
		options.c_cflag &= ~CSTOPB;
		break;   
		default:    
		fprintf(stderr,"Unsupported parity\n");     
		return (-1);   
	  }   
	/* ����ֹͣλ*/   
	switch (stopbits) 
	{    
		case 1:     
		options.c_cflag &= ~CSTOPB;   
		break;   
		case 2:     
		options.c_cflag |= CSTOPB;   
		break; 
		default:     
		fprintf(stderr,"Unsupported stop bits\n");   
		return (-1);  
	}  

	/* Set input parity option */  
	if (parity != 'n')
	{
		options.c_iflag |= INPCK; 
	} 
	tcflush(fd,TCIFLUSH); 
	options.c_lflag &= (~ECHO); 
	options.c_lflag &= (~ICANON); 
	options.c_cc[VTIME] = 1; /* ���ó�ʱ15 seconds*/    
	options.c_cc[VMIN] = 100; /* Update the options and do it NOW */ 

	//c_cc�����VSTART��VSTOPԪ�ر��趨��DC1��DC3������ASCII��׼��XON��XOFF�ַ�������ڴ����������ַ���ʱ
	//��ʹ�����ȥ����Ҫ��������������Σ����� 
	options.c_iflag &= ~ (IXON | IXOFF | IXANY); 
	
	//��ʱ������write��������ʱû�м���س�����Ϣ�ͷ��Ͳ���ȥ������Ҫ����Ϊ�������������ʱ�ǰ��չ淶ģʽ���յ�
	//�س����вŷ��ͣ�����������������ǲ��ؼ���س����еġ���ʱӦת�����з�ʽ���룬��������ֱ�ӷ��ͣ�������
	//�£� 
	options.c_lflag &= ~ (ICANON | ECHO | ECHOE | ISIG); 
	
	//����������������������ַ�0X0d��ʱ���������ն˵õ����ַ���0X0a��ԭ������Ϊ�ڴ���������c_iflag��c_oflag�д�
	//�ڴ�NL-CR��CR-NL��ӳ�䣬�������ܰѻس��ͻ��е���ͬһ���ַ������Խ���������������֮�� 
	options.c_iflag &= ~ (INLCR | ICRNL | IGNCR); 
	options.c_oflag &= ~(ONLCR | OCRNL); 
	

	if (tcsetattr(fd,TCSANOW,&options) != 0)    
	{  
  		perror("SetupSerial 3");    
  		return (-1);   
	}  
	return (0);   
} 

int fd_uart0;
struct timeval uart0_tv;
fd_set uart0_ready;		/* used for select */

int fn_init_uart0(int baudrate,int databits,int stopbits,int parity)
{
	char *dev  = "/dev/ttyS0"; 
	uart0_tv.tv_sec = 0;
	uart0_tv.tv_usec = 0;
	fd_uart0 = open(dev,O_RDWR);       
	if (-1 == fd_uart0)  
	{        
		perror("Can't Open Serial Port"); 
		return -1;     
	}   
	set_speed(fd_uart0,baudrate); 
	if (set_Parity(fd_uart0,databits,stopbits,parity) == -1)  
	{ 
		printf("Set Parity Error\n"); 
		return -1;
	} 
	return 0;	
}


int fn_close_uart0(void)
{
	int result;
	result = close(fd_uart0);   	
}

int fn_read_data_block_uart0(char* buff,int len)
{
	int nread;	
	nread = read(fd_uart0, buff, len);
	return nread;	
	/*if(nread<0) 
	{
		perror("read error"); 
	}*/	
}

int fn_write_data_block_uart0(char* buff,int len)
{
	int nwrite;	
	nwrite = write(fd_uart0,buff,len); //��GPIO�豸�ļ���д���� 
	return nwrite;	
	/*if(nwrite<0) 
	{
		perror("read error"); 
	}*/	
}

// ���fd_uart0�пɶ��¼����򷵻�0,���򷵻�-1
// �ú�������ֻ�ǲ�ѯ������ȴ����������������ص�
int fn_poll_uart0_recv(void)
{
	FD_ZERO(&uart0_ready);
	FD_SET(fd_uart0, &uart0_ready);	
	select(fd_uart0 + 1, &uart0_ready, NULL, NULL, &uart0_tv);
	if (FD_ISSET(fd_uart0, &uart0_ready)) 
	{
		return 0;	
	}
	return -1;
}






