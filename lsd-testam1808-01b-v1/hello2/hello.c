#include "grlib.h"
#include "widget.h"
#include "canvas.h"
#include "pushbutton.h"
#include "formike128x128x16.h"
#include "gb_print.h"
#include "key.h"   
#include "hello.h" 

unsigned char g_u8_current_screen = M_SCREEN_FIRST_FACE;
//-----------------------------------------------------------------------------
// ��0�� ��ʼ����
//-----------------------------------------------------------------------------
unsigned long g_u32_year = 2045;	     // ��ǰ����--��
unsigned long g_u32_month = 10;			 // ��ǰ����--��
unsigned long g_u32_date = 20;			 // ��ǰ����--��
unsigned long g_u32_hour = 16;			 // ��ǰʱ��--ʱ
unsigned long g_u32_minute = 15;		 // ��ǰʱ��--��
unsigned long g_u32_second = 1;			 // ��ǰʱ��--��
unsigned char g_pu8_date[] = "yyyy-mm-dd"; // ��ǰ����--�ַ���
unsigned char g_pu8_time[] = "hh:mm:ss";   // ��ǰʱ��--�ַ���
//-----------------------------------------------------------------------------
// �ڶ��� ���ؽ���������ʾ
//-----------------------------------------------------------------------------
double g_f64_local_data_a_voltage = 0.02;	     // A���ѹ
double g_f64_local_data_b_voltage = 221.15;		 // B���ѹ
double g_f64_local_data_c_voltage = -240.03;	 // C���ѹ
double g_f64_local_data_a_current = -1.23;		 // A�����
double g_f64_local_data_b_current = -0.21;		 // B�����
double g_f64_local_data_c_current = 0.02;		 // C�����
double g_f64_local_data_a_voltage_angle = 2.10;	 // A���ѹ���
double g_f64_local_data_b_voltage_angle = -40.8; // B���ѹ���
double g_f64_local_data_c_voltage_angle = -30.6; // C���ѹ���
//-----------------------------------------------------------------------------
// ������ ������������ϸ��ʾ
//-----------------------------------------------------------------------------
unsigned char g_pu8_measure_data_point_num[] = "������n";
unsigned char g_pu8_measure_data_point_time_hour[M_MEASURE_DATA_POINT_NUM] = {12,12,12,12,12,12};	   // ������--����ʱ��--ʱ
unsigned char g_pu8_measure_data_point_time_minute[M_MEASURE_DATA_POINT_NUM] = {12,10,9,8,7,6};  // ������--����ʱ��--��
unsigned char g_pu8_measure_data_point_time[M_MEASURE_DATA_POINT_NUM][8] = {"hh:mm","hh:mm","hh:mm"
									,"hh:mm","hh:mm","hh:mm"}; // ������--����ʱ��--�ַ���
double g_f64_measure_data_point_zyj[M_MEASURE_DATA_POINT_NUM] = {123456.78,
								159.66,15.06,1.456,0.123,0.015};	  // ������--�����й������
double g_f64_measure_data_point_zyf[M_MEASURE_DATA_POINT_NUM] = {123456.78,
								159.66,15.06,1.456,0.123,0.015};	  // ������--�����й������
double g_f64_measure_data_point_zyp[M_MEASURE_DATA_POINT_NUM] = {123456.78,
								159.66,15.06,1.456,0.123,0.015};	  // ������--�����й�ƽ����
double g_f64_measure_data_point_zyg[M_MEASURE_DATA_POINT_NUM] = {123456.78,
								159.66,15.06,1.456,0.123,0.015};	  // ������--�����й��ȵ���
double g_f64_measure_data_point_fyj[M_MEASURE_DATA_POINT_NUM] = {123456.78,
								159.66,15.06,1.456,0.123,0.015};	  // ������--�����й������
double g_f64_measure_data_point_fyf[M_MEASURE_DATA_POINT_NUM] = {123456.78,
								159.66,15.06,1.456,0.123,0.015};	  // ������--�����й������
double g_f64_measure_data_point_fyp[M_MEASURE_DATA_POINT_NUM] = {123456.78,
								159.66,15.06,1.456,0.123,0.015};	  // ������--�����й�ƽ����
double g_f64_measure_data_point_fyg[M_MEASURE_DATA_POINT_NUM] = {123456.78,
								159.66,15.06,1.456,0.123,0.015};	  // ������--�����й��ȵ���
//-----------------------------------------------------------------------------
// ������ ͨѶͨ������
//-----------------------------------------------------------------------------
unsigned long g_u32_cmt_channal_set_host_ip = (((unsigned long)192<<24)|(168<<16)|(14<<8)|20);
unsigned long g_u32_cmt_channal_set_local_ip = (((unsigned long)192<<24)|(168<<16)|(14<<8)|21);
unsigned long g_u32_cmt_channal_set_term_ip = (((unsigned long)192<<24)|(168<<16)|(14<<8)|22);
double g_f64_cmt_channal_set_port_num = 5001;
unsigned char g_pu8_cmt_channal_set_apn[10] = "CMNET";
unsigned char g_pu8_cmt_channal_set_username[10] = "yuge";
unsigned char g_pu8_cmt_channal_set_passwd[10] = "000000";
double g_f64_cmt_channal_set_period = 0.3; // ��λms 

//-----------------------------------------------------------------------------
// ������ ̨���������鿴
//-----------------------------------------------------------------------------
double g_f64_area_meter_set_port1_interval = 0.3; // ��λms 
double g_f64_area_meter_set_port2_interval = 0.5; // ��λms 
double g_f64_area_meter_set_port3_interval = 0.4; // ��λms 

//-----------------------------------------------------------------------------
// �ھ��� �������汾
//-----------------------------------------------------------------------------
unsigned char g_pu8_amr_info_soft_version[20] = "10.03.26.09";

//void OnButtonPress(tWidget *pWidget);
//void OnSwUpdateButtonPress(tWidget *pWidget);

// WIDGET_ROOT
//      |
// g_sBackground--g_sHeading 
//                        |--> g_sHeadSignal --> g_sHeadCmtGscWay --> 
//                             g_sHeadWarningFlag --> g_sHeadStandard --> 
//                             g_sHeadShowMesData --> g_sHeadCurrentTime
//              --g_sMain
//                 |--> g_sMainFirstFace
//                       |--> g_sMainFirstFaceHead --> g_sMainFirstFaceDate --> g_sMainFirstFaceTime 
//                 |--> g_sMainMenu 
//                       |-->  g_sMainMenuHead --> g_sMainMenuLocalDataDisplay -->
//                             g_sMainMenuMeasureDataDisplay --> g_sMainMenuParameterSetting -->
//                             g_sMainMenuTerminalManager
//                 |--g_sMainLocalDataDisplay
//                       |--> g_sMainLocalDataDisplayHead |--> g_sMainLocalDataDisplayFirst 
//                                                                |--> g_sMainLocalDataDisplayFirstAVoltage --> 
//                                                                     g_sMainLocalDataDisplayFirstBVoltage -->
//                                                                     g_sMainLocalDataDisplayFirstCVoltage -->
//                                                                     g_sMainLocalDataDisplayFirstACurrent --> 
//                                                                     g_sMainLocalDataDisplayFirstBCurrent --> 
//                                                                     g_sMainLocalDataDisplayFirstCCurrent 
//                                                                        |--> g_sMainLocalDataDisplayFirstNum   
//                                                         |--> g_sMainLocalDataDisplaySecond 
//                                                                |--> g_sMainLocalDataDisplayFirstAVoltageAnagle --> 
//                                                                     g_sMainLocalDataDisplayFirstBVoltageAnagle -->
//                                                                     g_sMainLocalDataDisplayFirstCVoltageAnagle
//                                                                        |--> g_sMainLocalDataDisplaySecondNum
//                 |-->g_sMainMeasureDataDisplay
//                       |--> g_sMainMeasureDataDisplayHead --> g_sMainMeasureDataDisplayPoint1 -->
//                                                              g_sMainMeasureDataDisplayPoint2 --> 
//                                                              g_sMainMeasureDataDisplayPoint3 --> 
//                                                              g_sMainMeasureDataDisplayPoint4 --> 
//                                                              g_sMainMeasureDataDisplayPoint5 --> 
//                                                              g_sMainMeasureDataDisplayPoint6
//                                                                |--> g_sMainMeasureDataDisplayNum 
//                 |-->g_sMainParaSet
//                       |--> g_sMainParaSetHead --> g_sMainParaSetCmtChannelSet -->
//                                                   g_sMainParaSetAreaMeterSet --> 
//                                                   g_sMainParaSetCentralMeterSet --> 
//                                                   g_sMainParaSetTimeSet --> 
//                                                   g_sMainParaSetPasswdSet --> 
//                                                   g_sMainParaSetNumberSet 
//                                                     |--> g_sMainParaSetNum 
//                |-->g_sMainMeasureDataDetial
//                     |--> g_sMainMeasureDataDetialHead |--> g_sMainMeasureDataDetialFirst
//                                                               |--> g_sMainMeasureDataDetialTimeInfo -->
//                                                                    g_sMainMeasureDataDetialTime -->
//                                                                    g_sMainMeasureDataDetialZYJ -->
//                                                                    g_sMainMeasureDataDetialZYF -->
//                                                                    g_sMainMeasureDataDetialZYP -->
//                                                                    g_sMainMeasureDataDetialZYG -->
//                                                                    g_sMainMeasureDataDetialFYJ 
//                                                                      |-->g_sMainMeasureDataDetialFirstNum 
//                                                       |--> g_sMainMeasureDataDetialSecond 
//                                                                |--> g_sMainMeasureDataDetialFYF -->
//                                                                     g_sMainMeasureDataDetialFYP -->
//                                                                     g_sMainMeasureDataDetialFYG 
//                                                                         |-->g_sMainMeasureDataDetialSecondNum
                                                             
//              -->g_sMainInfoGround
//                       |--> g_sMainInfo

//-----------------------------------------------------------------------------
// ���屳��
//-----------------------------------------------------------------------------
//���屳��
Canvas(g_sBackground, WIDGET_ROOT, 0, &g_sHeading,
       &g_sFormike128x128x16, 0, 0, 160, 160,
       CANVAS_STYLE_FILL | PB_STYLE_OUTLINE, ClrWhite, ClrBlack, ClrBlack, 0, 0, 0, 0);

//-----------------------------------------------------------------------------
// ������Ϣ��
//-----------------------------------------------------------------------------
// ��������Ϣ�������ֲ���
Canvas(g_sHeading, &g_sBackground, &g_sMain, &g_sHeadSignal,
       &g_sFormike128x128x16, 0, 0, 160, 24,
       (CANVAS_STYLE_FILL | PB_STYLE_OUTLINE),
       ClrWhite, ClrBlack, ClrBlack, 0, 0, 0, 0);

// �ź�ǿ��
Canvas(g_sHeadSignal, &g_sHeading, &g_sHeadCmtGscWay, 0,
       &g_sFormike128x128x16, 1, 2, 20, 20,
       (CANVAS_STYLE_IMG ),
       ClrWhite, ClrBlack, ClrBlack, &g_sFontMsyh16, 0, g_pucsignal20x20, 0);

// ͨ�ŷ�ʽѡ�� G S C 
Canvas(g_sHeadCmtGscWay, &g_sHeading, &g_sHeadWarningFlag, 0,
       &g_sFormike128x128x16, 22, 2, 20, 20,
       (CANVAS_STYLE_TEXT | CANVAS_STYLE_TEXT_TOP),
       ClrWhite, ClrBlack, ClrBlack, &g_sFontCmss26, "G", 0, 0);

// �쳣����
CircularButton(g_sHeadWarningFlag,&g_sHeading, &g_sHeadStandard, 0,
               &g_sFormike128x128x16, 52, 11, 9,
               PB_STYLE_FILL | PB_STYLE_OUTLINE | PB_STYLE_TEXT | CANVAS_STYLE_TEXT_LEFT,
               ClrWhite, ClrWhite, ClrBlack, ClrBlack,
               &g_sFontCmss16b, "!", 0, 0, 0, 0, 0);
// ��׼
Canvas(g_sHeadStandard, &g_sHeading, &g_sHeadShowMesData, 0,
       &g_sFormike128x128x16, 66, 2, 28, 20,
       (CANVAS_STYLE_FILL | CANVAS_STYLE_OUTLINE | CANVAS_STYLE_TEXT | CANVAS_STYLE_TEXT_TOP),
       ClrWhite, ClrBlack, ClrBlack, &g_sFontCmss18, "Std", 0, 0);

// ����ʾ�ڼ�������
Canvas(g_sHeadShowMesData, &g_sHeading, &g_sHeadCurrentTime, 0,
       &g_sFormike128x128x16, 96, 2, 20, 20,
       (CANVAS_STYLE_FILL | CANVAS_STYLE_OUTLINE | CANVAS_STYLE_TEXT),
       ClrWhite, ClrBlack, ClrBlack, &g_sFontCmss18b, "01", 0, 0);

// ��ǰʱ��
Canvas(g_sHeadCurrentTime, &g_sHeading, 0, 0,
       &g_sFormike128x128x16, 122, 2, 37, 20,
       (CANVAS_STYLE_FILL | CANVAS_STYLE_TEXT | CANVAS_STYLE_TEXT_BOTTOM),
       ClrWhite, ClrBlack, ClrBlack, &g_sFontCmss12b, "12:00", 0, 0);

//-----------------------------------------------------------------------------
// ��Ҫ��ʾ����
//-----------------------------------------------------------------------------
// ��Ҫ��ʾ����
Canvas(g_sMain, &g_sBackground, &g_sMainInfoGround, &g_sMainFirstFace,
       &g_sFormike128x128x16, 1, 25, 158, 134,
       (CANVAS_STYLE_FILL),
       ClrWhite, ClrBlack, ClrBlack, 0, 0, 0, 0);

// ���ڳ���״̬����ʾ����
Canvas(g_sMainInfoGround, &g_sBackground, 0,&g_sMainInfo,
       &g_sFormike128x128x16, 0, 142, 160, 18,
       (CANVAS_STYLE_OUTLINE | CANVAS_STYLE_FILL),
       ClrWhite, 0, ClrBlack, 0, 0, 0, OnPaintMainCharacter);

// ���ڳ���״̬����ʾ״̬
Canvas(g_sMainInfo, &g_sMainInfoGround, 0,0,
       &g_sFormike128x128x16, 1, 143, 158, 16,
       (CANVAS_STYLE_FILL | CANVAS_STYLE_APP_DRAWN),
       ClrWhite, 0, ClrBlack, 0, "�ն����ڳ���..", 0, OnPaintMainCharacter);


//-----------------------------------------------------------------------------
// ��0�� ��ʼ����
//-----------------------------------------------------------------------------
// ��0�� ��ʼ����
Canvas(g_sMainFirstFace, &g_sMain, 0, &g_sMainFirstFaceHead,
       &g_sFormike128x128x16, 1, 25, 158, 134,
       (CANVAS_STYLE_FILL),
       ClrWhite, ClrBlack, ClrBlack, 0, 0, 0, 0);

Canvas(g_sMainFirstFaceHead, &g_sMainFirstFace, &g_sMainFirstFaceDate,0,
       &g_sFormike128x128x16, 1+8*3, 25, 134, 16,
       (CANVAS_STYLE_FILL | CANVAS_STYLE_APP_DRAWN),
       ClrWhite, 0, ClrBlack, 0, "��ѹ����������", 0, OnPaintMainCharacter);

Canvas(g_sMainFirstFaceDate, &g_sMainFirstFace, &g_sMainFirstFaceTime,0,
       &g_sFormike128x128x16, 1+8*5, 25+16+1+16+1, 5*16, 16,
       (CANVAS_STYLE_FILL | CANVAS_STYLE_APP_DRAWN),
       ClrWhite, 0, ClrBlack, 0, (const char*)g_pu8_date, 0, OnPaintMainFirstFaceDate);

Canvas(g_sMainFirstFaceTime, &g_sMainFirstFace, 0,0,
       &g_sFormike128x128x16, 1+8*6, 25+16+1+16+1+16+1, 4*16, 16,
       (CANVAS_STYLE_FILL | CANVAS_STYLE_APP_DRAWN),
       ClrWhite, 0, ClrBlack, 0, (const char*)g_pu8_time, 0, OnPaintMainFirstFaceTime);

//-----------------------------------------------------------------------------
// ��һ�� ���˵�
//-----------------------------------------------------------------------------
// ��һ�� ���˵�
Canvas(g_sMainMenu, &g_sMain, 0, &g_sMainMenuHead,
       &g_sFormike128x128x16, 1, 25, 158, 134,
       (CANVAS_STYLE_FILL),
       ClrWhite, ClrBlack, ClrBlack, 0, 0, 0, 0);

Canvas(g_sMainMenuHead, &g_sMainMenu, &g_sMainMenuLocalDataDisplay,0,
       &g_sFormike128x128x16, 1+8*6, 25, 16*3, 16,
       (CANVAS_STYLE_FILL | CANVAS_STYLE_APP_DRAWN),
       ClrWhite, 0, ClrBlack, 0, "���˵�", 0, OnPaintMainCharacter);

Canvas(g_sMainMenuLocalDataDisplay, &g_sMainMenu, &g_sMainMenuMeasureDataDisplay,0,
       &g_sFormike128x128x16, 1+16, 42, 8*16, 16,
       (CANVAS_STYLE_FILL | CANVAS_STYLE_APP_DRAWN | CANVAS_STYLE_REVERSE_COLOR),
       ClrWhite, 0, ClrBlack, 0, "���ؽ���������ʾ", 0, OnPaintMainCharacter);

Canvas(g_sMainMenuMeasureDataDisplay, &g_sMainMenu, &g_sMainMenuParameterSetting,0,
       &g_sFormike128x128x16, 1+24, 59, 7*16, 16,
       (CANVAS_STYLE_FILL | CANVAS_STYLE_APP_DRAWN),
       ClrWhite, 0, ClrBlack, 0, "������������ʾ", 0, OnPaintMainCharacter);

Canvas(g_sMainMenuParameterSetting, &g_sMainMenu, &g_sMainMenuTerminalManager, 0,
       &g_sFormike128x128x16, 1+24, 76, 7*16, 16,
       (CANVAS_STYLE_FILL | CANVAS_STYLE_APP_DRAWN),
       ClrWhite, 0, ClrBlack, 0, "��ز����Ĳ鿴", 0, OnPaintMainCharacter);

Canvas(g_sMainMenuTerminalManager, &g_sMainMenu, 0, 0,
       &g_sFormike128x128x16, 1+24, 93, 7*16, 16,
       (CANVAS_STYLE_FILL | CANVAS_STYLE_APP_DRAWN),
       ClrWhite, 0, ClrBlack, 0, "�ն˹�����ά��", 0, OnPaintMainCharacter);

//-----------------------------------------------------------------------------
// �ڶ��� ���ؽ���������ʾ
//-----------------------------------------------------------------------------
// �ڶ��� ���ؽ���������ʾ
Canvas(g_sMainLocalDataDisplay, &g_sMain, 0, &g_sMainLocalDataDisplayHead,
       &g_sFormike128x128x16, 1, 25, 157, 134,
       (CANVAS_STYLE_FILL),
       ClrWhite, ClrBlack, ClrBlack, 0, 0, 0, 0);

// �˵���
Canvas(g_sMainLocalDataDisplayHead, &g_sMainLocalDataDisplay, 0, &g_sMainLocalDataDisplayFirst,
       &g_sFormike128x128x16, 1+8, 25, 8*16, 16,
       (CANVAS_STYLE_FILL | CANVAS_STYLE_APP_DRAWN),
       ClrWhite, 0, ClrBlack, 0, "���ؽ���������ʾ", 0, OnPaintMainCharacter);

// ��ʾ���ݵĵ�һ��
Canvas(g_sMainLocalDataDisplayFirst, &g_sMainLocalDataDisplayHead, 0, &g_sMainLocalDataDisplayFirstAVoltage,
		&g_sFormike128x128x16, 1, 42, 157, 117,
       (CANVAS_STYLE_FILL),
       ClrWhite, ClrBlack, ClrBlack, 0, 0, 0, 0);
// A���ѹ
Canvas(g_sMainLocalDataDisplayFirstAVoltage, &g_sMainLocalDataDisplayFirst, &g_sMainLocalDataDisplayFirstBVoltage, 0,
       &g_sFormike128x128x16, 1, 42, 157, 16,
       (CANVAS_STYLE_FILL | CANVAS_STYLE_APP_DRAWN | CANVAS_STYLE_REVERSE_COLOR),
       ClrWhite, 0, ClrBlack, (const tFont*)&g_f64_local_data_a_voltage, " A���ѹ:", 
	   (const unsigned char*)2, OnPaintMainLocalDataDisplay);
// B���ѹ
Canvas(g_sMainLocalDataDisplayFirstBVoltage, &g_sMainLocalDataDisplayFirst, &g_sMainLocalDataDisplayFirstCVoltage, 0,
       &g_sFormike128x128x16, 1, 59, 157, 16,
       (CANVAS_STYLE_FILL | CANVAS_STYLE_APP_DRAWN),
       ClrWhite, 0, ClrBlack, (const tFont*)&g_f64_local_data_b_voltage, " B���ѹ:", 
	   (const unsigned char*)2, OnPaintMainLocalDataDisplay);
// C���ѹ
Canvas(g_sMainLocalDataDisplayFirstCVoltage, &g_sMainLocalDataDisplayFirst, &g_sMainLocalDataDisplayFirstACurrent, 0,
       &g_sFormike128x128x16, 1, 76, 157, 16,
       (CANVAS_STYLE_FILL | CANVAS_STYLE_APP_DRAWN),
       ClrWhite, 0, ClrBlack, (const tFont*)&g_f64_local_data_c_voltage, " C���ѹ:", 
	   (const unsigned char*)2, OnPaintMainLocalDataDisplay);
// A�����
Canvas(g_sMainLocalDataDisplayFirstACurrent, &g_sMainLocalDataDisplayFirst, &g_sMainLocalDataDisplayFirstBCurrent, 0,
       &g_sFormike128x128x16, 1, 93, 157, 16,
       (CANVAS_STYLE_FILL | CANVAS_STYLE_APP_DRAWN),
       ClrWhite, 0, ClrBlack, (const tFont*)&g_f64_local_data_a_current, " A�����:", 
	   (const unsigned char*)2, OnPaintMainLocalDataDisplay);
// B�����
Canvas(g_sMainLocalDataDisplayFirstBCurrent, &g_sMainLocalDataDisplayFirst, &g_sMainLocalDataDisplayFirstCCurrent, 0,
       &g_sFormike128x128x16, 1, 109, 157, 16,
       (CANVAS_STYLE_FILL | CANVAS_STYLE_APP_DRAWN),
       ClrWhite, 0, ClrBlack, (const tFont*)&g_f64_local_data_b_current, " B�����:", 
	   (const unsigned char*)2, OnPaintMainLocalDataDisplay);
// C�����
Canvas(g_sMainLocalDataDisplayFirstCCurrent, &g_sMainLocalDataDisplayFirst, 0, &g_sMainLocalDataDisplayFirstNum,
       &g_sFormike128x128x16, 1, 126, 157, 16,
       (CANVAS_STYLE_FILL | CANVAS_STYLE_APP_DRAWN),
       ClrWhite, 0, ClrBlack, (const tFont*)&g_f64_local_data_c_current, " C�����:", 
	   (const unsigned char*)2, OnPaintMainLocalDataDisplay);
// ��ʾ��ǰ������Ϊ��һ��
Canvas(g_sMainLocalDataDisplayFirstNum, &g_sMainLocalDataDisplayFirstCCurrent, 0,0 ,
       &g_sFormike128x128x16, 135, 25, 24, 16,
       (CANVAS_STYLE_FILL | CANVAS_STYLE_APP_DRAWN),
       ClrWhite, 0, ClrBlack, 0, "1/2", 
	   0, OnPaintMainCharacter);

// ��ʾ���ݵĵڶ���
Canvas(g_sMainLocalDataDisplaySecond, &g_sMainLocalDataDisplayHead, 0, &g_sMainLocalDataDisplaySecondAVoltageAnagle,
       &g_sFormike128x128x16, 1, 42, 157, 117,
       (CANVAS_STYLE_FILL),
       ClrWhite, ClrBlack, ClrBlack, 0, 0, 0, 0);
// A���ѹ���
Canvas(g_sMainLocalDataDisplaySecondAVoltageAnagle, &g_sMainLocalDataDisplaySecond, &g_sMainLocalDataDisplaySecondBVoltageAnagle, 0,
       &g_sFormike128x128x16, 1, 42, 157, 16,
       (CANVAS_STYLE_FILL | CANVAS_STYLE_APP_DRAWN),
       ClrWhite, 0, ClrBlack, (const tFont*)&g_f64_local_data_a_voltage_angle, " A���ѹ���:", 
	   (const unsigned char*)1, OnPaintMainLocalDataDisplay);
// B���ѹ���
Canvas(g_sMainLocalDataDisplaySecondBVoltageAnagle, &g_sMainLocalDataDisplaySecond, &g_sMainLocalDataDisplaySecondCVoltageAnagle, 0,
       &g_sFormike128x128x16, 1, 59, 157, 16,
       (CANVAS_STYLE_FILL | CANVAS_STYLE_APP_DRAWN),
       ClrWhite, 0, ClrBlack, (const tFont*)&g_f64_local_data_b_voltage_angle, " B���ѹ���:", 
	   (const unsigned char*)1, OnPaintMainLocalDataDisplay);
// C���ѹ���
Canvas(g_sMainLocalDataDisplaySecondCVoltageAnagle, &g_sMainLocalDataDisplaySecond, 0, &g_sMainLocalDataDisplaySecondNum,
       &g_sFormike128x128x16, 1, 76, 157, 16,
       (CANVAS_STYLE_FILL | CANVAS_STYLE_APP_DRAWN),
       ClrWhite, 0, ClrBlack, (const tFont*)&g_f64_local_data_c_voltage_angle, " C���ѹ���:", 
	   (const unsigned char*)1, OnPaintMainLocalDataDisplay);
// ��ʾ��ǰ������Ϊ��һ��
Canvas(g_sMainLocalDataDisplaySecondNum, &g_sMainLocalDataDisplaySecondCVoltageAnagle, 0,0 ,
       &g_sFormike128x128x16, 135, 25, 24, 16,
       (CANVAS_STYLE_FILL | CANVAS_STYLE_APP_DRAWN ),
       ClrWhite, 0, ClrBlack, 0, "2/2", 
	   0, OnPaintMainCharacter);

//-----------------------------------------------------------------------------
// ������ ������������ʾ
//-----------------------------------------------------------------------------
// ������ ������������ʾ
Canvas(g_sMainMeasureDataDisplay, &g_sMain, 0, &g_sMainMeasureDataDisplayHead,
       &g_sFormike128x128x16, 1, 25, 157, 134,
       (CANVAS_STYLE_FILL),
       ClrWhite, ClrBlack, ClrBlack, 0, 0, 0, 0);
// �˵���
Canvas(g_sMainMeasureDataDisplayHead, &g_sMainMeasureDataDisplay, &g_sMainMeasureDataDisplayPoint1, 0,
       &g_sFormike128x128x16, 1+8, 25, 7*16, 16,
       (CANVAS_STYLE_FILL | CANVAS_STYLE_APP_DRAWN),
       ClrWhite, 0, ClrBlack, 0, "������������ʾ", 0, OnPaintMainCharacter);
// ������1
Canvas(g_sMainMeasureDataDisplayPoint1, &g_sMainMeasureDataDisplay, &g_sMainMeasureDataDisplayPoint2, 0,
       &g_sFormike128x128x16, 1+8*6, 42, 90, 16,
       (CANVAS_STYLE_FILL | CANVAS_STYLE_APP_DRAWN | CANVAS_STYLE_REVERSE_COLOR),
       ClrWhite, 0, ClrBlack, 0, "������1", 
	   0, OnPaintMainCharacter);
// ������2
Canvas(g_sMainMeasureDataDisplayPoint2, &g_sMainMeasureDataDisplay, &g_sMainMeasureDataDisplayPoint3, 0,
       &g_sFormike128x128x16, 1+8*6, 59, 90, 16,
       (CANVAS_STYLE_FILL | CANVAS_STYLE_APP_DRAWN),
       ClrWhite, 0, ClrBlack, 0, "������2", 
	   0, OnPaintMainCharacter);
// ������3
Canvas(g_sMainMeasureDataDisplayPoint3, &g_sMainMeasureDataDisplay, &g_sMainMeasureDataDisplayPoint4, 0,
       &g_sFormike128x128x16, 1+8*6, 76, 90, 16,
       (CANVAS_STYLE_FILL | CANVAS_STYLE_APP_DRAWN),
       ClrWhite, 0, ClrBlack, 0, "������3", 
	   0, OnPaintMainCharacter);
// ������4
Canvas(g_sMainMeasureDataDisplayPoint4, &g_sMainMeasureDataDisplay, &g_sMainMeasureDataDisplayPoint5, 0,
       &g_sFormike128x128x16, 1+8*6, 93, 90, 16,
       (CANVAS_STYLE_FILL | CANVAS_STYLE_APP_DRAWN),
       ClrWhite, 0, ClrBlack, 0, "������4", 
	   0, OnPaintMainCharacter);
// ������5
Canvas(g_sMainMeasureDataDisplayPoint5, &g_sMainMeasureDataDisplay, &g_sMainMeasureDataDisplayPoint6, 0,
       &g_sFormike128x128x16, 1+8*6, 109, 90, 16,
       (CANVAS_STYLE_FILL | CANVAS_STYLE_APP_DRAWN),
       ClrWhite, 0, ClrBlack, 0, "������5", 
	   0, OnPaintMainCharacter);
// ������6
Canvas(g_sMainMeasureDataDisplayPoint6, &g_sMainMeasureDataDisplay, 0, &g_sMainMeasureDataDisplayNum,
       &g_sFormike128x128x16, 1+8*6, 126, 90, 16,
       (CANVAS_STYLE_FILL | CANVAS_STYLE_APP_DRAWN),
       ClrWhite, 0, ClrBlack, 0, "������6", 
	   0, OnPaintMainCharacter);
// ��ʾ��ǰ������Ϊ��һ��
Canvas(g_sMainMeasureDataDisplayNum, &g_sMainMeasureDataDisplayPoint6, 0,0 ,
       &g_sFormike128x128x16, 135, 25, 24, 16,
       (CANVAS_STYLE_FILL | CANVAS_STYLE_APP_DRAWN ),
       ClrWhite, 0, ClrBlack, 0, "1/1", 
	   0, OnPaintMainCharacter);

