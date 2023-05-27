/***************************************************
*
* @file         Filter.c
* @brief        滤波函数
* @version      v1.0
* @date         2022/2/8
*
***************************************************/

#include "filter.h"

//-----------------------宏-----------------------//


//--------------------全局变量---------------------//

//float Filter_buf[Filter_N + 1] = {0};	//滑动窗口数组

float Q_angle = 0.001;	//陀螺仪噪声协方差
float Q_bias = 0.003;	//陀螺仪漂移噪声协方差
float R_angle = 0.03;	//角度测量噪声协方差


float kal_P_1[2][2] = {0};
float kal_k_1[2] = {0};
float kal_angle_1;	//滤波值
float kal_rate_1;		//滤波值
float angle_bias_1;

float kal_P_2[2][2] = {0};
float kal_k_2[2] = {0};
float kal_angle_2;	//滤波值
float kal_rate_2;		//滤波值
float angle_bias_2;

float kal_P_3[2][2] = {0};
float kal_k_3[2] = {0};
float kal_angle_3;	//滤波值
float kal_rate_3;		//滤波值
float angle_bias_3;

float cpm_k = 0.85;	//二阶滤波系数
float cpm_angle;//滤波值

float yaw_Filter = 0;

//---------------------结构体---------------------//



//-------------------------------------------------------------------------------------------------------------------
//  @brief      卡尔曼滤波 | yaw角
//  @param      now_angle            应该由加速度计得到angle，再使用陀螺仪进行补偿，但是加速度计得不到yaw角，可能还是得使用磁力计
//  @param      now_rate             陀螺仪得到的角速度
//  @param      dt      			 采样时间
//  @return     kal_angle			 滤波值
//  Sample usage:
//-------------------------------------------------------------------------------------------------------------------
float Kalmen_getAngle1(float now_angle, float now_rate,float dt)
{
    //预测当前角度
    kal_angle_1 = kal_angle_1 - Q_bias * dt + now_rate * dt;

    //预测误差协方差
    kal_P_1[0][0] += Q_angle - (kal_P_1[0][1] -kal_P_1[1][0]) * dt;
    kal_P_1[0][1] -= kal_P_1[0][1] * dt;
    kal_P_1[1][0] -= kal_P_1[1][0] * dt;
    kal_P_1[1][1] += Q_bias;

    //计算卡尔曼增益
    kal_k_1[0] = kal_P_1[0][0]/(kal_P_1[0][0] + R_angle);
    kal_k_1[1] = kal_P_1[1][0]/(kal_P_1[0][0] + R_angle);

    //计算最优估计值
    kal_angle_1 = kal_angle_1 + kal_k_1[0] * (now_angle - kal_angle_1);
    Q_bias    = Q_bias    + kal_k_1[1] * (now_angle - kal_angle_1);

    //更新协方差矩阵
    kal_P_1[0][0] = kal_P_1[0][0] - kal_k_1[0] * kal_P_1[0][0];
    kal_P_1[0][1] = kal_P_1[0][1] - kal_k_1[0] * kal_P_1[0][1];
    kal_P_1[1][0] = kal_P_1[1][0] - kal_k_1[1] * kal_P_1[0][0];
    kal_P_1[1][1] = kal_P_1[1][1] - kal_k_1[1] * kal_P_1[0][1];

    return kal_angle_1;
}

float Kalmen_getAngle2(float now_angle, float now_rate,float dt)
{
    //预测当前角度
    kal_angle_2 = kal_angle_2 - Q_bias * dt + now_rate * dt;

    //预测误差协方差
    kal_P_2[0][0] += Q_angle - (kal_P_2[0][1] -kal_P_2[1][0]) * dt;
    kal_P_2[0][1] -= kal_P_2[0][1] * dt;
    kal_P_2[1][0] -= kal_P_2[1][0] * dt;
    kal_P_2[1][1] += Q_bias;

    //计算卡尔曼增益
    kal_k_2[0] = kal_P_2[0][0]/(kal_P_2[0][0] + R_angle);
    kal_k_2[1] = kal_P_2[1][0]/(kal_P_2[0][0] + R_angle);

    //计算最优估计值
    kal_angle_2 = kal_angle_2 + kal_k_2[0] * (now_angle - kal_angle_2);
    Q_bias    = Q_bias    + kal_k_2[1] * (now_angle - kal_angle_2);

    //更新协方差矩阵
    kal_P_2[0][0] = kal_P_2[0][0] - kal_k_2[0] * kal_P_2[0][0];
    kal_P_2[0][1] = kal_P_2[0][1] - kal_k_2[0] * kal_P_2[0][1];
    kal_P_2[1][0] = kal_P_2[1][0] - kal_k_2[1] * kal_P_2[0][0];
    kal_P_2[1][1] = kal_P_2[1][1] - kal_k_2[1] * kal_P_2[0][1];

    return kal_angle_2;
}

