#ifndef __HELLO_H__
#define __HELLO_H__

#include "grlib.h"
#include "widget.h"
#include "canvas.h"
#include "pushbutton.h"

#define M_SCREEN_FIRST_FACE              0
#define M_SCREEN_MENU			         1
#define M_SCREEN_LOCALDATADISPLAY		 2
#define M_SCREEN_MEASUREDATADISPLAY		 3
#define M_SCREEN_MEASUREDATADETIAL		 4
#define M_SCREEN_PARAMETERSETTING		 5
#define M_SCREEN_TERMINALMANAGER		 6

#define M_SCREEN_CMT_CHANNAL_SET		 7
#define M_SCREEN_AREA_METER_SET		     8
#define M_SCREEN_AMR_INFO    		     9
#define M_SCREEN_LAST_5_MESSAGE          10

#define M_MEASURE_DATA_POINT_NUM  6
extern unsigned char g_pu8_measure_data_point_time_hour[M_MEASURE_DATA_POINT_NUM];	   // ������--����ʱ��--ʱ
extern unsigned char g_pu8_measure_data_point_time_minute[M_MEASURE_DATA_POINT_NUM];  // ������--����ʱ��--��
extern unsigned char g_pu8_measure_data_point_time[M_MEASURE_DATA_POINT_NUM][8]; // ������--����ʱ��--�ַ���
extern double g_f64_measure_data_point_zyj[M_MEASURE_DATA_POINT_NUM];	  // ������--�����й������
extern double g_f64_measure_data_point_zyf[M_MEASURE_DATA_POINT_NUM];	  // ������--�����й������
extern double g_f64_measure_data_point_zyp[M_MEASURE_DATA_POINT_NUM];	  // ������--�����й�ƽ����
extern double g_f64_measure_data_point_zyg[M_MEASURE_DATA_POINT_NUM];	  // ������--�����й��ȵ���
extern double g_f64_measure_data_point_fyj[M_MEASURE_DATA_POINT_NUM];	  // ������--�����й������
extern double g_f64_measure_data_point_fyf[M_MEASURE_DATA_POINT_NUM];	  // ������--�����й������
extern double g_f64_measure_data_point_fyp[M_MEASURE_DATA_POINT_NUM];	  // ������--�����й�ƽ����
extern double g_f64_measure_data_point_fyg[M_MEASURE_DATA_POINT_NUM];	  // ������--�����й��ȵ���

