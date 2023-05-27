/*********************************************************************************************************************
* RT1064DVL6A Opensourec Library ����RT1064DVL6A ��Դ�⣩��һ�����ڹٷ� SDK �ӿڵĵ�������Դ��
* Copyright (c) 2022 SEEKFREE ��ɿƼ�
* 
* ���ļ��� RT1064DVL6A ��Դ���һ����
* 
* RT1064DVL6A ��Դ�� ���������
* �����Ը���������������ᷢ���� GPL��GNU General Public License���� GNUͨ�ù�������֤��������
* �� GPL �ĵ�3�棨�� GPL3.0������ѡ��ģ��κκ����İ汾�����·�����/���޸���
* 
* ����Դ��ķ�����ϣ�����ܷ������ã�����δ�������κεı�֤
* ����û�������������Ի��ʺ��ض���;�ı�֤
* ����ϸ����μ� GPL
* 
* ��Ӧ�����յ�����Դ���ͬʱ�յ�һ�� GPL �ĸ���
* ���û�У������<https://www.gnu.org/licenses/>
* 
* ����ע����
* ����Դ��ʹ�� GPL3.0 ��Դ����֤Э�� ������������Ϊ���İ汾
* ��������Ӣ�İ��� libraries/doc �ļ����µ� GPL3_permission_statement.txt �ļ���
* ����֤������ libraries �ļ����� �����ļ����µ� LICENSE �ļ�
* ��ӭ��λʹ�ò����������� ���޸�����ʱ���뱣����ɿƼ��İ�Ȩ����������������
* 
* �ļ�����          main
* ��˾����          �ɶ���ɿƼ����޹�˾
* �汾��Ϣ          �鿴 libraries/doc �ļ����� version �ļ� �汾˵��
* ��������          IAR 8.32.4 or MDK 5.33
* ����ƽ̨          RT1064DVL6A
* ��������          https://seekfree.taobao.com/
* 
* �޸ļ�¼
* ����              ����                ��ע
* 2022-09-21        SeekFree            first version
********************************************************************************************************************/

#include "zf_common_headfile.h"

#define LED1                        (B9 )

#define PIT_CH                         (PIT_CH0 )                                 // ʹ�õ������жϱ�� ����޸� ��Ҫͬ����Ӧ�޸������жϱ���� isr.c �еĵ���


int main(void)
{
    clock_init(SYSTEM_CLOCK_600M);  // ����ɾ��
    debug_init();                   // ���Զ˿ڳ�ʼ��
    
    gpio_init(LED1, GPO, GPIO_HIGH, GPO_PUSH_PULL);                             // ��ʼ�� LED1 ��� Ĭ�ϸߵ�ƽ �������ģʽ

    while(1)
    {
        if(imu660ra_init_1())
        {
            printf("\r\nIMU660RA init error.");                                 // IMU660RA ��ʼ��ʧ��
        }
        else
        {
            break;
        }
        gpio_toggle_level(LED1);                                                // ��ת LED ���������ƽ ���� LED ���� ��ʼ����������ƻ����ĺ���
    }
		pit_ms_init(PIT_CH, 5);
    interrupt_global_enable(0);
    
    while(1)
   {
//        printf("\r\nIMU660RA acc data: x=%5d, y=%5d, z=%5d\r\n", imu660ra_acc_x_1, imu660ra_acc_y_1, imu660ra_acc_z_1);
//        printf("%d,%d,%d\r\n", imu660ra_gyro_x_1, imu660ra_gyro_y_1, imu660ra_gyro_z_1);
			printf("%d,%d,%d\n", (int)head.Angle_X, (int)head.Angle_Y, (int)head.Angle_Z);
		 //printf("\r\n data:  x=%5d\r\n",(int)head.Angle_X_F );
//        gpio_toggle_level(LED1);                                                // ��ת LED ���������ƽ ���� LED ����
        system_delay_ms(5);
    }
}

//-------------------------------------------------------------------------------------------------------------------
// �������     PIT ���жϴ������� ����������� PIT ��Ӧ�Ķ�ʱ���жϵ��� ��� isr.c
// ����˵��     void
// ���ز���     void
// ʹ��ʾ��     pit_handler();
//-------------------------------------------------------------------------------------------------------------------
void pit_handler (void)
{
	Get_Value();
}
// **************************** �������� ****************************

// *************************** ���̳�������˵�� ***************************
// ��������ʱ�밴�������������б����
// 
// ����1������û������
//      �鿴�������ִ򿪵��Ƿ�����ȷ�Ĵ��ڣ����򿪵� COM ���Ƿ��Ӧ���ǵ������������� USB-TTL ģ��� COM ��
//      �����ʹ����ɿƼ� CMSIS-DAP | ARM �������������ӣ���ô������������Ƿ��ɶ��������İ崮�������Ƿ��Ѿ����ӣ��������߲鿴���İ�ԭ��ͼ�����ҵ�
//      �����ʹ�� USB-TTL ģ�����ӣ���ô��������Ƿ������Ƿ��ɶ���ģ�� TX �Ƿ����ӵĺ��İ�� RX��ģ�� RX �Ƿ����ӵĺ��İ�� TX
// 
// ����2��������������
//      �鿴�����������õĲ������Ƿ����������һ�£������� zf_common_debug.h �ļ��� DEBUG_UART_BAUDRATE �궨��Ϊ debug uart ʹ�õĴ��ڲ�����
// 
// ����3��������� IMU660RA init error.
//      ��� IMU660RA �Ľ����Ƿ���ȷ
//      ��� IMU660RA ��ģ���ǲ��ǻ���
//      ���ź��߼���������
// 
// ����4��IMU660RA ��ֵ�쳣
//      �����ǲ��������� �����ź��߱���·��
//      ����ģ�鲿������

