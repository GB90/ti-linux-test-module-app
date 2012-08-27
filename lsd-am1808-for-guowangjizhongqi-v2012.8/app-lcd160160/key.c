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
#include "key.h"
#include "hello.h" 
#include "grlib.h"
#include "am1808_gpio.h"

//#define KEY_UP  0
//#define KEY_DOWN  5
//#define KEY_LEFT  2
//#define KEY_RIGHT  1
//#define KEY_OK  4
//#define KEY_CANCEL  3


// systick��ȫ�ּ������� 
unsigned long g_u32_systick_count = 0;
unsigned char g_u8_key_flag = 0;
unsigned char g_u8_key_num = 0;

// ���˵��±�
unsigned char g_u8_main_menu_index = 0;
// ����������ʾ�±�
unsigned char g_u8_main_local_data_index = 0;
// ��������ʾ�±�
unsigned char g_u8_main_measure_data_index = 0;
// �����趨�����±�
unsigned char g_u8_main_para_set_index = 0;
// �ն˹����±�
unsigned char g_u8_main_term_set_index = 0;

// ������������ϸ��ʾ�±�
unsigned char g_u8_main_measure_data_detial_index = 0;
// ѭ��ѡ�����±�
unsigned char g_u8_main_measure_data_detial_circle_display_index = 0;
// ѭ��ѡ���־
unsigned char g_u8_main_measure_data_detial_circle_display_select_flag = 0;
// ѭ�Ա�־
unsigned char g_u8_main_measure_data_detial_circle_display_flag = 0;

// ͨ�������±�
unsigned char g_u8_main_cmt_channal_set_index = 0;
// ѭ��ѡ�����±�
unsigned char g_u8_main_cmt_channal_set_circle_display_index = 0;
// ѭ��ѡ���־
unsigned char g_u8_main_cmt_channal_set_circle_display_select_flag = 0;
// ѭ�Ա�־
unsigned char g_u8_main_cmt_channal_set_circle_display_flag = 0;

// ̨���������鿴
unsigned char g_u8_main_area_meter_set_index = 0;

int  fd_buttons;  
unsigned char u8_old_buttons[6] = {1,1,1,1,1,1}; 
unsigned char u8_current_buttons[6] = {1,1,1,1,1,1};
unsigned char u8_up_buttions[6] = { 
				 KEY_UP,
				 KEY_DOWN,
				 KEY_LEFT,
				 KEY_RIGHT,
				 KEY_OK,
				 KEY_CANCEL};

//-----------------------------------------------------------------------------
//
// ��������  :  fn_systick_interrupt 
// ��������  :  systick�жϷ�����
//
// �������  :  ��
//
// ���ز���  :  ��
// 
//-----------------------------------------------------------------------------
#if 0
void fn_systick_interrupt(void)
{
    unsigned long u32_i;  
      unsigned long u8_key_change_cnt;
       
        // ʹ�� read ������ȡһ�鰴��ֵ��6 ����  
        if (read(fd_buttons, u8_current_buttons, sizeof u8_current_buttons) != sizeof u8_current_buttons) 
       { 
            perror("read buttons:"); 
            exit(1); 
        } 

       // ���������ȡ���İ���ֵ  
        for (u32_i = 0, u8_key_change_cnt = 0; u32_i < sizeof(u8_old_buttons)/ sizeof(u8_old_buttons[0]); u32_i++) 
	{ 
             if (u8_old_buttons[u32_i] != u8_current_buttons[u32_i]) 
             { 
                 u8_old_buttons[u32_i] = u8_current_buttons[u32_i]; 
                 // ��ӡ����ֵ����������������/̧���״̬  
                // printf("%skey %d is %s", u8_key_change_cnt? ", ": "", u32_i, u8_old_buttons[u32_i] == '0' ? "down" : "up"); 
                 u8_key_change_cnt++; 
		 if(u8_current_buttons[u32_i] == '0')
		{ 
                      g_u8_key_flag = 1;
		      g_u8_key_num = u32_i;
                }
             } 
        } 
        if (u8_key_change_cnt) { 
            // printf("\n"); 
        }  
}
#endif




