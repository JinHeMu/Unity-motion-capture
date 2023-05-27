/***************************************************
*
* @file         Road.h
* @brief        ���������ݴ����ļ�
* @version      v1.0
* @date         2022/1/18
*
***************************************************/
#ifndef _FILTER_h
#define _FILTER_h
#include <stdint.h>
//-----------------------��-----------------------//
#define Filter_N 10	//������ȡ10����������ֵ
//--------------------ȫ�ֱ���---------------------//
extern float yaw_Filter;
//---------------------�ṹ��---------------------//
struct RC_Para
{
    float temp;  //�ݴ�ֵ,�洢RC_baro
    float value; //�˲�ֵ
    float RC;    //��ͨ�˲�����
};
typedef struct RC_Para *RC_Filter_pt;



/***************************************************************************/
float Kalmen_getAngle1(float now_angle, float now_rate,float dt);
float Kalmen_getAngle2(float now_angle, float now_rate,float dt);
float Kalmen_getAngle3(float now_angle, float now_rate,float dt);

float complementary_filter2(float now_angle, float now_rate, float dt);
float Movingaverage_filter(float value,float Filter_buff[]);
float RCFilter(float value,RC_Filter_pt Filter);
int Angel_PID(int NowAngel,int TargetAngel);

#endif