#include "get_value.h"

#define M_PI 3.1415926f

Angle head;Raw_Data head_Raw;
//Angle head;Raw_Data head_Raw;
//Angle head;Raw_Data head_Raw;
//Angle head;Raw_Data head_Raw;
//Angle head;Raw_Data head_Raw;
//Angle head;Raw_Data head_Raw;
//Angle head;Raw_Data head_Raw;
//Angle head;Raw_Data head_Raw;
//Angle head;Raw_Data head_Raw;


void Value_process(float imu660ra_gyro_x, float imu660ra_gyro_y, float imu660ra_gyro_z, Angle *Object, Raw_Data *Object_raw)
{

	if(abs((int)imu660ra_gyro_x)<6)
	{
		imu660ra_gyro_x = 0;
	}
	if(abs((int)imu660ra_gyro_y)<6)
	{
		imu660ra_gyro_y = 0;
	}
	if(abs((int)imu660ra_gyro_z)<6)
	{
		imu660ra_gyro_z = 0;
	}
	// 陀螺仪角度转弧度
	Object_raw->gyro_x = ((float)imu660ra_gyro_x) * M_PI / 180 / 16.4f;
	Object_raw->gyro_y = ((float)imu660ra_gyro_y) * M_PI / 180 / 16.4f;
	Object_raw->gyro_z = ((float)imu660ra_gyro_z) * M_PI / 180 / 16.4f;
	

	
	Object->Angle_X += (Object_raw->gyro_x / 3.33);
	Object->Angle_Y += (Object_raw->gyro_y / 3.33);
	Object->Angle_Z += (Object_raw->gyro_z / 3.33);
	Object->Angle_X_F = Kalmen_getAngle1(Object->Angle_X, Object_raw->gyro_x, 0.005);
	Object->Angle_Y_F = Kalmen_getAngle2(Object->Angle_Y, Object_raw->gyro_y, 0.005);
	Object->Angle_Z_F = Kalmen_getAngle3(Object->Angle_Z, Object_raw->gyro_z, 0.005);



	if (Object->Angle_Z_F >= 360)
	{
		Object->Angle_Z_F -= 360;
	}

	if (Object->Angle_Z_F <= -360)
	{
		Object->Angle_Z_F += 360;
	}
}

void Get_Value(void)
{
	
//	imu660ra_get_acc_1();                                                         // 获取 IMU660RA 的加速度测量数值
//  imu660ra_get_gyro_1();                                                        // 获取 IMU660RA 的角速度测量数值
//	Value_process(imu660ra_gyro_x_1, imu660ra_gyro_y_1, imu660ra_gyro_z_1, &head, &head_Raw);
	
	imu660ra_get_acc_9();                                                         // 获取 IMU660RA 的加速度测量数值
  imu660ra_get_gyro_9();                                                        // 获取 IMU660RA 的角速度测量数值
	Value_process(imu660ra_gyro_x_9, imu660ra_gyro_y_9, imu660ra_gyro_z_9, &head, &head_Raw);
}