void fn_systick_interrupt(void)
{
	int i;
	for(i = 0;i < 6;i++)
	{
		u8_old_buttons[i] = u8_current_buttons[i] ;
	}
	u8_current_buttons[0] = fn_get_am1808_gpio_value(KEY_UP);
	u8_current_buttons[1] = fn_get_am1808_gpio_value(KEY_DOWN);
	u8_current_buttons[2] = fn_get_am1808_gpio_value(KEY_LEFT);
	u8_current_buttons[3] = fn_get_am1808_gpio_value(KEY_RIGHT);
	u8_current_buttons[4] = fn_get_am1808_gpio_value(KEY_OK);
	u8_current_buttons[5] = fn_get_am1808_gpio_value(KEY_CANCEL);

	for(i = 0;i < 6;i++)
	{
		if((u8_current_buttons[i] == 1) && (u8_old_buttons[i] == 0))
		{	
			g_u8_key_flag = 1;
		        g_u8_key_num = u8_up_buttions[i];
			break;
		}
	}
#if 0
	printf("cur[0]=%d,[1]=%d,[2]=%d,[3]=%d,[4]=%d,[5]=%d\n",
		u8_current_buttons[0],u8_current_buttons[1],u8_current_buttons[2],
		u8_current_buttons[3],u8_current_buttons[4],u8_current_buttons[5]);
	printf("old[0]=%d,[1]=%d,[2]=%d,[3]=%d,[4]=%d,[5]=%d\n",
		u8_old_buttons[0],u8_old_buttons[1],u8_old_buttons[2],
		u8_old_buttons[3],u8_old_buttons[4],u8_old_buttons[5]);
#endif
}


