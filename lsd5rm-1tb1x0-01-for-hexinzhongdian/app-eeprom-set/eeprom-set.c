#include <stdio.h>
#include <linux/types.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/ioctl.h>
#include <errno.h>

#include <linux/i2c.h>
#include <linux/i2c-dev.h>

#pragma pack(1)					// ָ����1�ֽڶ���

typedef  struct  __eeprom_data {
	unsigned int  sn_code;			// ������(��1��ʼ��32λ)�����������ظ��������������ϵ�����һ������Ϊ������ϵͳ��mac��ַ
	char    year;				// ��������
	char    month;				// ��������
	char    day;				// ��������
} eeprom_data;

#pragma pack()					// ȡ��ָ�����룬�ָ�ȱʡ����

unsigned int sn;
char year,month,day;
int main(int argc, char **argv)
{
	int  fd, ret;
	char  *eprom, mac_string[100];
	eeprom_data   eepromconfig;
	struct i2c_rdwr_ioctl_data e2prom_data;
	int tmp;
	
	fd = open("/dev/i2c-3", O_RDWR);

	/*
	 * /dev/i2c-0����ע��i2c-dev.c������ģ�����һ���ɲ������������������ʹ��i2c-dev.c
	 * �ķ�ʽ����û�У�Ҳ����Ҫ����ڵ㡣
	 */
	if(fd < 0)
	{
		printf("\n\r open /dev/i2c-3 error");
		return 0;
	}

	/*
	 * ��Ϊ����ʱ���У�������õ�2����ʼ�źţ��ֽڶ������У������Դ˽�
	 * e2prom_data.nmsgs����Ϊ2
	 */
	e2prom_data.nmsgs = 2;
	e2prom_data.msgs = (struct i2c_msg *)malloc(e2prom_data.nmsgs * sizeof(struct i2c_msg));
	if(!e2prom_data.msgs)
	{
		printf("\n\r e2prom_data.msgs malloc error");
		return 0;
	}

	ioctl(fd, I2C_TIMEOUT, 1);/*��ʱʱ��*/
	ioctl(fd, I2C_RETRIES, 2);/*�ظ�����*/

	
	if(argc != 5)
	{
		printf("Usage:eeprom-set SN YEAR MONTH DAY\n");
		printf("Usage:SN 32bit 100000 start,inc auto\n");
		printf("Usage:YEAR such as 12 is 2012\n");
		printf("Usage:MONTH 01 - 12\n");
		printf("Usage:DAY 01 - 31\n");
		return 0;
	}

	ret = sscanf(argv[1], "%d", &tmp);
	if(ret != 1)
	{
		printf("EEROR:sscanf sn error\n");
	}
	else
	{
		sn = tmp;
		//printf("OK:sscanf sn = %d\n",sn);
	}
	
	ret = sscanf(argv[2], "%d", &tmp);
	if(ret != 1)
	{
		printf("EEROR:sscanf year error\n");
	}
	else
	{
		year = tmp; 
		//printf("OK:sscanf year = %d\n",year);
	}

	ret = sscanf(argv[3], "%d", &tmp);
	if(ret != 1)
	{
		printf("EEROR:sscanf month error\n");
	}
	else
	{
		month = tmp;
		//printf("OK:sscanf month = %d\n",month);
	}

	ret = sscanf(argv[4], "%d", &tmp);
	if(ret != 1)
	{
		printf("EEROR:sscanf day error\n");
	}
	else
	{
		day = tmp;
		//printf("OK:sscanf day = %d\n",day);
	}


	//printf("sn=0x%08x,year=0x%02x,month=0x%02x,day=0x%02x\n",
	//		sn,year,month,day);	
	
	eepromconfig.sn_code = sn;
	eepromconfig.year = year;
	eepromconfig.month = month;
	eepromconfig.day = day;	
	printf("eepromconfig.sn_code=%d\n",eepromconfig.sn_code);
	printf("eepromconfig.year=%d\n",eepromconfig.year);
	printf("eepromconfig.month=%d\n",eepromconfig.month);
	printf("eepromconfig.day=%d\n",eepromconfig.day);
	//printf("eeprom_data sizeof =%d\n",sizeof(eeprom_data));
	eprom = (char *)&eepromconfig;
	//printf("eprom data=%02x %02x %02x %02x %02x %02x %02x \n",
	//			eprom[0],eprom[1],eprom[2],eprom[3],eprom[4],eprom[5],eprom[6]);

	e2prom_data.nmsgs=1;
	(e2prom_data.msgs[0]).len=8;		//2: 1�� e2prom д��Ŀ��ĵ�ַ��1������ 
	(e2prom_data.msgs[0]).addr=0x50;	//e2prom �豸��ַ
	(e2prom_data.msgs[0]).flags=0;		//write
	(e2prom_data.msgs[0]).buf=(unsigned char*)malloc(8);
	(e2prom_data.msgs[0]).buf[0]=0x10;		// e2prom д��Ŀ��ĵ�ַ
	(e2prom_data.msgs[0]).buf[1]=eprom[0];	//the data to write 
	(e2prom_data.msgs[0]).buf[2]=eprom[1];	//the data to write 
	(e2prom_data.msgs[0]).buf[3]=eprom[2];	//the data to write 
	(e2prom_data.msgs[0]).buf[4]=eprom[3];	//the data to write 
	(e2prom_data.msgs[0]).buf[5]=eprom[4];	//the data to write 
	(e2prom_data.msgs[0]).buf[6]=eprom[5];	//the data to write 
	(e2prom_data.msgs[0]).buf[7]=eprom[6];	//the data to write 

	ret=ioctl(fd,I2C_RDWR,(unsigned long)&e2prom_data);
	if(ret<0)
	{
		printf("\n\r ioctl error write");
		return 0;
	}
	else
	{
		printf("write to EEPROM address=0x%02x\n",	(e2prom_data.msgs[0]).buf[0]);
		printf("data=%02x %02x %02x %02x %02x %02x %02x \n",	(e2prom_data.msgs[0]).buf[1],
									(e2prom_data.msgs[0]).buf[2],
									(e2prom_data.msgs[0]).buf[3],
									(e2prom_data.msgs[0]).buf[4],
									(e2prom_data.msgs[0]).buf[5],
									(e2prom_data.msgs[0]).buf[6],
									(e2prom_data.msgs[0]).buf[7]);
	}

	// free buff
	free((e2prom_data.msgs[0]).buf);
	// free buff
	free(e2prom_data.msgs);

	close(fd);

	return 0;
}




