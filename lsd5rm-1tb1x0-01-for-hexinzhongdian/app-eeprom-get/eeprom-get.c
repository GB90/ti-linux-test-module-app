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

int main(int argc, char **argv)
{
	int  fd, ret;
	char  *eprom, mac_string[100];
	eeprom_data   *eepromconfig;
	struct i2c_rdwr_ioctl_data e2prom_data;
	unsigned long sn;
	unsigned char year,month,day;

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

	
	/******read data from e2prom*******/
	e2prom_data.nmsgs=2;
	(e2prom_data.msgs[0]).len=1;		//e2prom Ŀ�����ݵĵ�ַ
	(e2prom_data.msgs[0]).addr=0x50;	// e2prom �豸��ַ
	(e2prom_data.msgs[0]).flags=0;		//write
	(e2prom_data.msgs[0]).buf=(unsigned char*)malloc(2);
	(e2prom_data.msgs[0]).buf[0]=0x10;	//e2prom���ݵ�ַ
	(e2prom_data.msgs[1]).len=7;		//����������
	(e2prom_data.msgs[1]).addr=0x50;	// e2prom �豸��ַ 
	(e2prom_data.msgs[1]).flags=I2C_M_RD;	//read
	(e2prom_data.msgs[1]).buf=(unsigned char*)malloc(7);	//��ŷ���ֵ�ĵ�ַ��
	(e2prom_data.msgs[1]).buf[0]=0;		//��ʼ��������


	ret=ioctl(fd,I2C_RDWR,(unsigned long)&e2prom_data);
	if(ret<0)
	{
		printf("\n\r ioctl error read");
		return 0;
	}
	else
	{
		printf("Read from  EEPROM address=0x%02x\n",	(e2prom_data.msgs[0]).buf[0]);
		printf("data=%02x %02x %02x %02x %02x %02x %02x \n",	
				(e2prom_data.msgs[1]).buf[0],
				(e2prom_data.msgs[1]).buf[1],
				(e2prom_data.msgs[1]).buf[2],
				(e2prom_data.msgs[1]).buf[3],
				(e2prom_data.msgs[1]).buf[4],
				(e2prom_data.msgs[1]).buf[5],
				(e2prom_data.msgs[1]).buf[6]);
	}

	eepromconfig = (eeprom_data   *)(e2prom_data.msgs[1].buf);
	printf("eepromconfig.sn_code=%d\n",eepromconfig->sn_code);
	printf("eepromconfig.year=%d\n",eepromconfig->year);
	printf("eepromconfig.month=%d\n",eepromconfig->month);
	printf("eepromconfig.day=%d\n",eepromconfig->day);

	// free buff
	free((e2prom_data.msgs[0]).buf);
	free((e2prom_data.msgs[1]).buf);

	// free buff
	free(e2prom_data.msgs);

	close(fd);

	return 0;
}