//-----------------------------------------------------------------------------
//
// ��������  :  fn_key_process 
// ��������  :  ��������
//
// �������  :  ��
//
// ���ز���  :  ��
// 
//-----------------------------------------------------------------------------
void fn_key_process(void)
{
  
   usleep(50000); // 50ms
   fn_systick_interrupt(); 
   // ����а�������
   if(g_u8_key_flag == 1)
   {
       // ���������־
	   g_u8_key_flag = 0;
	   // �ж���ʲô����
	   switch (g_u8_key_num)
	   {
case KEY_UP:
		   // �������main����Ŀ¼��
		   if(g_u8_current_screen == M_SCREEN_MENU)
		   { 
		       fn_canvas_prev_index(&g_sMainMenuLocalDataDisplay,&g_u8_main_menu_index);
		   }
		   // ������ڱ��ؽ���������ʾ��ʱ��
		   else if(g_u8_current_screen == M_SCREEN_LOCALDATADISPLAY)
		   {
		        // ��Ϊ��һ��ֻ����ʾ6������
				if(g_u8_main_local_data_index >= 6)
				{
				   // �жϵ�ǰ�Ƿ��ڵڶ�����
				   WidgetRemove((tWidget *)&g_sMainLocalDataDisplaySecond);
				   WidgetAdd((tWidget *)&g_sMainLocalDataDisplayHead, 
				          (tWidget *)&g_sMainLocalDataDisplayFirst); 
				}

				// ���ӵ�һ���͵ڶ���������
				WidgetLink((tWidget *)&g_sMainLocalDataDisplayFirstCCurrent, 
				          (tWidget *)&g_sMainLocalDataDisplaySecondAVoltageAnagle);
				// ѡ����һ���������Ѿ���Ӧ�ķ��״���
				fn_canvas_prev_index(&g_sMainLocalDataDisplayFirstAVoltage,&g_u8_main_local_data_index);	
				// �ͷ�����
				WidgetUnLink((tWidget *)&g_sMainLocalDataDisplayFirstCCurrent, 
				          (tWidget *)&g_sMainLocalDataDisplaySecondAVoltageAnagle);
						  	  		    
				// ����������ڵڶ���������ʾ�ڶ���������
				if(g_u8_main_local_data_index >= 6)
				{
				   WidgetAdd((tWidget *)&g_sMainLocalDataDisplayHead, 
				          (tWidget *)&g_sMainLocalDataDisplaySecond); 
				}
		   }
		   // ���ڲ�����������ʾ
		   else if(g_u8_current_screen == M_SCREEN_MEASUREDATADISPLAY)
		   { 
		       fn_canvas_prev_index(&g_sMainMeasureDataDisplayPoint1,&g_u8_main_measure_data_index); 
		   }
		   // ���ڲ����趨
		   else if(g_u8_current_screen == M_SCREEN_PARAMETERSETTING)
		   { 
		       fn_canvas_prev_index(&g_sMainParaSetCmtChannelSet,&g_u8_main_para_set_index); 
		   }
		   // �����ն˹���
		   else if(g_u8_current_screen == M_SCREEN_TERMINALMANAGER)
		   { 
		       fn_canvas_prev_index(&g_sMainTermSetAMRInfo,&g_u8_main_term_set_index); 
		   }
		   // ���ڲ�������ϸ��ʾ����
		   else if(g_u8_current_screen == M_SCREEN_MEASUREDATADETIAL)
		   {
		        // �����趨ѭ��
				if(g_u8_main_measure_data_detial_circle_display_select_flag == 1)
				{
					// ѡ����һ���������Ѿ���Ӧ�ķ��״���
					fn_canvas_prev_index(&g_sMainMeasureDataDetialCircleConfirm,
								&g_u8_main_measure_data_detial_circle_display_index);	
				}
				// ������������·�
				else
				{
	                // ��Ϊ��һ��ֻ����ʾ6������
					if(g_u8_main_measure_data_detial_index >= 6)
					{
					   // �жϵ�ǰ�Ƿ��ڵڶ�����
					   WidgetRemove((tWidget *)&g_sMainMeasureDataDetialSecond);
					   WidgetAdd((tWidget *)&g_sMainMeasureDataDetialHead, 

					          (tWidget *)&g_sMainMeasureDataDetialFirst); 
					}
	
					// ���ӵ�һ���͵ڶ���������
					WidgetLink((tWidget *)&g_sMainMeasureDataDetialFYJ, 
					          (tWidget *)&g_sMainMeasureDataDetialFYF);
					// ѡ����һ���������Ѿ���Ӧ�ķ��״���
					fn_canvas_prev_index(&g_sMainMeasureDataDetialTime,&g_u8_main_measure_data_detial_index);	
					// �ͷ�����
					WidgetUnLink((tWidget *)&g_sMainMeasureDataDetialFYJ, 
					          (tWidget *)&g_sMainMeasureDataDetialFYF);
							  	  		    
					// ����������ڵڶ���������ʾ�ڶ���������
					if(g_u8_main_measure_data_detial_index >= 6)
					{
					   WidgetAdd((tWidget *)&g_sMainMeasureDataDetialHead, 
					          (tWidget *)&g_sMainMeasureDataDetialSecond); 
					}
				}		
		   }
		   else if(g_u8_current_screen == M_SCREEN_CMT_CHANNAL_SET)
		   {
		      	// ��Ϊ��һ��ֻ����ʾ6������
				if(g_u8_main_cmt_channal_set_index >= 6)
				{
				   // �жϵ�ǰ�Ƿ��ڵڶ�����
				   WidgetRemove((tWidget *)&g_sMainCmtChannalSetSecond);
				   WidgetAdd((tWidget *)&g_sMainCmtChannalSetHead, 
				          (tWidget *)&g_sMainCmtChannalSetFirst); 
				}

				// ���ӵ�һ���͵ڶ���������
				WidgetLink((tWidget *)&g_sMainCmtChannalSetUserName, 
				          (tWidget *)&g_sMainCmtChannalSetPasswd);
				// ѡ����һ���������Ѿ���Ӧ�ķ��״���
				fn_canvas_prev_index(&g_sMainCmtChannalSetHostIP,&g_u8_main_cmt_channal_set_index);	
				// �ͷ�����
				WidgetUnLink((tWidget *)&g_sMainCmtChannalSetUserName, 
				          (tWidget *)&g_sMainCmtChannalSetPasswd);
						  	  		    
				// ����������ڵڶ���������ʾ�ڶ���������
				if(g_u8_main_cmt_channal_set_index >= 6)
				{
				   WidgetAdd((tWidget *)&g_sMainCmtChannalSetHead, 
				          (tWidget *)&g_sMainCmtChannalSetSecond); 
				}
		   }
		   // ̨���������鿴
		   else if(g_u8_current_screen == M_SCREEN_AREA_METER_SET)
		   { 
		       fn_canvas_prev_index(&g_sMainAreaMeterSetPort1Interval,&g_u8_main_area_meter_set_index); 
		   }

		   break;
case KEY_DOWN:
           // �������main����Ŀ¼��
		   if(g_u8_current_screen == M_SCREEN_MENU)
		   { 
		       fn_canvas_next_index(&g_sMainMenuLocalDataDisplay,&g_u8_main_menu_index); 
		   }
           // ������ڱ��ؽ���������ʾ��ʱ��
		   else if(g_u8_current_screen == M_SCREEN_LOCALDATADISPLAY)
		   {
		        // ��Ϊ��һ��ֻ����ʾ6������
				if(g_u8_main_local_data_index >= 6)
				{
				   // �жϵ�ǰ�Ƿ��ڵڶ�����
				   WidgetRemove((tWidget *)&g_sMainLocalDataDisplaySecond);
				   WidgetAdd((tWidget *)&g_sMainLocalDataDisplayHead, 
				          (tWidget *)&g_sMainLocalDataDisplayFirst); 
				}

				// ���ӵ�һ���͵ڶ���������
				WidgetLink((tWidget *)&g_sMainLocalDataDisplayFirstCCurrent, 
				          (tWidget *)&g_sMainLocalDataDisplaySecondAVoltageAnagle);
				// ѡ����һ���������Ѿ���Ӧ�ķ��״���
				fn_canvas_next_index(&g_sMainLocalDataDisplayFirstAVoltage,&g_u8_main_local_data_index);	
				// �ͷ�����
				WidgetUnLink((tWidget *)&g_sMainLocalDataDisplayFirstCCurrent, 
				          (tWidget *)&g_sMainLocalDataDisplaySecondAVoltageAnagle);
						  	  		    
				// ����������ڵڶ���������ʾ�ڶ���������
				if(g_u8_main_local_data_index >= 6)
				{
				   WidgetAdd((tWidget *)&g_sMainLocalDataDisplayHead, 
				          (tWidget *)&g_sMainLocalDataDisplaySecond); 
				}
		   }
		   // ���ڲ�����������ʾ
		   else if(g_u8_current_screen == M_SCREEN_MEASUREDATADISPLAY)
		   { 
		       fn_canvas_next_index(&g_sMainMeasureDataDisplayPoint1,&g_u8_main_measure_data_index); 
		   }
		   // ���ڲ����鿴
		   else if(g_u8_current_screen == M_SCREEN_PARAMETERSETTING)
		   { 
		       fn_canvas_next_index(&g_sMainParaSetCmtChannelSet,&g_u8_main_para_set_index); 
		   }
		   // �����ն˹���
		   else if(g_u8_current_screen == M_SCREEN_TERMINALMANAGER)
		   { 
		       fn_canvas_next_index(&g_sMainTermSetAMRInfo,&g_u8_main_term_set_index); 
		   }
		   // ���ڲ�������ϸ��ʾ����
		   else if(g_u8_current_screen == M_SCREEN_MEASUREDATADETIAL)
		   {
		        // �����趨ѭ��
				if(g_u8_main_measure_data_detial_circle_display_select_flag == 1)
				{
					// ѡ����һ���������Ѿ���Ӧ�ķ��״���
					fn_canvas_next_index(&g_sMainMeasureDataDetialCircleConfirm,
								&g_u8_main_measure_data_detial_circle_display_index);	
				}
				// ������������·�
				else
				{
				    // ��Ϊ��һ��ֻ����ʾ6������
					if(g_u8_main_measure_data_detial_index >= 6)
					{
					   // �жϵ�ǰ�Ƿ��ڵڶ�����
					   WidgetRemove((tWidget *)&g_sMainMeasureDataDetialSecond);
					   WidgetAdd((tWidget *)&g_sMainMeasureDataDetialHead, 
					          (tWidget *)&g_sMainMeasureDataDetialFirst); 
					}
	
					// ���ӵ�һ���͵ڶ���������
					WidgetLink((tWidget *)&g_sMainMeasureDataDetialFYJ, 
					          (tWidget *)&g_sMainMeasureDataDetialFYF);
					// ѡ����һ���������Ѿ���Ӧ�ķ��״���
					fn_canvas_next_index(&g_sMainMeasureDataDetialTime,&g_u8_main_measure_data_detial_index);	
					// �ͷ�����
					WidgetUnLink((tWidget *)&g_sMainMeasureDataDetialFYJ, 
					          (tWidget *)&g_sMainMeasureDataDetialFYF);
							  	  		    
					// ����������ڵڶ���������ʾ�ڶ���������
					if(g_u8_main_measure_data_detial_index >= 6)
					{
					   WidgetAdd((tWidget *)&g_sMainMeasureDataDetialHead, 
					          (tWidget *)&g_sMainMeasureDataDetialSecond); 
					}
				}
		   }
		   else if(g_u8_current_screen == M_SCREEN_CMT_CHANNAL_SET)
		   {
		      	// ��Ϊ��һ��ֻ����ʾ6������
				if(g_u8_main_cmt_channal_set_index >= 6)
				{
				   // �жϵ�ǰ�Ƿ��ڵڶ�����
				   WidgetRemove((tWidget *)&g_sMainCmtChannalSetSecond);
				   WidgetAdd((tWidget *)&g_sMainCmtChannalSetHead, 
				          (tWidget *)&g_sMainCmtChannalSetFirst); 
				}

				// ���ӵ�һ���͵ڶ���������
				WidgetLink((tWidget *)&g_sMainCmtChannalSetUserName, 
				          (tWidget *)&g_sMainCmtChannalSetPasswd);
				// ѡ����һ���������Ѿ���Ӧ�ķ��״���
				fn_canvas_next_index(&g_sMainCmtChannalSetHostIP,&g_u8_main_cmt_channal_set_index);	
				// �ͷ�����
				WidgetUnLink((tWidget *)&g_sMainCmtChannalSetUserName, 
				          (tWidget *)&g_sMainCmtChannalSetPasswd);
						  	  		    
				// ����������ڵڶ���������ʾ�ڶ���������
				if(g_u8_main_cmt_channal_set_index >= 6)
				{
				   WidgetAdd((tWidget *)&g_sMainCmtChannalSetHead, 
				          (tWidget *)&g_sMainCmtChannalSetSecond); 
				}
		   }
		   // ̨���������鿴
		   else if(g_u8_current_screen == M_SCREEN_AREA_METER_SET)
		   { 
		       fn_canvas_next_index(&g_sMainAreaMeterSetPort1Interval,&g_u8_main_area_meter_set_index); 
		   }

		   break;
case KEY_OK:
		   // �������main����Ŀ¼�£���ʱ����ok������������е��Ӳ˵���
		   if(g_u8_current_screen == M_SCREEN_MENU)
		   {
		      // ���ؽ���������ʾ
			  if(g_u8_main_menu_index == 0)
			  {
			   	  g_u8_current_screen = M_SCREEN_LOCALDATADISPLAY;
				  WidgetRemove((tWidget *)&g_sMainMenu);
				  WidgetAdd((tWidget *)&g_sMain, (tWidget *)&g_sMainLocalDataDisplay);
			  }
			  // ������������ʾ
			  else if(g_u8_main_menu_index == 1)
			  {
			   	  g_u8_current_screen = M_SCREEN_MEASUREDATADISPLAY;
				  WidgetRemove((tWidget *)&g_sMainMenu);
				  WidgetAdd((tWidget *)&g_sMain, (tWidget *)&g_sMainMeasureDataDisplay);
			  }
			  // �������úͲ鿴
			  else if (g_u8_main_menu_index == 2)
			  {
			      g_u8_current_screen = M_SCREEN_PARAMETERSETTING;
				  WidgetRemove((tWidget *)&g_sMainMenu);
				  WidgetAdd((tWidget *)&g_sMain, (tWidget *)&g_sMainParaSet);
			  }
			  // �ն˹�����ά��
			  else if (g_u8_main_menu_index == 3)
			  {
			      g_u8_current_screen = M_SCREEN_TERMINALMANAGER;
				  WidgetRemove((tWidget *)&g_sMainMenu);
				  WidgetAdd((tWidget *)&g_sMain, (tWidget *)&g_sMainTermSet);
			  }
		   }
		   // ������ڿ�ʼ���棬��ʱ����ok������������˵�
		   else if(g_u8_current_screen == M_SCREEN_FIRST_FACE)
		   {
		      g_u8_current_screen = M_SCREEN_MENU;
			  WidgetRemove((tWidget *)&g_sMainFirstFace);
			  WidgetAdd((tWidget *)&g_sMain, (tWidget *)&g_sMainMenu);
		   }
		   // ������ڲ�����������ʾ���棬�������Ҫ��ʾ�Ĳ�������ϸ��ʾ����
		   else if(g_u8_current_screen == M_SCREEN_MEASUREDATADISPLAY)
		   {
		      // ������ʾ����
			  g_u8_current_screen = M_SCREEN_MEASUREDATADETIAL;
			  WidgetRemove((tWidget *)&g_sMainMeasureDataDisplay);
			  WidgetAdd((tWidget *)&g_sMain, (tWidget *)&g_sMainMeasureDataDetial);
			  // �趨��ʾ��ֵ
			  g_sMainMeasureDataDetialZYJ.pFont = (const tFont*)&g_f64_measure_data_point_zyj[g_u8_main_measure_data_index];
  			  g_sMainMeasureDataDetialZYF.pFont = (const tFont*)&g_f64_measure_data_point_zyf[g_u8_main_measure_data_index];
			  g_sMainMeasureDataDetialZYP.pFont = (const tFont*)&g_f64_measure_data_point_zyp[g_u8_main_measure_data_index];
			  g_sMainMeasureDataDetialZYG.pFont = (const tFont*)&g_f64_measure_data_point_zyg[g_u8_main_measure_data_index];
			  g_sMainMeasureDataDetialFYJ.pFont = (const tFont*)&g_f64_measure_data_point_fyj[g_u8_main_measure_data_index];
			  g_sMainMeasureDataDetialFYF.pFont = (const tFont*)&g_f64_measure_data_point_fyf[g_u8_main_measure_data_index];
			  g_sMainMeasureDataDetialFYP.pFont = (const tFont*)&g_f64_measure_data_point_fyp[g_u8_main_measure_data_index];
			  g_sMainMeasureDataDetialFYG.pFont = (const tFont*)&g_f64_measure_data_point_fyg[g_u8_main_measure_data_index];
			  g_sMainMeasureDataDetialTime.pcText = (const char*)(g_pu8_measure_data_point_time[g_u8_main_measure_data_index]);
		   }
		   // ����ѭ����ʾ
		   else if(g_u8_current_screen == M_SCREEN_MEASUREDATADETIAL)
		   {
		       if(g_u8_main_measure_data_detial_circle_display_select_flag == 0)
			   {
			       g_u8_main_measure_data_detial_circle_display_select_flag = 1;

				   // ���ӵ�һ���͵ڶ���������
				   WidgetLink((tWidget *)&g_sMainMeasureDataDetialHead, 
					          (tWidget *)&g_sMainMeasureDataDetialCircleGround); 
			   }
			   else if(g_u8_main_measure_data_detial_circle_display_select_flag == 1)
			   {
			      g_u8_main_measure_data_detial_circle_display_flag = 
				             (g_u8_main_measure_data_detial_circle_display_index?0:1); 
				  // ���ӵ�һ���͵ڶ���������
				  WidgetUnLink((tWidget *)&g_sMainMeasureDataDetialHead, 
					          (tWidget *)&g_sMainMeasureDataDetialCircleGround); 
				  g_u8_main_measure_data_detial_circle_display_select_flag = 0;
			   }
		   }
		   // �������úͲ鿴
		   else if(g_u8_current_screen == M_SCREEN_PARAMETERSETTING)
		   {
		      // ͨѶͨ������
			  if(g_u8_main_para_set_index == 0)
			  {
			     g_u8_current_screen = M_SCREEN_CMT_CHANNAL_SET;
				 WidgetRemove((tWidget *)&g_sMainParaSet);
				 WidgetAdd((tWidget *)&g_sMain, (tWidget *)&g_sMainCmtChannalSet);
			  }
			  // ̨���������鿴
			  if(g_u8_main_para_set_index == 1)
			  {
			     g_u8_current_screen = M_SCREEN_AREA_METER_SET;
				 WidgetRemove((tWidget *)&g_sMainParaSet);
				 WidgetAdd((tWidget *)&g_sMain, (tWidget *)&g_sMainAreaMeterSet);
			  }
		   }
		   else if(g_u8_current_screen == M_SCREEN_TERMINALMANAGER)
		   {
		      if(g_u8_main_term_set_index == 0)
			  {
			      g_u8_current_screen = M_SCREEN_AMR_INFO;
				  WidgetRemove((tWidget *)&g_sMainTermSet);
				  WidgetAdd((tWidget *)&g_sMain, (tWidget *)&g_sMainAMRInfo);
			  } 
		   }
		   break;
case KEY_CANCEL:
		   // �ӱ��ز���������ʾ����
		   if(g_u8_current_screen == M_SCREEN_LOCALDATADISPLAY)
		   {
                g_u8_current_screen = M_SCREEN_MENU; 
				WidgetRemove((tWidget *)&g_sMainLocalDataDisplay);
				WidgetAdd((tWidget *)&g_sMain, (tWidget *)&g_sMainMenu);
		   }
		   // �Ӳ�����������ʾ����
		   else if(g_u8_current_screen == M_SCREEN_MEASUREDATADISPLAY)
		   {
		        g_u8_current_screen = M_SCREEN_MENU;
				WidgetRemove((tWidget *)&g_sMainMeasureDataDisplay);
				WidgetAdd((tWidget *)&g_sMain, (tWidget *)&g_sMainMenu);
		   }
		   // �Ӳ����鿴��ʾ����
		   else if(g_u8_current_screen == M_SCREEN_PARAMETERSETTING)
		   {
		        g_u8_current_screen = M_SCREEN_MENU;
				WidgetRemove((tWidget *)&g_sMainParaSet);
				WidgetAdd((tWidget *)&g_sMain, (tWidget *)&g_sMainMenu);
		   }
		   // ���ն˹�����ʾ����
		   else if(g_u8_current_screen == M_SCREEN_TERMINALMANAGER)
		   {
		        g_u8_current_screen = M_SCREEN_MENU;
				WidgetRemove((tWidget *)&g_sMainTermSet);
				WidgetAdd((tWidget *)&g_sMain, (tWidget *)&g_sMainMenu);
		   }
		   // �����˵���ʾ����
		   else if(g_u8_current_screen == M_SCREEN_MENU)
		   {
		      g_u8_current_screen = M_SCREEN_FIRST_FACE;
			  WidgetRemove((tWidget *)&g_sMainMenu);
			  WidgetAdd((tWidget *)&g_sMain, (tWidget *)&g_sMainFirstFace);
		   }
		   // ������������ϸ��ʾ
		   else if(g_u8_current_screen == M_SCREEN_MEASUREDATADETIAL)
		   {
		      // �������ѡ��ѭ�Ա�־��ʱ�򣬰���ȡ��������
			  if(g_u8_main_measure_data_detial_circle_display_select_flag == 1)
			  {
			      // �Ͽ�ѭ��ѡ���
				  WidgetUnLink((tWidget *)&g_sMainMeasureDataDetialHead, 
					          (tWidget *)&g_sMainMeasureDataDetialCircleGround);
				  // ���ѡ��ѭ����ʾ��־���� 
				  g_u8_main_measure_data_detial_circle_display_select_flag = 0;
			  }
			  else
			  {
				  // ���Ե�������ʾ����
				  g_u8_current_screen = M_SCREEN_MEASUREDATADISPLAY;
				  WidgetRemove((tWidget *)&g_sMainMeasureDataDetial);
				  WidgetAdd((tWidget *)&g_sMain, (tWidget *)&g_sMainMeasureDataDisplay);
			  }  
		   }
		   // ͨѶͨ������
		   else if(g_u8_current_screen == M_SCREEN_CMT_CHANNAL_SET)
		   {
		      g_u8_current_screen = M_SCREEN_PARAMETERSETTING;
			  WidgetRemove((tWidget *)&g_sMainCmtChannalSet);
			  WidgetAdd((tWidget *)&g_sMain, (tWidget *)&g_sMainParaSet);
		   }
		   // ̨���������鿴
		   else if(g_u8_current_screen == M_SCREEN_AREA_METER_SET)
		   { 
		        g_u8_current_screen = M_SCREEN_PARAMETERSETTING;
				WidgetRemove((tWidget *)&g_sMainAreaMeterSet);
				WidgetAdd((tWidget *)&g_sMain, (tWidget *)&g_sMainParaSet);
		   }
		   else if(g_u8_current_screen == M_SCREEN_AMR_INFO)
		   {
		         g_u8_current_screen = M_SCREEN_TERMINALMANAGER;
				 WidgetRemove((tWidget *)&g_sMainAMRInfo);
				 WidgetAdd((tWidget *)&g_sMain, (tWidget *)&g_sMainTermSet); 
		   }
		   break;
		   default:
		   break;
	   }
	   WidgetPaint(WIDGET_ROOT);
   }    
}

//-----------------------------------------------------------------------------
//
// ��������  :  fn_systick_init 
// ��������  :  systick��ʼ��
//
// �������  :  ��
//
// ���ز���  :  ��
// 
//-----------------------------------------------------------------------------
void fn_systick_init(void)
{

}

//-----------------------------------------------------------------------------
//
// ��������  :  fn_key_init 
// ��������  :  ������ʼ��
//
// �������  :  ��
//
// ���ز���  :  ��
// 
//-----------------------------------------------------------------------------
void fn_key_init(void)
{
        // �򿪰����豸/dev/buttons  
     fd_buttons = open("/dev/buttons", 0); 
     if (fd_buttons < 0) { 
         // ��ʧ�����˳�  
         perror("open device buttons"); 
         exit(1); 
     } 
}