//-----------------------------------------------------------------------------
// ������ ������������ϸ��ʾ
//-----------------------------------------------------------------------------
// ������ ������������ϸ��ʾ
Canvas(g_sMainMeasureDataDetial, &g_sMain, 0, &g_sMainMeasureDataDetialHead,
       &g_sFormike128x128x16, 1, 25, 157, 134,
       (CANVAS_STYLE_FILL),
       ClrWhite, ClrBlack, ClrBlack, 0, 0, 0, 0);

// ������n
Canvas(g_sMainMeasureDataDetialHead, &g_sMainMeasureDataDetial, 0, &g_sMainMeasureDataDetialFirst,
       &g_sFormike128x128x16, 1+6*8, 25, 7*8, 16,
       (CANVAS_STYLE_FILL | CANVAS_STYLE_APP_DRAWN),
       ClrWhite, 0, ClrBlack, 0, (const char*)g_pu8_measure_data_point_num, 0, OnPaintMainMeasureDataDetialPoint);

// ѡ��ѭ����ʾ����
Canvas(g_sMainMeasureDataDetialCircleGround, &g_sMainMeasureDataDetial, 0,&g_sMainMeasureDataDetialCircleConfirm,
       &g_sFormike128x128x16, 83, 80, 4*16+3*2, 16*2+3*3,
       (CANVAS_STYLE_FILL | CANVAS_STYLE_OUTLINE),
       ClrWhite, 0, ClrBlack, 0, 0, 0, 0);
// ȷ��ѭ����ʾ
Canvas(g_sMainMeasureDataDetialCircleConfirm, &g_sMainMeasureDataDetialCircleGround, &g_sMainMeasureDataDetialCircleCancel,0,
       &g_sFormike128x128x16, 83+3, 80+3, 4*16, 16,
       (CANVAS_STYLE_FILL | CANVAS_STYLE_APP_DRAWN | CANVAS_STYLE_REVERSE_COLOR),
       ClrWhite, 0, ClrBlack, 0, "ȷ��ѭ��", 0, OnPaintMainCharacter);
// ȡ��ѭ����ʾ
Canvas(g_sMainMeasureDataDetialCircleCancel, &g_sMainMeasureDataDetialCircleGround, 0,0,
       &g_sFormike128x128x16, 83+3, 80+3+16+3, 4*16, 16,
       (CANVAS_STYLE_FILL | CANVAS_STYLE_APP_DRAWN),
       ClrWhite, 0, ClrBlack, 0, "ȡ��ѭ��", 0, OnPaintMainCharacter);

// ��ʾ���ݵĵ�һ��
Canvas(g_sMainMeasureDataDetialFirst, &g_sMainMeasureDataDetialHead, 0, &g_sMainMeasureDataDetialTimeInfo,
		&g_sFormike128x128x16, 1, 42, 157, 117,
       (CANVAS_STYLE_FILL),
       ClrWhite, ClrBlack, ClrBlack, 0, 0, 0, 0);

// ����ʱ����ʾ����
Canvas(g_sMainMeasureDataDetialTimeInfo, &g_sMainMeasureDataDetialFirst, &g_sMainMeasureDataDetialTime, 0,
       &g_sFormike128x128x16, 1, 42, 8*9, 16,
       (CANVAS_STYLE_FILL | CANVAS_STYLE_APP_DRAWN),
       ClrWhite, 0, ClrBlack, 0, "����ʱ��:", 
	   0, OnPaintMainCharacter);

// ����ʱ��
Canvas(g_sMainMeasureDataDetialTime, &g_sMainMeasureDataDetialFirst, &g_sMainMeasureDataDetialZYJ, 0,
       &g_sFormike128x128x16, 73, 42, 8*5, 16,
       (CANVAS_STYLE_FILL | CANVAS_STYLE_APP_DRAWN | CANVAS_STYLE_REVERSE_COLOR),
       ClrWhite, 0, ClrBlack, 0, 0, 
	   0, OnPaintMainMeasureDataDetialTime);

// �����й������
Canvas(g_sMainMeasureDataDetialZYJ, &g_sMainMeasureDataDetialFirst, &g_sMainMeasureDataDetialZYF, 0,
       &g_sFormike128x128x16, 1, 59, 157, 16,
       (CANVAS_STYLE_FILL | CANVAS_STYLE_APP_DRAWN),
       ClrWhite, 0, ClrBlack, (const tFont*)&g_f64_measure_data_point_zyj[0], "���й���:", 
	   (const unsigned char*)2, OnPaintMainLocalDataDisplay);
// �����й������
Canvas(g_sMainMeasureDataDetialZYF, &g_sMainMeasureDataDetialFirst, &g_sMainMeasureDataDetialZYP, 0,
       &g_sFormike128x128x16, 1, 76, 157, 16,
       (CANVAS_STYLE_FILL | CANVAS_STYLE_APP_DRAWN),
       ClrWhite, 0, ClrBlack, (const tFont*)&g_f64_measure_data_point_zyf[0], "���й���:", 
	   (const unsigned char*)2, OnPaintMainLocalDataDisplay);
// �����й�ƽ����
Canvas(g_sMainMeasureDataDetialZYP, &g_sMainMeasureDataDetialFirst, &g_sMainMeasureDataDetialZYG, 0,
       &g_sFormike128x128x16, 1, 93, 157, 16,
       (CANVAS_STYLE_FILL | CANVAS_STYLE_APP_DRAWN),
       ClrWhite, 0, ClrBlack, (const tFont*)&g_f64_measure_data_point_zyp[0], "���й�ƽ:", 
	   (const unsigned char*)2, OnPaintMainLocalDataDisplay);
// �����й��ȵ���
Canvas(g_sMainMeasureDataDetialZYG, &g_sMainMeasureDataDetialFirst, &g_sMainMeasureDataDetialFYJ, 0,
       &g_sFormike128x128x16, 1, 109, 157, 16,
       (CANVAS_STYLE_FILL | CANVAS_STYLE_APP_DRAWN),
       ClrWhite, 0, ClrBlack, (const tFont*)&g_f64_measure_data_point_zyg[0], "���й���:", 
	   (const unsigned char*)2, OnPaintMainLocalDataDisplay);
// �����й������
Canvas(g_sMainMeasureDataDetialFYJ, &g_sMainMeasureDataDetialFirst, 0, &g_sMainMeasureDataDetialFirstNum,
       &g_sFormike128x128x16, 1, 126, 157, 16,
       (CANVAS_STYLE_FILL | CANVAS_STYLE_APP_DRAWN),
       ClrWhite, 0, ClrBlack, (const tFont*)&g_f64_measure_data_point_fyj[0], "���й���:", 
	   (const unsigned char*)2, OnPaintMainLocalDataDisplay);
// ��ʾ��ǰ������Ϊ��һ��
Canvas(g_sMainMeasureDataDetialFirstNum, &g_sMainMeasureDataDetialFYJ, 0,0 ,
       &g_sFormike128x128x16, 135, 25, 24, 16,
       (CANVAS_STYLE_FILL | CANVAS_STYLE_APP_DRAWN),
       ClrWhite, 0, ClrBlack, 0, "1/2", 
	   0, OnPaintMainCharacter);

// ��ʾ���ݵĵڶ���
Canvas(g_sMainMeasureDataDetialSecond, &g_sMainMeasureDataDetialHead, 0, &g_sMainMeasureDataDetialFYF,
       &g_sFormike128x128x16, 1, 42, 157, 117,
       (CANVAS_STYLE_FILL),
       ClrWhite, ClrBlack, ClrBlack, 0, 0, 0, 0);
// �����й������
Canvas(g_sMainMeasureDataDetialFYF, &g_sMainMeasureDataDetialSecond, &g_sMainMeasureDataDetialFYP, 0,
       &g_sFormike128x128x16, 1, 42, 157, 16,
       (CANVAS_STYLE_FILL | CANVAS_STYLE_APP_DRAWN),
       ClrWhite, 0, ClrBlack, (const tFont*)&g_f64_measure_data_point_fyf[0], "���й���:", 
	   (const unsigned char*)2, OnPaintMainLocalDataDisplay);
// �����й�ƽ����
Canvas(g_sMainMeasureDataDetialFYP, &g_sMainMeasureDataDetialSecond, &g_sMainMeasureDataDetialFYG, 0,
       &g_sFormike128x128x16, 1, 59, 157, 16,
       (CANVAS_STYLE_FILL | CANVAS_STYLE_APP_DRAWN),
       ClrWhite, 0, ClrBlack, (const tFont*)&g_f64_measure_data_point_fyp[0], "���й�ƽ:", 
	   (const unsigned char*)2, OnPaintMainLocalDataDisplay);
// �����й��ȵ���
Canvas(g_sMainMeasureDataDetialFYG, &g_sMainMeasureDataDetialSecond, 0, &g_sMainMeasureDataDetialSecondNum,
       &g_sFormike128x128x16, 1, 76, 157, 16,
       (CANVAS_STYLE_FILL | CANVAS_STYLE_APP_DRAWN),
       ClrWhite, 0, ClrBlack, (const tFont*)&g_f64_measure_data_point_fyg[0], "���й���:", 
	   (const unsigned char*)2, OnPaintMainLocalDataDisplay);
// ��ʾ��ǰ������Ϊ��һ��
Canvas(g_sMainMeasureDataDetialSecondNum, &g_sMainMeasureDataDetialFYG, 0,0 ,
       &g_sFormike128x128x16, 135, 25, 24, 16,
       (CANVAS_STYLE_FILL | CANVAS_STYLE_APP_DRAWN),
       ClrWhite, 0, ClrBlack, 0, "2/2", 
	   0, OnPaintMainCharacter);


//-----------------------------------------------------------------------------
// ������ ����������鿴
//-----------------------------------------------------------------------------
// ������ ����������鿴
Canvas(g_sMainParaSet, &g_sMain, 0, &g_sMainParaSetHead,
       &g_sFormike128x128x16, 1, 25, 158, 134,
       (CANVAS_STYLE_FILL),
       ClrWhite, ClrBlack, ClrBlack, 0, 0, 0, 0);
// ����������鿴
Canvas(g_sMainParaSetHead, &g_sMainParaSet, &g_sMainParaSetCmtChannelSet,0,
       &g_sFormike128x128x16, 1+8*3, 25, 6*16, 16,
       (CANVAS_STYLE_FILL | CANVAS_STYLE_APP_DRAWN),
       ClrWhite, 0, ClrBlack, 0, "��ز����鿴", 0, OnPaintMainCharacter);
