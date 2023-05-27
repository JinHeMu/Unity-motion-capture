/***************************************************
*
* @file         Filter.c
* @brief        �˲�����
* @version      v1.0
* @date         2022/2/8
*
***************************************************/

#include "filter.h"

//-----------------------��-----------------------//


//--------------------ȫ�ֱ���---------------------//

//float Filter_buf[Filter_N + 1] = {0};	//������������

float Q_angle = 0.001;	//����������Э����
float Q_bias = 0.003;	//������Ư������Э����
float R_angle = 0.03;	//�ǶȲ�������Э����


float kal_P_1[2][2] = {0};
float kal_k_1[2] = {0};
float kal_angle_1;	//�˲�ֵ
float kal_rate_1;		//�˲�ֵ
float angle_bias_1;

float kal_P_2[2][2] = {0};
float kal_k_2[2] = {0};
float kal_angle_2;	//�˲�ֵ
float kal_rate_2;		//�˲�ֵ
float angle_bias_2;

float kal_P_3[2][2] = {0};
float kal_k_3[2] = {0};
float kal_angle_3;	//�˲�ֵ
float kal_rate_3;		//�˲�ֵ
float angle_bias_3;

float cpm_k = 0.85;	//�����˲�ϵ��
float cpm_angle;//�˲�ֵ

float yaw_Filter = 0;

//---------------------�ṹ��---------------------//



//-------------------------------------------------------------------------------------------------------------------
//  @brief      �������˲� | yaw��
//  @param      now_angle            Ӧ���ɼ��ٶȼƵõ�angle����ʹ�������ǽ��в��������Ǽ��ٶȼƵò���yaw�ǣ����ܻ��ǵ�ʹ�ô�����
//  @param      now_rate             �����ǵõ��Ľ��ٶ�
//  @param      dt      			 ����ʱ��
//  @return     kal_angle			 �˲�ֵ
//  Sample usage:
//-------------------------------------------------------------------------------------------------------------------
float Kalmen_getAngle1(float now_angle, float now_rate,float dt)
{
    //Ԥ�⵱ǰ�Ƕ�
    kal_angle_1 = kal_angle_1 - Q_bias * dt + now_rate * dt;

    //Ԥ�����Э����
    kal_P_1[0][0] += Q_angle - (kal_P_1[0][1] -kal_P_1[1][0]) * dt;
    kal_P_1[0][1] -= kal_P_1[0][1] * dt;
    kal_P_1[1][0] -= kal_P_1[1][0] * dt;
    kal_P_1[1][1] += Q_bias;

    //���㿨��������
    kal_k_1[0] = kal_P_1[0][0]/(kal_P_1[0][0] + R_angle);
    kal_k_1[1] = kal_P_1[1][0]/(kal_P_1[0][0] + R_angle);

    //�������Ź���ֵ
    kal_angle_1 = kal_angle_1 + kal_k_1[0] * (now_angle - kal_angle_1);
    Q_bias    = Q_bias    + kal_k_1[1] * (now_angle - kal_angle_1);

    //����Э�������
    kal_P_1[0][0] = kal_P_1[0][0] - kal_k_1[0] * kal_P_1[0][0];
    kal_P_1[0][1] = kal_P_1[0][1] - kal_k_1[0] * kal_P_1[0][1];
    kal_P_1[1][0] = kal_P_1[1][0] - kal_k_1[1] * kal_P_1[0][0];
    kal_P_1[1][1] = kal_P_1[1][1] - kal_k_1[1] * kal_P_1[0][1];

    return kal_angle_1;
}

