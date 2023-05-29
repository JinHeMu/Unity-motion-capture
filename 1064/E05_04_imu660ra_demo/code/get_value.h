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


extern Angle head;extern Raw_Data head_Raw;

extern Angle spine;extern Raw_Data spine_Raw;

extern Angle thigh_l;extern Raw_Data thigh_l_Raw;
extern Angle thigh_r;extern Raw_Data thigh_r_Raw;

extern Angle calf_l;extern Raw_Data calf_l_Raw;
extern Angle calf_r;extern Raw_Data calf_r_Raw;

extern Angle upperarm_l;extern Raw_Data upperarm_l_Raw;
extern Angle upperarm_r;extern Raw_Data upperarm_r_Raw;

extern Angle lowerarm_l;extern Raw_Data lowerarm_l_Raw;
extern Angle lowerarm_r;extern Raw_Data lowerarm_r_Raw;

void Get_Value(void);
#endif