//-----------------------------------------------------------------------------
// ���屳��
//-----------------------------------------------------------------------------
extern tCanvasWidget g_sBackground;
//-----------------------------------------------------------------------------
// ������Ϣ��
//-----------------------------------------------------------------------------
extern tCanvasWidget g_sHeading;
extern tCanvasWidget g_sHeadSignal;
extern tCanvasWidget g_sHeadCmtGscWay;
extern tPushButtonWidget g_sHeadWarningFlag;
extern tCanvasWidget g_sHeadStandard;
extern tCanvasWidget g_sHeadShowMesData;
extern tCanvasWidget g_sHeadCurrentTime;
//-----------------------------------------------------------------------------
// ��Ҫ��ʾ����
//-----------------------------------------------------------------------------
extern tCanvasWidget g_sMain;
extern tCanvasWidget g_sMainInfoGround;
extern tCanvasWidget g_sMainInfo;
//-----------------------------------------------------------------------------
// ��0�� ��ʼ����
//-----------------------------------------------------------------------------
extern tCanvasWidget g_sMainFirstFace;
extern tCanvasWidget g_sMainFirstFaceHead;
extern tCanvasWidget g_sMainFirstFaceDate;
extern tCanvasWidget g_sMainFirstFaceTime;
//-----------------------------------------------------------------------------
// ��һ�� ���˵�
//-----------------------------------------------------------------------------
extern tCanvasWidget g_sMainMenu;
extern tCanvasWidget g_sMainMenuHead;
extern tCanvasWidget g_sMainMenuLocalDataDisplay;
extern tCanvasWidget g_sMainMenuMeasureDataDisplay;
extern tCanvasWidget g_sMainMenuParameterSetting;
extern tCanvasWidget g_sMainMenuTerminalManager;
//-----------------------------------------------------------------------------
// �ڶ��� ���ؽ���������ʾ
//-----------------------------------------------------------------------------
extern tCanvasWidget g_sMainLocalDataDisplay;
extern tCanvasWidget g_sMainLocalDataDisplayHead;
// �����µĵ�һ����	 1/2
extern tCanvasWidget g_sMainLocalDataDisplayFirst;
extern tCanvasWidget g_sMainLocalDataDisplayFirstNum;
extern tCanvasWidget g_sMainLocalDataDisplayFirstAVoltage;
extern tCanvasWidget g_sMainLocalDataDisplayFirstBVoltage;
extern tCanvasWidget g_sMainLocalDataDisplayFirstCVoltage;
extern tCanvasWidget g_sMainLocalDataDisplayFirstACurrent;
extern tCanvasWidget g_sMainLocalDataDisplayFirstBCurrent;
extern tCanvasWidget g_sMainLocalDataDisplayFirstCCurrent;
// �����µĵڶ����� 2/2
extern tCanvasWidget g_sMainLocalDataDisplaySecond;
extern tCanvasWidget g_sMainLocalDataDisplaySecondNum;
extern tCanvasWidget g_sMainLocalDataDisplaySecondAVoltageAnagle;
extern tCanvasWidget g_sMainLocalDataDisplaySecondBVoltageAnagle;
extern tCanvasWidget g_sMainLocalDataDisplaySecondCVoltageAnagle;
//-----------------------------------------------------------------------------
// ������ ������������ʾ
//-----------------------------------------------------------------------------
// ������ ������������ʾ
extern tCanvasWidget g_sMainMeasureDataDisplay;
extern tCanvasWidget g_sMainMeasureDataDisplayHead;
extern tCanvasWidget g_sMainMeasureDataDisplayPoint1;
extern tCanvasWidget g_sMainMeasureDataDisplayPoint2;
extern tCanvasWidget g_sMainMeasureDataDisplayPoint3;
extern tCanvasWidget g_sMainMeasureDataDisplayPoint4;
extern tCanvasWidget g_sMainMeasureDataDisplayPoint5;
extern tCanvasWidget g_sMainMeasureDataDisplayPoint6;
extern tCanvasWidget g_sMainMeasureDataDisplayNum;

//-----------------------------------------------------------------------------
// ������ ������������ϸ��ʾ
//-----------------------------------------------------------------------------
extern tCanvasWidget g_sMainMeasureDataDetial;
extern tCanvasWidget g_sMainMeasureDataDetialHead;
extern tCanvasWidget g_sMainMeasureDataDetialCircleGround;
extern tCanvasWidget g_sMainMeasureDataDetialCircleConfirm;
extern tCanvasWidget g_sMainMeasureDataDetialCircleCancel;
extern tCanvasWidget g_sMainMeasureDataDetialFirst;
extern tCanvasWidget g_sMainMeasureDataDetialTimeInfo;
extern tCanvasWidget g_sMainMeasureDataDetialTime;
extern tCanvasWidget g_sMainMeasureDataDetialZYJ;
extern tCanvasWidget g_sMainMeasureDataDetialZYF;
extern tCanvasWidget g_sMainMeasureDataDetialZYP;
extern tCanvasWidget g_sMainMeasureDataDetialZYG;
extern tCanvasWidget g_sMainMeasureDataDetialFYJ;
extern tCanvasWidget g_sMainMeasureDataDetialFirstNum;
extern tCanvasWidget g_sMainMeasureDataDetialSecond;
extern tCanvasWidget g_sMainMeasureDataDetialFYF;
extern tCanvasWidget g_sMainMeasureDataDetialFYP;
extern tCanvasWidget g_sMainMeasureDataDetialFYG;
extern tCanvasWidget g_sMainMeasureDataDetialSecondNum;

//-----------------------------------------------------------------------------
// ������ ���˵�
//-----------------------------------------------------------------------------
// ������ ���˵�
extern tCanvasWidget g_sMainParaSet;
extern tCanvasWidget g_sMainParaSetHead;
extern tCanvasWidget g_sMainParaSetCmtChannelSet;
extern tCanvasWidget g_sMainParaSetAreaMeterSet;
extern tCanvasWidget g_sMainParaSetCentralMeterSet;
extern tCanvasWidget g_sMainParaSetTimeSet;
extern tCanvasWidget g_sMainParaSetPasswdSet;
extern tCanvasWidget g_sMainParaSetNumberSet;
extern tCanvasWidget g_sMainParaSetNum;