// ͨѶͨ������
Canvas(g_sMainParaSetCmtChannelSet, &g_sMainParaSet, &g_sMainParaSetAreaMeterSet,0,
       &g_sFormike128x128x16, 1+16*2, 42, 6*16, 16,
       (CANVAS_STYLE_FILL | CANVAS_STYLE_APP_DRAWN | CANVAS_STYLE_REVERSE_COLOR),
       ClrBlack, 0, ClrWhite, 0, "ͨѶͨ���鿴", 0, OnPaintMainCharacter);
// ̨������������
Canvas(g_sMainParaSetAreaMeterSet, &g_sMainParaSet, &g_sMainParaSetCentralMeterSet,0,
       &g_sFormike128x128x16, 1+16*1, 59, 8*16, 16,
       (CANVAS_STYLE_FILL | CANVAS_STYLE_APP_DRAWN),
       ClrWhite, 0, ClrBlack, 0, "̨���������鿴", 0, OnPaintMainCharacter);
// ��������������
Canvas(g_sMainParaSetCentralMeterSet, &g_sMainParaSet, &g_sMainParaSetTimeSet, 0,
       &g_sFormike128x128x16, 1+16*1, 76, 8*16, 16,
       (CANVAS_STYLE_FILL | CANVAS_STYLE_APP_DRAWN),
       ClrWhite, 0, ClrBlack, 0, "�����������鿴", 0, OnPaintMainCharacter);
// �ն�ʱ������
Canvas(g_sMainParaSetTimeSet, &g_sMainParaSet, &g_sMainParaSetPasswdSet, 0,
       &g_sFormike128x128x16, 1+16*2, 93, 6*16, 16,
       (CANVAS_STYLE_FILL | CANVAS_STYLE_APP_DRAWN),
       ClrWhite, 0, ClrBlack, 0, "�ն�ʱ��鿴", 0, OnPaintMainCharacter);
// ������������
Canvas(g_sMainParaSetPasswdSet, &g_sMainParaSet, &g_sMainParaSetNumberSet, 0,
       &g_sFormike128x128x16, 1+16*2, 109, 6*16, 16,
       (CANVAS_STYLE_FILL | CANVAS_STYLE_APP_DRAWN),
       ClrWhite, 0, ClrBlack, 0, "��������鿴", 0, OnPaintMainCharacter);
// �ն˱��
Canvas(g_sMainParaSetNumberSet, &g_sMainParaSet, 0, &g_sMainParaSetNum,
       &g_sFormike128x128x16, 1+16*3, 126, 4*16, 16,
       (CANVAS_STYLE_FILL | CANVAS_STYLE_APP_DRAWN),
       ClrWhite, 0, ClrBlack, 0, "�ն˱��", 0, OnPaintMainCharacter);
// ��ʾ��ǰ������Ϊ��һ��
Canvas(g_sMainParaSetNum, &g_sMainParaSetNumberSet, 0,0 ,
       &g_sFormike128x128x16, 135, 25, 24, 16,
       (CANVAS_STYLE_FILL | CANVAS_STYLE_APP_DRAWN),
       ClrWhite, 0, ClrBlack, 0, "1/1", 
	   0, OnPaintMainCharacter);

//-----------------------------------------------------------------------------
// ������ ͨѶͨ���鿴
//-----------------------------------------------------------------------------
// ������ ͨѶͨ���鿴
Canvas(g_sMainCmtChannalSet, &g_sMain, 0, &g_sMainCmtChannalSetHead,
       &g_sFormike128x128x16, 1, 25, 157, 134,
       (CANVAS_STYLE_FILL),
       ClrWhite, ClrBlack, ClrBlack, 0, 0, 0, 0);
// ͨѶͨ������
Canvas(g_sMainCmtChannalSetHead, &g_sMainCmtChannalSet, 0, &g_sMainCmtChannalSetFirst,
       &g_sFormike128x128x16, 1+3*8, 25, 8*8, 16,
       (CANVAS_STYLE_FILL | CANVAS_STYLE_APP_DRAWN),
       ClrWhite, 0, ClrBlack, 0,"ͨѶͨ���鿴", 0, OnPaintMainCharacter);
//// ѡ��ѭ����ʾ����
//Canvas(g_sMainCmtChannalSetCircleGround, &g_sMainCmtChannalSet, 0,&g_sMainCmtChannalSetCircleConfirm,
//       &g_sFormike128x128x16, 83, 80, 4*16+3*2, 16*2+3*3,
//       (CANVAS_STYLE_FILL | CANVAS_STYLE_OUTLINE),
//       ClrWhite, 0, ClrBlack, 0, 0, 0, 0);
//// ȷ��ѭ����ʾ
//Canvas(g_sMainCmtChannalSetCircleConfirm, &g_sMainCmtChannalSetCircleGround, &g_sMainCmtChannalSetCircleCancel,0,
//       &g_sFormike128x128x16, 83+3, 80+3, 4*16, 16,
//       (CANVAS_STYLE_FILL | CANVAS_STYLE_APP_DRAWN | CANVAS_STYLE_REVERSE_COLOR),
//       ClrWhite, 0, ClrBlack, 0, "ȷ��ѭ��", 0, OnPaintMainCharacter);
//// ȡ��ѭ����ʾ
//Canvas(g_sMainCmtChannalSetCircleCancel, &g_sMainCmtChannalSetCircleGround, 0,0,
//       &g_sFormike128x128x16, 83+3, 80+3+16+3, 4*16, 16,
//       (CANVAS_STYLE_FILL | CANVAS_STYLE_APP_DRAWN),
//       ClrWhite, 0, ClrBlack, 0, "ȡ��ѭ��", 0, OnPaintMainCharacter);
// ��ʾ���ݵĵ�һ��
Canvas(g_sMainCmtChannalSetFirst, &g_sMainCmtChannalSetHead, 0, &g_sMainCmtChannalSetHostIP,
		&g_sFormike128x128x16, 1, 42, 157, 117,
       (CANVAS_STYLE_FILL),
       ClrWhite, ClrBlack, ClrBlack, 0, 0, 0, 0);
// ����IP��ַ
Canvas(g_sMainCmtChannalSetHostIP, &g_sMainCmtChannalSetFirst, &g_sMainCmtChannalSetLocalIP, 0,
       &g_sFormike128x128x16, 1, 42, 8*9, 16,
       (CANVAS_STYLE_FILL | CANVAS_STYLE_APP_DRAWN | CANVAS_STYLE_REVERSE_COLOR),
       ClrWhite, 0, ClrBlack, (const tFont*)&g_u32_cmt_channal_set_host_ip, "����IP:", 
	   0, OnPaintCmtChannalSetIPDisplay);
// ����IP
Canvas(g_sMainCmtChannalSetLocalIP, &g_sMainCmtChannalSetFirst, &g_sMainCmtChannalSetTermIP, 0,
       &g_sFormike128x128x16, 1, 59, 8*5, 16,
       (CANVAS_STYLE_FILL | CANVAS_STYLE_APP_DRAWN),
       ClrWhite, 0, ClrBlack, (const tFont*)&g_u32_cmt_channal_set_local_ip, "����IP:", 
	   0, OnPaintCmtChannalSetIPDisplay);
// �ն�IP
Canvas(g_sMainCmtChannalSetTermIP, &g_sMainCmtChannalSetFirst, &g_sMainCmtChannalSetPortNum, 0,
       &g_sFormike128x128x16, 1, 76, 157, 16,
       (CANVAS_STYLE_FILL | CANVAS_STYLE_APP_DRAWN),
       ClrWhite, 0, ClrBlack, (const tFont*)&g_u32_cmt_channal_set_term_ip, "�ն�IP:", 
	   0, OnPaintCmtChannalSetIPDisplay);
// �˿ں�
Canvas(g_sMainCmtChannalSetPortNum, &g_sMainCmtChannalSetFirst, &g_sMainCmtChannalSetAPN, 0,
       &g_sFormike128x128x16, 1, 93, 157, 16,
       (CANVAS_STYLE_FILL | CANVAS_STYLE_APP_DRAWN),
       ClrWhite, 0, ClrBlack, (const tFont*)&g_f64_cmt_channal_set_port_num, "�˿ں�:", 
	   (const unsigned char*)0, OnPaintMainLocalDataDisplay);
// APN
Canvas(g_sMainCmtChannalSetAPN, &g_sMainCmtChannalSetFirst, &g_sMainCmtChannalSetUserName, 0,
       &g_sFormike128x128x16, 1, 109, 157, 16,
       (CANVAS_STYLE_FILL | CANVAS_STYLE_APP_DRAWN),
       ClrWhite, 0, ClrBlack, (const tFont*)g_pu8_cmt_channal_set_apn, "APN:", 
	   0, OnPaintStringDisplay);
// �û���
Canvas(g_sMainCmtChannalSetUserName, &g_sMainCmtChannalSetFirst, 0, &g_sMainCmtChannalSetFirstNum,
       &g_sFormike128x128x16, 1, 126, 157, 16,
       (CANVAS_STYLE_FILL | CANVAS_STYLE_APP_DRAWN),
       ClrWhite, 0, ClrBlack, (const tFont*)g_pu8_cmt_channal_set_username, "�û���:", 
	   0, OnPaintStringDisplay);
// ��ʾ��ǰ������Ϊ��һ��
Canvas(g_sMainCmtChannalSetFirstNum, &g_sMainCmtChannalSetUserName, 0,0 ,
       &g_sFormike128x128x16, 135, 25, 24, 16,
       (CANVAS_STYLE_FILL | CANVAS_STYLE_APP_DRAWN),
       ClrWhite, 0, ClrBlack, 0, "1/2", 
	   0, OnPaintMainCharacter);


// ��ʾ���ݵĵڶ���
Canvas(g_sMainCmtChannalSetSecond, &g_sMainCmtChannalSetHead, 0, &g_sMainCmtChannalSetPasswd,
       &g_sFormike128x128x16, 1, 42, 157, 117,
       (CANVAS_STYLE_FILL),
       ClrWhite, ClrBlack, ClrBlack, 0, 0, 0, 0);
// ����
Canvas(g_sMainCmtChannalSetPasswd, &g_sMainCmtChannalSetSecond, &g_sMainCmtChannalSetPeriod, 0,
       &g_sFormike128x128x16, 1, 42, 157, 16,
       (CANVAS_STYLE_FILL | CANVAS_STYLE_APP_DRAWN),
       ClrWhite, 0, ClrBlack, (const tFont*)g_pu8_cmt_channal_set_passwd, "����:", 
	   0, OnPaintStringDisplay);