float Kalmen_getAngle3(float now_angle, float now_rate,float dt)
{
    //预测当前角度
    kal_angle_3 = kal_angle_3 - Q_bias * dt + now_rate * dt;

    //预测误差协方差
    kal_P_3[0][0] += Q_angle - (kal_P_3[0][1] -kal_P_3[1][0]) * dt;
    kal_P_3[0][1] -= kal_P_3[0][1] * dt;
    kal_P_3[1][0] -= kal_P_3[1][0] * dt;
    kal_P_3[1][1] += Q_bias;

    //计算卡尔曼增益
    kal_k_3[0] = kal_P_3[0][0]/(kal_P_3[0][0] + R_angle);
    kal_k_3[1] = kal_P_3[1][0]/(kal_P_3[0][0] + R_angle);

    //计算最优估计值
    kal_angle_3 = kal_angle_3 + kal_k_3[0] * (now_angle - kal_angle_3);
    Q_bias    = Q_bias    + kal_k_3[1] * (now_angle - kal_angle_3);

    //更新协方差矩阵
    kal_P_3[0][0] = kal_P_3[0][0] - kal_k_3[0] * kal_P_3[0][0];
    kal_P_3[0][1] = kal_P_3[0][1] - kal_k_3[0] * kal_P_3[0][1];
    kal_P_3[1][0] = kal_P_3[1][0] - kal_k_3[1] * kal_P_3[0][0];
    kal_P_3[1][1] = kal_P_3[1][1] - kal_k_3[1] * kal_P_3[0][1];

    return kal_angle_3;
}


//-------------------------------------------------------------------------------------------------------------------
//  @brief      二阶互补滤波 | yaw角
//  @param      now_angle            应该由加速度计得到angle，再使用陀螺仪进行补偿，但是加速度计得不到yaw角，可能还是得使用磁力计
//  @param      now_rate             陀螺仪得到的角速度
//  @param      dt      			 采样时间
//  @return     cpm_angle			 滤波值
//  Sample usage:
//-------------------------------------------------------------------------------------------------------------------


float complementary_filter2(float now_angle, float now_rate, float dt)
{
    float y1,x1,x2;
    x1 = (now_angle - cpm_angle) * cpm_k * cpm_k;
    y1 = y1 + x1 * dt;
    x2 = y1 + 2 * cpm_k *(now_angle - cpm_angle) + now_rate;
    cpm_angle = cpm_angle + x2 * dt;
    return cpm_angle;
}

//-------------------------------------------------------------------------------------------------------------------
//  @brief      输入一个值弹出一个值，所有值取平均 | 滑动滤波
//  @param		待滤波的值
//  @return
//  Sample usage:
//-------------------------------------------------------------------------------------------------------------------

float Movingaverage_filter(float value,float Filter_buff[])
{
    int8_t i = 0;//遍历
    float temp = value;
    float Filter_sum = 0;
    Filter_buff[Filter_N] = temp;

    for(i = 0; i < Filter_N; i++)
    {
        Filter_buff[i] = Filter_buff[i+1];		//数据左移
        Filter_sum += Filter_buff[i];
    }
    temp = Filter_sum / Filter_N;
    return temp;
}


//-------------------------------------------------------------------------------------------------------------------
//  @brief      低通滤波
//  @param      待滤波的值
//  @return     滤波值
//  Sample usage:
//-------------------------------------------------------------------------------------------------------------------

float RCFilter(float value,RC_Filter_pt Filter)
{
    Filter->temp = value;
    Filter->value = (1 - Filter->RC) * Filter->value + Filter->RC * Filter->temp;
//	temp = RC * value + (1 - RC) * temp;
    return Filter->value;
}