//-----------------------------------------------------------------------------
// ������ ͨѶͨ������
//-----------------------------------------------------------------------------
extern tCanvasWidget g_sMainCmtChannalSet;
extern tCanvasWidget g_sMainCmtChannalSetHead;
extern tCanvasWidget g_sMainCmtChannalSetCircleGround;
extern tCanvasWidget g_sMainCmtChannalSetCircleConfirm;
extern tCanvasWidget g_sMainCmtChannalSetCircleCancel;
extern tCanvasWidget g_sMainCmtChannalSetFirst;
extern tCanvasWidget g_sMainCmtChannalSetHostIP;
extern tCanvasWidget g_sMainCmtChannalSetLocalIP;
extern tCanvasWidget g_sMainCmtChannalSetTermIP;
extern tCanvasWidget g_sMainCmtChannalSetPortNum;
extern tCanvasWidget g_sMainCmtChannalSetAPN;
extern tCanvasWidget g_sMainCmtChannalSetUserName;
extern tCanvasWidget g_sMainCmtChannalSetFirstNum;
extern tCanvasWidget g_sMainCmtChannalSetSecond;
extern tCanvasWidget g_sMainCmtChannalSetPasswd;
extern tCanvasWidget g_sMainCmtChannalSetPeriod;
extern tCanvasWidget g_sMainCmtChannalSetSecondNum;
//-----------------------------------------------------------------------------
// ������ ̨���������鿴
//-----------------------------------------------------------------------------
// ������ ̨���������鿴
extern tCanvasWidget g_sMainAreaMeterSet;
extern tCanvasWidget g_sMainAreaMeterSetHead;
extern tCanvasWidget g_sMainAreaMeterSetFirst;
extern tCanvasWidget g_sMainAreaMeterSetPort1Interval;
extern tCanvasWidget g_sMainAreaMeterSetPort2Interval;
extern tCanvasWidget g_sMainAreaMeterSetPort3Interval;
extern tCanvasWidget g_sMainAreaMeterSetFirstNum;
//-----------------------------------------------------------------------------
// �ڰ��� �ն˹�����ά��
//-----------------------------------------------------------------------------
// �ڰ��� �ն˹�����ά��
extern tCanvasWidget g_sMainTermSet;
extern tCanvasWidget g_sMainTermSetHead;
extern tCanvasWidget g_sMainTermSetAMRInfo;
extern tCanvasWidget g_sMainTermSetLast5Message;
extern tCanvasWidget g_sMainTermSetSystemReset;
extern tCanvasWidget g_sMainTermSetNum;

//-----------------------------------------------------------------------------
// �ھ��� �������汾
//-----------------------------------------------------------------------------
// �ھ��� �������汾
extern tCanvasWidget g_sMainAMRInfo;
extern tCanvasWidget g_sMainAMRInfoHead;
extern tCanvasWidget g_sMainAMRInfoVersion;
extern tCanvasWidget g_sMainAMRInfoSoftVersion;

//-----------------------------------------------------------------------------
// ��������
//-----------------------------------------------------------------------------
extern void OnPaintStringDisplay(tWidget *pWidget, tContext *pContext);
extern void OnPaintCmtChannalSetIPDisplay(tWidget *pWidget, tContext *pContext);
extern void OnPaintMainMeasureDataDetialPoint(tWidget *pWidget, tContext *pContext);
extern void OnPaintMainMeasureDataDetialTime(tWidget *pWidget, tContext *pContext);
extern void OnPaintMainFirstFaceDate(tWidget *pWidget, tContext *pContext);
extern void OnPaintMainFirstFaceTime(tWidget *pWidget, tContext *pContext);
extern void OnPaintMainCharacter(tWidget *pWidget, tContext *pContext);
extern void fn_set_cavas_fore_back_ground(tCanvasWidget *pst_canvas,unsigned long ulForeground,unsigned long ulBackground);
extern void fn_canvas_set_reverse_color(tCanvasWidget *pst_canvas);
extern void fn_canvas_clear_reverse_color(tCanvasWidget *pst_canvas);
extern void OnPaintMainLocalDataDisplay(tWidget *pWidget, tContext *pContext);
extern int fn_canvas_next_index(tCanvasWidget *pst_canvas,unsigned char *pu8_index);
extern int fn_canvas_prev_index(tCanvasWidget *pst_canvas,unsigned char *pu8_index);

extern unsigned char g_u8_current_screen;


#endif