float Kalmen_getAngle2(float now_angle, float now_rate,float dt)
{
    //Ԥ�⵱ǰ�Ƕ�
    kal_angle_2 = kal_angle_2 - Q_bias * dt + now_rate * dt;

    //Ԥ�����Э����
    kal_P_2[0][0] += Q_angle - (kal_P_2[0][1] -kal_P_2[1][0]) * dt;
    kal_P_2[0][1] -= kal_P_2[0][1] * dt;
    kal_P_2[1][0] -= kal_P_2[1][0] * dt;
    kal_P_2[1][1] += Q_bias;

    //���㿨��������
    kal_k_2[0] = kal_P_2[0][0]/(kal_P_2[0][0] + R_angle);
    kal_k_2[1] = kal_P_2[1][0]/(kal_P_2[0][0] + R_angle);

    //�������Ź���ֵ
    kal_angle_2 = kal_angle_2 + kal_k_2[0] * (now_angle - kal_angle_2);
    Q_bias    = Q_bias    + kal_k_2[1] * (now_angle - kal_angle_2);

    //����Э�������
    kal_P_2[0][0] = kal_P_2[0][0] - kal_k_2[0] * kal_P_2[0][0];
    kal_P_2[0][1] = kal_P_2[0][1] - kal_k_2[0] * kal_P_2[0][1];
    kal_P_2[1][0] = kal_P_2[1][0] - kal_k_2[1] * kal_P_2[0][0];
    kal_P_2[1][1] = kal_P_2[1][1] - kal_k_2[1] * kal_P_2[0][1];

    return kal_angle_2;
}

float Kalmen_getAngle3(float now_angle, float now_rate,float dt)
{
    //Ԥ�⵱ǰ�Ƕ�
    kal_angle_3 = kal_angle_3 - Q_bias * dt + now_rate * dt;

    //Ԥ�����Э����
    kal_P_3[0][0] += Q_angle - (kal_P_3[0][1] -kal_P_3[1][0]) * dt;
    kal_P_3[0][1] -= kal_P_3[0][1] * dt;
    kal_P_3[1][0] -= kal_P_3[1][0] * dt;
    kal_P_3[1][1] += Q_bias;

    //���㿨��������
    kal_k_3[0] = kal_P_3[0][0]/(kal_P_3[0][0] + R_angle);
    kal_k_3[1] = kal_P_3[1][0]/(kal_P_3[0][0] + R_angle);

    //�������Ź���ֵ
    kal_angle_3 = kal_angle_3 + kal_k_3[0] * (now_angle - kal_angle_3);
    Q_bias    = Q_bias    + kal_k_3[1] * (now_angle - kal_angle_3);

    //����Э�������
    kal_P_3[0][0] = kal_P_3[0][0] - kal_k_3[0] * kal_P_3[0][0];
    kal_P_3[0][1] = kal_P_3[0][1] - kal_k_3[0] * kal_P_3[0][1];
    kal_P_3[1][0] = kal_P_3[1][0] - kal_k_3[1] * kal_P_3[0][0];
    kal_P_3[1][1] = kal_P_3[1][1] - kal_k_3[1] * kal_P_3[0][1];

    return kal_angle_3;
}


//-------------------------------------------------------------------------------------------------------------------
//  @brief      ���׻����˲� | yaw��
//  @param      now_angle            Ӧ���ɼ��ٶȼƵõ�angle����ʹ�������ǽ��в��������Ǽ��ٶȼƵò���yaw�ǣ����ܻ��ǵ�ʹ�ô�����
//  @param      now_rate             �����ǵõ��Ľ��ٶ�
//  @param      dt      			 ����ʱ��
//  @return     cpm_angle			 �˲�ֵ
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
//  @brief      ����һ��ֵ����һ��ֵ������ֵȡƽ�� | �����˲�
//  @param		���˲���ֵ
//  @return
//  Sample usage:
//-------------------------------------------------------------------------------------------------------------------

float Movingaverage_filter(float value,float Filter_buff[])
{
    int8_t i = 0;//����
    float temp = value;
    float Filter_sum = 0;
    Filter_buff[Filter_N] = temp;

    for(i = 0; i < Filter_N; i++)
    {
        Filter_buff[i] = Filter_buff[i+1];		//��������
        Filter_sum += Filter_buff[i];
    }
    temp = Filter_sum / Filter_N;
    return temp;
}


//-------------------------------------------------------------------------------------------------------------------
//  @brief      ��ͨ�˲�
//  @param      ���˲���ֵ
//  @return     �˲�ֵ
//  Sample usage:
//-------------------------------------------------------------------------------------------------------------------

float RCFilter(float value,RC_Filter_pt Filter)
{
    Filter->temp = value;
    Filter->value = (1 - Filter->RC) * Filter->value + Filter->RC * Filter->temp;
//	temp = RC * value + (1 - RC) * temp;
    return Filter->value;
}