// ��������
Canvas(g_sMainCmtChannalSetPeriod, &g_sMainCmtChannalSetSecond, 0, &g_sMainCmtChannalSetSecondNum,
       &g_sFormike128x128x16, 1, 59, 157, 16,
       (CANVAS_STYLE_FILL | CANVAS_STYLE_APP_DRAWN),
       ClrWhite, 0, ClrBlack, (const tFont*)&g_f64_cmt_channal_set_period, "��������:", 
	   (const unsigned char*)1, OnPaintMainLocalDataDisplay);
// ��ʾ��ǰ������Ϊ�ڶ���
Canvas(g_sMainCmtChannalSetSecondNum, &g_sMainCmtChannalSetPeriod, 0,0 ,
       &g_sFormike128x128x16, 135, 25, 24, 16,
       (CANVAS_STYLE_FILL | CANVAS_STYLE_APP_DRAWN),
       ClrWhite, 0, ClrBlack, 0, "2/2", 
	   0, OnPaintMainCharacter);

//-----------------------------------------------------------------------------
// ������ ̨���������鿴
//-----------------------------------------------------------------------------
// ������ ̨���������鿴
Canvas(g_sMainAreaMeterSet, &g_sMain, 0, &g_sMainAreaMeterSetHead,
       &g_sFormike128x128x16, 1, 25, 157, 134,
       (CANVAS_STYLE_FILL),
       ClrWhite, ClrBlack, ClrBlack, 0, 0, 0, 0);
// �˿ڳ�����
Canvas(g_sMainAreaMeterSetHead, &g_sMainAreaMeterSet, 0, &g_sMainAreaMeterSetFirst,
       &g_sFormike128x128x16, 1+3*8, 25, 8*8, 16,
       (CANVAS_STYLE_FILL | CANVAS_STYLE_APP_DRAWN),
       ClrWhite, 0, ClrBlack, 0,"�˿ڳ�����", 0, OnPaintMainCharacter);
// ��ʾ���ݵĵ�һ��
Canvas(g_sMainAreaMeterSetFirst, &g_sMainAreaMeterSetHead, 0, &g_sMainAreaMeterSetPort1Interval,
		&g_sFormike128x128x16, 1, 42, 157, 117,
       (CANVAS_STYLE_FILL),
       ClrWhite, ClrBlack, ClrBlack, 0, 0, 0, 0);
// �˿�1���:
Canvas(g_sMainAreaMeterSetPort1Interval, &g_sMainAreaMeterSetFirst, &g_sMainAreaMeterSetPort2Interval, 0,
       &g_sFormike128x128x16, 1, 42, 8*9, 16,
       (CANVAS_STYLE_FILL | CANVAS_STYLE_APP_DRAWN | CANVAS_STYLE_REVERSE_COLOR),
       ClrWhite, 0, ClrBlack, (const tFont*)&g_f64_area_meter_set_port1_interval, "�˿�1���:", 
	   (const unsigned char*)1, OnPaintMainLocalDataDisplay);
// �˿�2���:
Canvas(g_sMainAreaMeterSetPort2Interval, &g_sMainAreaMeterSetFirst, &g_sMainAreaMeterSetPort3Interval, 0,
       &g_sFormike128x128x16, 1, 59, 8*10, 16,
       (CANVAS_STYLE_FILL | CANVAS_STYLE_APP_DRAWN),
       ClrWhite, 0, ClrBlack, (const tFont*)&g_f64_area_meter_set_port1_interval, "�˿�2���:", 
	   (const unsigned char*)1, OnPaintMainLocalDataDisplay);
// �˿�3���:
Canvas(g_sMainAreaMeterSetPort3Interval, &g_sMainAreaMeterSetFirst, 0, &g_sMainAreaMeterSetFirstNum,
       &g_sFormike128x128x16, 1, 76,8*10 , 16,
       (CANVAS_STYLE_FILL | CANVAS_STYLE_APP_DRAWN),
       ClrWhite, 0, ClrBlack, (const tFont*)&g_f64_area_meter_set_port1_interval, "�˿�3���:", 
	   (const unsigned char*)1, OnPaintMainLocalDataDisplay);
// ��ʾ��ǰ������Ϊ��һ��
Canvas(g_sMainAreaMeterSetFirstNum, &g_sMainAreaMeterSetPort3Interval, 0,0 ,
       &g_sFormike128x128x16, 127, 25, 24, 16,
       (CANVAS_STYLE_FILL | CANVAS_STYLE_APP_DRAWN),
       ClrWhite, 0, ClrBlack, 0, " 1/1", 
	   0, OnPaintMainCharacter);

//-----------------------------------------------------------------------------
// �ڰ��� �ն˹�����ά��
//-----------------------------------------------------------------------------
// �ڰ��� �ն˹�����ά��
Canvas(g_sMainTermSet, &g_sMain, 0, &g_sMainTermSetHead,
       &g_sFormike128x128x16, 1, 25, 158, 134,
       (CANVAS_STYLE_FILL),
       ClrWhite, ClrBlack, ClrBlack, 0, 0, 0, 0);
// �ն˹�����ά��
Canvas(g_sMainTermSetHead, &g_sMainTermSet, 0,&g_sMainTermSetAMRInfo,
       &g_sFormike128x128x16, 1, 25, 7*16, 16,
       (CANVAS_STYLE_FILL | CANVAS_STYLE_APP_DRAWN),
       ClrWhite, 0, ClrBlack, 0, "�ն˹�����ά��", 0, OnPaintMainCharacter);
// ��������Ϣ
Canvas(g_sMainTermSetAMRInfo, &g_sMainTermSetHead, &g_sMainTermSetLast5Message,0,
       &g_sFormike128x128x16, 1+8*5, 42, 5*16, 16,
       (CANVAS_STYLE_FILL | CANVAS_STYLE_APP_DRAWN | CANVAS_STYLE_REVERSE_COLOR),
       ClrBlack, 0, ClrWhite, 0, "��������Ϣ", 0, OnPaintMainCharacter);
// ���5��������Ϣ
Canvas(g_sMainTermSetLast5Message, &g_sMainTermSetHead, &g_sMainTermSetSystemReset,0,
       &g_sFormike128x128x16, 1+20, 59, 8*15, 16,
       (CANVAS_STYLE_FILL | CANVAS_STYLE_APP_DRAWN),
       ClrWhite, 0, ClrBlack, 0, "���5��������Ϣ", 0, OnPaintMainCharacter);
// ϵͳ��λ
Canvas(g_sMainTermSetSystemReset, &g_sMainTermSetHead, 0,&g_sMainTermSetNum,
       &g_sFormike128x128x16, 1+16*3, 76, 4*16, 16,
       (CANVAS_STYLE_FILL | CANVAS_STYLE_APP_DRAWN),
       ClrWhite, 0, ClrBlack, 0, "ϵͳ��λ", 0, OnPaintMainCharacter);
// ��ʾ��ǰ������Ϊ��һ��
Canvas(g_sMainTermSetNum, &g_sMainTermSetSystemReset, 0,0 ,
       &g_sFormike128x128x16, 135, 25, 24, 16,
       (CANVAS_STYLE_FILL | CANVAS_STYLE_APP_DRAWN),
       ClrWhite, 0, ClrBlack, 0, "1/1", 
	   0, OnPaintMainCharacter);

//-----------------------------------------------------------------------------
// �ھ��� �������汾
//-----------------------------------------------------------------------------
// �ھ��� �������汾
Canvas(g_sMainAMRInfo, &g_sMain, 0, &g_sMainAMRInfoHead,
       &g_sFormike128x128x16, 1, 25, 158, 134,
       (CANVAS_STYLE_FILL),
       ClrWhite, ClrBlack, ClrBlack, 0, 0, 0, 0);
// �ն˹�����ά��
Canvas(g_sMainAMRInfoHead, &g_sMainAMRInfo, 0,&g_sMainAMRInfoVersion,
       &g_sFormike128x128x16, 1+8*5, 25, 5*16, 16,
       (CANVAS_STYLE_FILL | CANVAS_STYLE_APP_DRAWN),
       ClrWhite, 0, ClrBlack, 0, "��������Ϣ", 0, OnPaintMainCharacter);
// ��������Ϣ
Canvas(g_sMainAMRInfoVersion, &g_sMainAMRInfoHead, &g_sMainAMRInfoSoftVersion,0,
       &g_sFormike128x128x16, 1+44, 42, 5*16, 16,
       (CANVAS_STYLE_FILL | CANVAS_STYLE_APP_DRAWN),
       ClrWhite, 0, ClrBlack, 0, "����汾:", 0, OnPaintMainCharacter);
// ���5��������Ϣ
Canvas(g_sMainAMRInfoSoftVersion, &g_sMainAMRInfoHead, 0,0,
       &g_sFormike128x128x16, 1+20, 59, 8*15, 16,
       (CANVAS_STYLE_FILL | CANVAS_STYLE_APP_DRAWN),
       ClrWhite, 0, ClrBlack, (const tFont*)g_pu8_amr_info_soft_version, 
	   " ", 0, OnPaintStringDisplay);


//-----------------------------------------------------------------------------
//
// ��������  :  OnPaintCmtChannalSetIPDisplay 
// ��������  :  ���������ʾ�ַ���
//
// �������  :  ��
//
// ���ز���  :  ��
// 
//-----------------------------------------------------------------------------
void OnPaintStringDisplay(tWidget *pWidget, tContext *pContext)
{
   unsigned long u32_info_len = 0;
   //unsigned char pu8_ip_data[20];
   unsigned char *pu8_string_data;
   //unsigned char u8_value_data_index = 0;
   //unsigned long u32_i;
   //unsigned long u32_ip;
   short s16_xmin = (*pWidget).sPosition.sXMin;
   short s16_ymin = (*pWidget).sPosition.sYMin;
   //short s16_xmax = (*pWidget).sPosition.sXMax;
   //short s16_ymax = (*pWidget).sPosition.sYMax;   

   tCanvasWidget *pst_canvas = (tCanvasWidget *)pWidget;
   unsigned long ulForeground = (*pst_canvas).ulTextColor;
   unsigned long ulBackground = (*pst_canvas).ulFillColor;
   // �ж��Ƿ�Ҫ������ʾ
   if((pst_canvas->ulStyle) & CANVAS_STYLE_REVERSE_COLOR)
   {
       // ����
	   ulForeground = ClrWhite;
	   ulBackground = ClrBlack; 
   }
   else
   {
       // ������ʾ
	   ulForeground = ClrBlack;
	   ulBackground = ClrWhite; 
   }
   // ��ʾ��ʾ��������Ϣ
   u32_info_len = strlen(pst_canvas->pcText);    
   GBStringPrint(s16_xmin,s16_ymin,(unsigned char *)pst_canvas->pcText,ClrBlack,ClrWhite);

   // ���������ʹ��һ��
   pu8_string_data = ((unsigned char *)pst_canvas->pFont); 

   // ��������ַ���
   GBStringPrint(s16_xmin + 8*u32_info_len,s16_ymin,pu8_string_data,ulForeground,ulBackground);  
}


