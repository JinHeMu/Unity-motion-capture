#ifndef __GET_VALUE_H__
#define __GET_VALUE_H__

#include "zf_common_headfile.h"

typedef struct {
    float gyro_x;
    float gyro_y;
    float gyro_z;
    float acc_x;
    float acc_y;
    float acc_z;
} Raw_Data;

typedef struct {
    float Angle_X;
    float Angle_Y;
    float Angle_Z;
	  float Angle_X_F;
    float Angle_Y_F;
    float Angle_Z_F;
} Angle;

extern Angle head;
extern Raw_Data head_Raw;

void Get_Value(void);
#endif

