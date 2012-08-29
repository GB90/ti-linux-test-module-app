/**
 * @file i2c_rx8025t_test.c
 * @brief test for rx8025t on /dev/i2c-0
 *
 * Copyright (C) 2006-2011, toby
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 * @author toby.zhang <toby.chs@gmail.com>
 * @date 2011-7-24 21:30:07
 * @version 0.01
 *
 * This file is pary of driver for RX8025T.
 */

/**
 * @note
 *  \n
 *  
 * \b Change \b Logs: \n
 * 2011.06.01   ������ʼ by toby \n
 * 
 */

/**
 * @addtogroup api_i2c_rx8025t_test
 * @{ 
 */

//#include "i2c_rx8025t_test.h"

// TODO: Add your code here

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



unsigned char date[7];

/*
 * MAIN FUNCTION
 */
int i2c_rx8025t_test_rd(void)
{
	int fd;
	int ret;
	unsigned long u32_i;
	struct i2c_rdwr_ioctl_data e2prom_data;

	fd = open("/dev/i2c-3", O_RDWR);

	/*
	 * /dev/i2c-0����ע��i2c-dev.c������ģ�����һ���ɲ������������������ʹ��i2c-dev.c
	 * �ķ�ʽ����û�У�Ҳ����Ҫ����ڵ㡣
	 */
	if(fd<0)
	{
		perror("open error");
	}

	/*
	 * ��Ϊ����ʱ���У�������õ�2����ʼ�źţ��ֽڶ������У������Դ˽�
	 * e2prom_data.nmsgs����Ϊ2
	 */
	e2prom_data.nmsgs = 2;
	e2prom_data.msgs = (struct i2c_msg*)malloc(e2prom_data.nmsgs*sizeof(struct i2c_msg));
	if(!e2prom_data.msgs)
	{
		perror("e2prom_data.msgs malloc error");
		exit(1);
	}

	ioctl(fd, I2C_TIMEOUT, 1);/*��ʱʱ��*/
	ioctl(fd, I2C_RETRIES, 2);/*�ظ�����*/

	e2prom_data.nmsgs=1;
        (e2prom_data.msgs[0]).len=2; //1�� e2prom д��Ŀ��ĵ�ַ��1������ 
        (e2prom_data.msgs[0]).addr=0x50;//e2prom �豸��ַ
        (e2prom_data.msgs[0]).flags=0; //write
        (e2prom_data.msgs[0]).buf=(unsigned char*)malloc(2);
        (e2prom_data.msgs[0]).buf[0]=0x20;// e2prom д��Ŀ��ĵ�ַ
        (e2prom_data.msgs[0]).buf[1]=0x58;//the data to write 

	ret=ioctl(fd,I2C_RDWR,(unsigned long)&e2prom_data);
        if(ret<0)
        {
                perror("ioctl error1");
        }
	else
	{
		printf("write to EEPROM address=0x%02x,data=%02x ok\n",
				(e2prom_data.msgs[0]).buf[0],
				(e2prom_data.msgs[0]).buf[1]);
	}
        sleep(1);
	/******read data from e2prom*******/
        e2prom_data.nmsgs=2;
        (e2prom_data.msgs[0]).len=1; //e2prom Ŀ�����ݵĵ�ַ
        (e2prom_data.msgs[0]).addr=0x50; // e2prom �豸��ַ
        (e2prom_data.msgs[0]).flags=0;//write
        (e2prom_data.msgs[0]).buf[0]=0x20;//e2prom���ݵ�ַ
        (e2prom_data.msgs[1]).len=1;//����������
        (e2prom_data.msgs[1]).addr=0x50;// e2prom �豸��ַ 
        (e2prom_data.msgs[1]).flags=I2C_M_RD;//read
        (e2prom_data.msgs[1]).buf=(unsigned char*)malloc(1);//��ŷ���ֵ�ĵ�ַ��
        (e2prom_data.msgs[1]).buf[0]=0;//��ʼ��������

	ret=ioctl(fd,I2C_RDWR,(unsigned long)&e2prom_data);
        if(ret<0)
        {
                perror("ioctl error2");
        }
	else
	{
		printf("Read from EEPROM address=0x%02x,data=%02x ok\n",
				(e2prom_data.msgs[0]).buf[0],
				(e2prom_data.msgs[1]).buf[0]);
	}

	// free buff
	free((e2prom_data.msgs[0]).buf);
	free((e2prom_data.msgs[1]).buf);

	close(fd);

	return 0;
}



int main(int argc, char **argv)
{
	i2c_rx8025t_test_rd();
}

/**
 * Close the Doxygen group.
 * @}
 */

