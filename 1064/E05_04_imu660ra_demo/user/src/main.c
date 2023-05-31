#include "zf_common_headfile.h"

// Angle head;Raw_Data head_Raw;

// Angle spine;Raw_Data spine_Raw;

// Angle thigh_l;Raw_Data thigh_l_Raw;
// Angle thigh_r;Raw_Data thigh_r_Raw;

// Angle calf_l;Raw_Data calf_l_Raw;
// Angle calf_r;Raw_Data calf_r_Raw;

// Angle upperarm_l;Raw_Data upperarm_l_Raw;
// Angle upperarm_r;Raw_Data upperarm_r_Raw;

// Angle lowerarm_l;Raw_Data lowerarm_l_Raw;
// Angle lowerarm_r;Raw_Data lowerarm_r_Raw;

#define IPS200_TYPE     (IPS200_TYPE_SPI)                                 // 双排排针 并口两寸屏 这里宏定义填写 IPS200_TYPE_PARALLEL8

#define LED1 (B9)

#define PIT_CH (PIT_CH0) // 使用的周期中断编号 如果修改 需要同步对应修改周期中断编号与 isr.c 中的调用

int main(void)
{
  clock_init(SYSTEM_CLOCK_600M); // 不可删除
  debug_init();                  // 调试端口初始化

  gpio_init(LED1, GPO, GPIO_HIGH, GPO_PUSH_PULL);
  // 初始化 LED1 输出 默认高电平 推挽输出模式
  imu660ra_init_1();
	imu660ra_init_2();
	imu660ra_init_3();
  //		icm20602_init();

	gps_init();
	ips200_init(IPS200_TYPE);
	
  pit_ms_init(PIT_CH, 5);
  interrupt_global_enable(0);

  while (1)
  {

    printf("\nhead:%d,%d,%d", (int)head.Angle_X, (int)head.Angle_Y, (int)head.Angle_Z);
    printf("spine:%d,%d,%d", (int)spine.Angle_X, (int)spine.Angle_Y, (int)spine.Angle_Z);
    printf("thigh_l:%d,%d,%d", (int)thigh_l.Angle_X, (int)thigh_l.Angle_Y, (int)thigh_l.Angle_Z);
    printf("thigh_r:%d,%d,%d", (int)thigh_r.Angle_X, (int)thigh_r.Angle_Y, (int)thigh_r.Angle_Z);
    printf("calf_l:%d,%d,%d", (int)calf_l.Angle_X, (int)calf_l.Angle_Y, (int)calf_l.Angle_Z);
    printf("calf_r:%d,%d,%d", (int)calf_r.Angle_X, (int)calf_r.Angle_Y, (int)calf_r.Angle_Z);
    printf("upperarm_l:%d,%d,%d", (int)upperarm_l.Angle_X, (int)upperarm_l.Angle_Y, (int)upperarm_l.Angle_Z);
    printf("upperarm_r:%d,%d,%d", (int)upperarm_r.Angle_X, (int)upperarm_r.Angle_Y, (int)upperarm_r.Angle_Z);
    printf("lowerarm_l:%d,%d,%d", (int)lowerarm_l.Angle_X, (int)lowerarm_l.Angle_Y, (int)lowerarm_l.Angle_Z);
    printf("lowerarm_r:%d,%d,%d\n", (int)lowerarm_r.Angle_X, (int)lowerarm_r.Angle_Y, (int)lowerarm_r.Angle_Z);
		
//    //        gpio_toggle_level(LED1);                                                // 翻转 LED 引脚输出电平 控制 LED 亮灭
		ips200_show_string(100, 16*0, "X");ips200_show_string(150, 16*0, "Y");  ips200_show_string(200, 16*0, "Z");              

		ips200_show_string(0, 16*1, "head");
		ips200_show_string(0, 16*2, "spine");
		ips200_show_string(0, 16*3, "thigh_l");
		ips200_show_string(0, 16*4, "thigh_r");
		ips200_show_string(0, 16*5, "calf_l");
		ips200_show_string(0, 16*6, "calf_r");
		ips200_show_string(0, 16*7, "upperarm_l");
		ips200_show_string(0, 16*8, "upperarm_r");
		ips200_show_string(0, 16*9, "lowerarm_l");
		ips200_show_string(0, 16*10, "lowerarm_r");
		
		
	
		
		ips200_show_int(100, 16*1, (int)head.Angle_X, 4);ips200_show_int(150, 16*1, (int)head.Angle_Y, 4);ips200_show_int(200, 16*1, (int)head.Angle_Z, 4);
		ips200_show_int(100, 16*2, (int)spine.Angle_X, 4);ips200_show_int(150, 16*2, (int)spine.Angle_Y, 4);ips200_show_int(200, 16*2, (int)spine.Angle_Z, 4);
		ips200_show_int(100, 16*3, (int)thigh_l.Angle_X, 4);ips200_show_int(150, 16*3, (int)thigh_l.Angle_Y, 4);ips200_show_int(200, 16*3, (int)thigh_l.Angle_Z, 4);
		ips200_show_int(100, 16*4, (int)thigh_r.Angle_X, 4);ips200_show_int(150, 16*4, (int)thigh_r.Angle_Y, 4);ips200_show_int(200, 16*4, (int)thigh_r.Angle_Z, 4);
		ips200_show_int(100, 16*5, (int)calf_l.Angle_X, 4);ips200_show_int(150, 16*5, (int)calf_l.Angle_Y, 4);ips200_show_int(200, 16*5, (int)calf_l.Angle_Z, 4);
		ips200_show_int(100, 16*6, (int)calf_r.Angle_X, 4);ips200_show_int(150, 16*6, (int)calf_r.Angle_Y, 4);ips200_show_int(200, 16*6, (int)calf_r.Angle_Z, 4);
		ips200_show_int(100, 16*7, (int)upperarm_l.Angle_X, 4);ips200_show_int(150, 16*7, (int)upperarm_l.Angle_Y, 4);ips200_show_int(200, 16*7, (int)upperarm_l.Angle_Z, 4);
		ips200_show_int(100, 16*8, (int)upperarm_r.Angle_X, 4);ips200_show_int(150, 16*8, (int)upperarm_r.Angle_Y, 4);ips200_show_int(200, 16*8, (int)upperarm_r.Angle_Z, 4);
		ips200_show_int(100, 16*9, (int)lowerarm_l.Angle_X, 4);ips200_show_int(150, 16*9, (int)lowerarm_l.Angle_Y, 4);ips200_show_int(200, 16*9, (int)lowerarm_l.Angle_Z, 4);
		ips200_show_int(100, 16*10, (int)lowerarm_r.Angle_X, 4);ips200_show_int(150, 16*10, (int)lowerarm_r.Angle_Y, 4);ips200_show_int(200, 16*10, (int)lowerarm_r.Angle_Z, 4);
		
//		
//		if(gps_tau1201_flag)
//        {
//            gps_tau1201_flag = 0;

//            if(!gps_data_parse())          //开始解析数据
//            {
//                ips200_show_string(0, 16*11, "now time");                        // 显示字符串
//                ips200_show_string(0, 16*12, "gps_state");                       // 显示字符串
//                ips200_show_string(0, 16*13, "latitude");                        // 显示字符串
//                ips200_show_string(0, 16*14, "longitude");                       // 显示字符串
//                ips200_show_string(0, 16*15, "speed");                           // 显示字符串
//                ips200_show_string(0, 16*16, "direction");                       // 显示字符串
//                ips200_show_string(0, 16*17, "satellite_used");                  // 显示字符串
//                ips200_show_string(0, 16*18, "height");                          // 显示字符串
////                
//                ips200_show_uint(120, 16*11, gps_tau1201.time.year, 4);
//                ips200_show_uint(160, 16*11, gps_tau1201.time.month, 2);
//                ips200_show_uint(200, 16*11, gps_tau1201.time.day, 2);
//                ips200_show_uint(120, 16*12, gps_tau1201.time.hour, 2);
//                ips200_show_uint(160, 16*12, gps_tau1201.time.minute, 2);
//                ips200_show_uint(200, 16*12, gps_tau1201.time.second, 2);
//                ips200_show_uint(120, 16*13, gps_tau1201.state, 5);
//                ips200_show_float(120, 16*13, gps_tau1201.latitude, 4, 6);
//                ips200_show_float(120, 16*14, gps_tau1201.longitude, 4, 6);
//                ips200_show_float(120, 16*15, gps_tau1201.speed, 4, 6);
//                ips200_show_float(120, 16*16, gps_tau1201.direction, 4, 6);
//                ips200_show_uint(120, 16*17, gps_tau1201.satellite_used, 5);
//                ips200_show_float(120, 16*18, gps_tau1201.height, 4, 6);
//            }
//        }
		
    system_delay_ms(200);
  }
}

void pit_handler(void)
{
  Get_Value();
}
