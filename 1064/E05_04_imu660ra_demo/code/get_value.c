#include "get_value.h"

#define M_PI 3.1415926f

Angle head;
Raw_Data head_Raw;


void Value_process()
{

	if(abs((int)imu660ra_gyro_x_1)<6)
	{
		imu660ra_gyro_x_1 = 0;
	}
	if(abs((int)imu660ra_gyro_y_1)<6)
	{
		imu660ra_gyro_y_1 = 0;
	}
	if(abs((int)imu660ra_gyro_z_1)<6)
	{
		imu660ra_gyro_z_1 = 0;
	}
	// 陀螺仪角度转弧度
	head_Raw.gyro_x = ((float)imu660ra_gyro_x_1) * M_PI / 180 / 16.4f;
	head_Raw.gyro_y = ((float)imu660ra_gyro_y_1) * M_PI / 180 / 16.4f;
	head_Raw.gyro_z = ((float)imu660ra_gyro_z_1) * M_PI / 180 / 16.4f;
	

	
	head.Angle_X += (head_Raw.gyro_x / 3.33);
	head.Angle_Y += (head_Raw.gyro_y / 3.33);
	head.Angle_Z += (head_Raw.gyro_z / 3.33);
//	head.Angle_X_F = Kalmen_getAngle(head.Angle_X, head_Raw.gyro_x, 0.005);
//	head.Angle_Y_F = Kalmen_getAngle(head.Angle_Y, head_Raw.gyro_y, 0.005);
//	head.Angle_Z_F = Kalmen_getAngle(head.Angle_Z, head_Raw.gyro_z, 0.005);



	if (head.Angle_Z_F >= 360)
	{
		head.Angle_Z_F -= 360;
	}

	if (head.Angle_Z_F <= -360)
	{
		head.Angle_Z_F += 360;
	}
}

void Get_Value(void)
{
	
	imu660ra_get_acc_1();                                                         // 获取 IMU660RA 的加速度测量数值
  imu660ra_get_gyro_1();                                                        // 获取 IMU660RA 的角速度测量数值
	Value_process();
}