//-----------------------------------------------------------------------------
//
// ��������  :  OnPaintCmtChannalSetIPDisplay 
// ��������  :  ���������ʾIP��ַ
//
// �������  :  ��
//
// ���ز���  :  ��
// 
//-----------------------------------------------------------------------------
void OnPaintCmtChannalSetIPDisplay(tWidget *pWidget, tContext *pContext)
{
   unsigned long u32_info_len = 0;
   unsigned char pu8_ip_data[20];
   //unsigned char u8_value_data_index = 0;
   //unsigned long u32_i;
   unsigned long u32_ip;
   short s16_xmin = (*pWidget).sPosition.sXMin;
   short s16_ymin = (*pWidget).sPosition.sYMin;
   //short s16_xmax = (*pWidget).sPosition.sXMax;
   //short s16_ymax = (*pWidget).sPosition.sYMax;   

   tCanvasWidget *pst_canvas = (tCanvasWidget *)pWidget;
   unsigned long ulForeground = (*pst_canvas).ulTextColor;
   unsigned long ulBackground = (*pst_canvas).ulFillColor;
   // �ж��Ƿ�Ҫ������ʾ
   if((pst_canvas->ulStyle) & CANVAS_STYLE_REVERSE_COLOR)
   {
       // ����
	   ulForeground = ClrWhite;
	   ulBackground = ClrBlack; 
   }
   else
   {
       // ������ʾ
	   ulForeground = ClrBlack;
	   ulBackground = ClrWhite; 
   }
   // ��ʾ��ʾ��������Ϣ
   u32_info_len = strlen(pst_canvas->pcText);    
   GBStringPrint(s16_xmin,s16_ymin,(unsigned char *)pst_canvas->pcText,ClrBlack,ClrWhite);

   // ���������ʹ��һ��
   u32_ip = *((unsigned long *)pst_canvas->pFont); 
   pu8_ip_data[0] = '0' + (((u32_ip >> 24)&0xff)%1000)/100;
   pu8_ip_data[1] = '0' + (((u32_ip >> 24)&0xff)%100)/10;;
   pu8_ip_data[2] = '0' + (((u32_ip >> 24)&0xff)%10)/1;;

   pu8_ip_data[3] = '0' + (((u32_ip >> 16)&0xff)%1000)/100;
   pu8_ip_data[4] = '0' + (((u32_ip >> 16)&0xff)%100)/10;;
   pu8_ip_data[5] = '0' + (((u32_ip >> 16)&0xff)%10)/1;;

   pu8_ip_data[6] = '0' + (((u32_ip >> 8)&0xff)%1000)/100;
   pu8_ip_data[7] = '0' + (((u32_ip >> 8)&0xff)%100)/10;;
   pu8_ip_data[8] = '0' + (((u32_ip >> 8)&0xff)%10)/1;;

   pu8_ip_data[9] = '0' + (((u32_ip >> 0)&0xff)%1000)/100;
   pu8_ip_data[10] = '0' + (((u32_ip >> 0)&0xff)%100)/10;;
   pu8_ip_data[11] = '0' + (((u32_ip >> 0)&0xff)%10)/1;;

   // ���һλΪ0��ʾ����
   pu8_ip_data[12] = 0x00;

   // ��������ַ���
   GBStringPrint(s16_xmin + 8*u32_info_len,s16_ymin,pu8_ip_data,ulForeground,ulBackground);  
}



//-----------------------------------------------------------------------------
//
// ��������  :  OnPaintMainMeasureDataDetialPoint 
// ��������  :  ���������ʾ������
//
// �������  :  ��
//
// ���ز���  :  ��
// 
//-----------------------------------------------------------------------------
void OnPaintMainMeasureDataDetialPoint(tWidget *pWidget, tContext *pContext)
{	
   g_pu8_measure_data_point_num[6] = '0' + g_u8_main_measure_data_index + 1;
   OnPaintMainCharacter(pWidget, pContext);	 
}

//-----------------------------------------------------------------------------
//
// ��������  :  OnPaintMainMeasureDataDetialTime 
// ��������  :  ���������ʾ����ʱ��
//
// �������  :  ��
//
// ���ز���  :  ��
// 
//-----------------------------------------------------------------------------
void OnPaintMainMeasureDataDetialTime(tWidget *pWidget, tContext *pContext)
{	
	 //tCanvasWidget *pst_canvas = (tCanvasWidget *)pWidget;
     g_pu8_measure_data_point_time[g_u8_main_measure_data_index][0] = 
	 				'0' + ((g_pu8_measure_data_point_time_hour[g_u8_main_measure_data_index]%100)/10);  
     g_pu8_measure_data_point_time[g_u8_main_measure_data_index][1] = 
	 				'0' + ((g_pu8_measure_data_point_time_hour[g_u8_main_measure_data_index]%10)/1);  
     g_pu8_measure_data_point_time[g_u8_main_measure_data_index][3] = 
	 				'0' + ((g_pu8_measure_data_point_time_minute[g_u8_main_measure_data_index]%100)/10);  
     g_pu8_measure_data_point_time[g_u8_main_measure_data_index][4] = 
	 				'0' + ((g_pu8_measure_data_point_time_minute[g_u8_main_measure_data_index]%10)/1);  
	 OnPaintMainCharacter(pWidget,pContext);
}

//-----------------------------------------------------------------------------
//
// ��������  :  OnPaintMainFirstFaceDate 
// ��������  :  ���������ʾ����
//
// �������  :  ��
//
// ���ز���  :  ��
// 
//-----------------------------------------------------------------------------
void OnPaintMainFirstFaceDate(tWidget *pWidget, tContext *pContext)
{	 
	 if((g_u32_year < 10000) && (g_u32_month <= 12) && (g_u32_date <= 31))
	 {
	       g_pu8_date[0] = '0' + ((g_u32_year%10000)/1000);  
		   g_pu8_date[1] = '0' + ((g_u32_year%1000)/100);  
		   g_pu8_date[2] = '0' + ((g_u32_year%100)/10);  
		   g_pu8_date[3] = '0' + ((g_u32_year%10)/1);  

		   g_pu8_date[5] = '0' + ((g_u32_month%100)/10);  
		   g_pu8_date[6] = '0' + ((g_u32_month%10)/1);  

		   g_pu8_date[8] = '0' + ((g_u32_date%100)/10);  
		   g_pu8_date[9] = '0' + ((g_u32_date%10)/1);  

		   OnPaintMainCharacter(pWidget,pContext);
	 }
}

//-----------------------------------------------------------------------------
//
// ��������  :  OnPaintMainFirstFaceTime 
// ��������  :  ���������ʾʱ��
//
// �������  :  ��
//
// ���ز���  :  ��
// 
//-----------------------------------------------------------------------------
void OnPaintMainFirstFaceTime(tWidget *pWidget, tContext *pContext)
{	
	 if((g_u32_hour <= 24) && (g_u32_minute <= 59) && (g_u32_second <= 59))
	 {
		   g_pu8_time[0] = '0' + ((g_u32_hour%100)/10);  
		   g_pu8_time[1] = '0' + ((g_u32_hour%10)/1);  

		   g_pu8_time[3] = '0' + ((g_u32_minute%100)/10);  
		   g_pu8_time[4] = '0' + ((g_u32_minute%10)/1);  

		   g_pu8_time[6] = '0' + ((g_u32_second%100)/10);  
		   g_pu8_time[7] = '0' + ((g_u32_second%10)/1);  

		   OnPaintMainCharacter(pWidget,pContext);
	 }
}

//-----------------------------------------------------------------------------
//
// ��������  :  OnPaintMainLocalDataDisplay 
// ��������  :  ���������ʾ��Ӣ����Ϣ+�������ݵĺ���
//
// �������  :  ��
//
// ���ز���  :  ��
// 
//-----------------------------------------------------------------------------
void OnPaintMainLocalDataDisplay(tWidget *pWidget, tContext *pContext)
{
   double f32_value;
   unsigned long u32_value;
   unsigned long u32_decimal_num = 0;
   unsigned long u32_info_len = 0;
   unsigned char pu8_value_data[20];
   unsigned char u8_value_data_index = 0;
   unsigned long u32_i;
   unsigned long u32_j = 1;
   unsigned long u32_k;
   //unsigned long s32_tmp;
   unsigned long u32_tmp;
   unsigned char u8_negative_flag = 0;
   short s16_xmin = (*pWidget).sPosition.sXMin;
   short s16_ymin = (*pWidget).sPosition.sYMin;
   //short s16_xmax = (*pWidget).sPosition.sXMax;
   //short s16_ymax = (*pWidget).sPosition.sYMax;   
   tCanvasWidget *pst_canvas = (tCanvasWidget *)pWidget;
   unsigned long ulForeground = (*pst_canvas).ulTextColor;
   unsigned long ulBackground = (*pst_canvas).ulFillColor;
   // �ж��Ƿ�Ҫ������ʾ
   if((pst_canvas->ulStyle) & CANVAS_STYLE_REVERSE_COLOR)
   {
       // ����
	   ulForeground = ClrWhite;
	   ulBackground = ClrBlack; 
   }
   else
   {
       // ������ʾ
	   ulForeground = ClrBlack;
	   ulBackground = ClrWhite; 
   }
   // ��ʾ��ʾ��������Ϣ
   u32_info_len = strlen(pst_canvas->pcText);    
    //printf("aa %s,\n",pst_canvas->pcText);
   GBStringPrint(s16_xmin,s16_ymin,(unsigned char *)pst_canvas->pcText,ClrBlack,ClrWhite);

   // ���������ʹ��һ��
   u32_decimal_num = (unsigned long)pst_canvas->pucImage;   

   // ���������ʹ��һ��
   f32_value = *((double *)pst_canvas->pFont); 
   
   // ������Ҫ��Ӹ���
   if(f32_value < 0)
   {
     f32_value = 0 - f32_value;
	 pu8_value_data[u8_value_data_index] = '-'; 
	 u8_value_data_index++;
	 u8_negative_flag = 1;
   }
   
   // �ж��Ƿ���С��1�����С��1������Ҫ��ʾ0.����
   // �����Ǵ���1�������
   if(f32_value > 1)
   {
       u32_value = (unsigned long)f32_value;

	   u32_value = u32_value%1000000;
	   // �����ȡÿһλ
	   for(u32_i = 100000;u32_i >= 1; u32_i = u32_i/10)
	   {
	      	 // ��ȡ���λ��ֵ
			 u32_tmp = u32_value/u32_i;	 
			 // ɾ�����λ֮���ʣ������
			 u32_value = u32_value%u32_i;
			 if(u32_tmp != 0)
			 {
			    pu8_value_data[u8_value_data_index] = '0' + u32_tmp; 
				u8_value_data_index++;
			 }
			 else
			 {
			     // ��ʼ��0�Ĳ���ʾ
				 if(u8_value_data_index != u8_negative_flag)
				 {
				    pu8_value_data[u8_value_data_index] = '0' + u32_tmp; 
				    u8_value_data_index++;
				 }
			 }
	   }
   }
   // С��1�����
   else
   {
      // ��С����ǰ�����ַ�0
	  pu8_value_data[u8_value_data_index] = '0'; 
      u8_value_data_index++;
   }
   
   if(u32_decimal_num)
   {
	   // С����
	   pu8_value_data[u8_value_data_index] = '.'; 
	   u8_value_data_index++;
   }
   

   // ���ȳ��ϼ���10
   u32_j = 1;
   for(u32_i = 0; u32_i < u32_decimal_num; u32_i++)
   {
      // ��ȡС���㲿�ֵ�����ߵ�һλ
	  f32_value *= 10;
	  u32_j  *= 10;  
   }
   
   // ��ʾС���㲿������
   u32_tmp  = (unsigned long)f32_value;
   u32_tmp = u32_tmp%u32_j;
   u32_j = u32_j/10;

   // ����С���㲿��λ����ʾ 
   for(u32_i = 0; u32_i < u32_decimal_num; u32_i++)
   {
      // ��ȡС���㲿�ֵ�����ߵ�һλ
	  if(u32_j != 0)
	  {
	     u32_k = u32_tmp/u32_j; 
	  }
	  // �趨С�����ֵ�����
	  pu8_value_data[u8_value_data_index] = '0' + u32_k; 
	  u8_value_data_index++;
	  u32_tmp = u32_tmp%u32_j;
	  u32_j = u32_j/10; 
   }
   // ���һλΪ0��ʾ����
   pu8_value_data[u8_value_data_index] = 0x00;

   // ��������ַ���
   GBStringPrint(s16_xmin + 8*u32_info_len,s16_ymin,pu8_value_data,ulForeground,ulBackground);
}


//-----------------------------------------------------------------------------
//
// ��������  :  fn_canvas_set_reverse_color 
// ��������  :  �趨��ʾ����
//
// �������  :  ��
//
// ���ز���  :  ��
// 
//-----------------------------------------------------------------------------
void fn_canvas_set_reverse_color(tCanvasWidget *pst_canvas)
{
   pst_canvas->ulStyle |= (CANVAS_STYLE_REVERSE_COLOR); 
}

//-----------------------------------------------------------------------------
//
// ��������  :  fn_canvas_clear_reverse_color 
// ��������  :  �����ʾ����
//
// �������  :  ��
//
// ���ز���  :  ��
// 
//-----------------------------------------------------------------------------
void fn_canvas_clear_reverse_color(tCanvasWidget *pst_canvas)
{
   pst_canvas->ulStyle &= ~(CANVAS_STYLE_REVERSE_COLOR); 
}

//-----------------------------------------------------------------------------


//
// ��������  :  fn_set_cavas_fore_back_ground 
// ��������  :  �趨canvasǰ��ɫ�ͱ���ɫ
//
// �������  :  ��
//
// ���ز���  :  ��
// 
//-----------------------------------------------------------------------------
void fn_set_cavas_fore_back_ground(tCanvasWidget *pst_canvas,unsigned long ulForeground,unsigned long ulBackground)
{
   CanvasFillColorSet(pst_canvas,ulBackground);
   CanvasTextColorSet(pst_canvas,ulForeground);
}

//-----------------------------------------------------------------------------
//
// ��������  :  fn_canvas_next_index 
// ��������  :  �趨canvas�����±�
//
// �������  :  ��
//
// ���ز���  :  ��
// 
//-----------------------------------------------------------------------------
int fn_canvas_next_index(tCanvasWidget *pst_canvas,unsigned char *pu8_index)
{
    unsigned char u8_i;
    tCanvasWidget *pst_canvas_tmp = pst_canvas;
	for(u8_i = 0; u8_i < *pu8_index; u8_i++)
	{
	   // ��ȡ��һ��canvas
	   pst_canvas_tmp = (tCanvasWidget *)((*pst_canvas_tmp).sBase.pNext); 
	   if(pst_canvas_tmp == 0)
	   {
	     return 0 ; 
	   }
	}

	// ����Ѿ��������һ��canvas
    if((*pst_canvas_tmp).sBase.pNext == 0)
	{
	   *pu8_index = 0;	   
	   // �����ǰ����
	   fn_canvas_clear_reverse_color(pst_canvas_tmp);	   
	   pst_canvas_tmp = pst_canvas;
	   // ������һ������
	   fn_canvas_set_reverse_color(pst_canvas_tmp);
	}
	// û�е����һ��canvas 
	else
	{
	   *pu8_index = *pu8_index + 1;
	   // �����ǰ����
	   fn_canvas_clear_reverse_color(pst_canvas_tmp);	   
	   pst_canvas_tmp = (tCanvasWidget *)((*pst_canvas_tmp).sBase.pNext); 
	   // ������һ������
	   fn_canvas_set_reverse_color(pst_canvas_tmp);
	}
	return 1;
}

//-----------------------------------------------------------------------------
//
// ��������  :  fn_canvas_prev_index 
// ��������  :  �趨canvas�����±�
//
// �������  :  ��
//
// ���ز���  :  ��
// 
//-----------------------------------------------------------------------------
int fn_canvas_prev_index(tCanvasWidget *pst_canvas,unsigned char *pu8_index)
{
    unsigned char u8_i;
    tCanvasWidget *pst_canvas_tmp = pst_canvas;
    // �����ǰ�ڵ�һ���ʱ��
	if(*pu8_index == 0)
	{
	    // Ѱ�����һ��
		for(u8_i = 0;u8_i < 50; u8_i++)
		{
		   // ��ȡ��һ��canvas		   
		   if((tCanvasWidget *)((*pst_canvas_tmp).sBase.pNext) == 0)
		   {
		      // ��������һ���������һ��Ϊ0
			  break;
		   }
		   // ��ȡ��һ����
		   pst_canvas_tmp = (tCanvasWidget *)((*pst_canvas_tmp).sBase.pNext); 
		   // �����±�
		   *pu8_index = *pu8_index + 1;
		}

		// �������һ���
	    fn_canvas_set_reverse_color(pst_canvas_tmp);

		// ���������һ���
		pst_canvas_tmp = pst_canvas;
		// �����ǰ����
	    fn_canvas_clear_reverse_color(pst_canvas_tmp);
	}
	else
	{
		// ��ȡǰһ��
		*pu8_index = *pu8_index - 1;

		// Ѱ�ҵ�ǰһ����ָ��
		for(u8_i = 0; u8_i < *pu8_index; u8_i++)
		{
		   // ��ȡ��һ��canvas
		   pst_canvas_tmp = (tCanvasWidget *)((*pst_canvas_tmp).sBase.pNext); 
		   if(pst_canvas_tmp == 0)
		   {
		     return 0 ; 
		   }
		}
		
		// �趨ǰһ���
	    fn_canvas_set_reverse_color(pst_canvas_tmp);	 
		
		// ���������ǰ��ķ���
		pst_canvas_tmp = (tCanvasWidget *)((*pst_canvas_tmp).sBase.pNext); 
	    // ������һ������
	    fn_canvas_clear_reverse_color(pst_canvas_tmp);
	}	
	return 1;
}

//-----------------------------------------------------------------------------
//
// ��������  :  OnPaintMainCharacter 
// ��������  :  ��ʾ����
//
// �������  :  ��
//
// ���ز���  :  ��
// 
//-----------------------------------------------------------------------------
void OnPaintMainCharacter(tWidget *pWidget, tContext *pContext)
{
   short s16_xmin = (*pWidget).sPosition.sXMin;
   short s16_ymin = (*pWidget).sPosition.sYMin;
   //short s16_xmax = (*pWidget).sPosition.sXMax;
   //short s16_ymax = (*pWidget).sPosition.sYMax;   
   tCanvasWidget *pst_canvas = (tCanvasWidget *)pWidget;
   unsigned long ulForeground = (*pst_canvas).ulTextColor;
   unsigned long ulBackground = (*pst_canvas).ulFillColor;
   if((pst_canvas->ulStyle) & CANVAS_STYLE_REVERSE_COLOR)
   {
       ulForeground = ClrWhite;
	   ulBackground = ClrBlack; 
   }
   else
   {
       ulForeground = ClrBlack;
	   ulBackground = ClrWhite; 
   }
   // printf("aa %s,\n",pst_canvas->pcText);
   GBStringPrint(s16_xmin,s16_ymin,(unsigned char *)pst_canvas->pcText,ulForeground,ulBackground);
}






// ������
int
main(void)
{

    // ��ʼ��Һ����ʾ
    Formike128x128x16Init();

    // ���⿪��
    Formike128x128x16BacklightOn();

    // systick��ʼ������
    //fn_systick_init();

    // ������ʼ��
    fn_key_init();

    // ���ӱ��������ؼ���
    WidgetAdd(WIDGET_ROOT, (tWidget *)&g_sBackground);

    // ���ͻ��Ƹ��ؼ�����
    WidgetPaint(WIDGET_ROOT);

    // ��ѭ��
    while(1)
    {
        // ѭ��������Ϣ
        WidgetMessageQueueProcess();

		fn_key_process();
    }

}
