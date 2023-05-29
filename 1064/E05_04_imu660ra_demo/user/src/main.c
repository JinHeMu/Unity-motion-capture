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


#define LED1 (B9)

#define PIT_CH (PIT_CH0) // 使用的周期中断编号 如果修改 需要同步对应修改周期中断编号与 isr.c 中的调用

int main(void)
{
  clock_init(SYSTEM_CLOCK_600M); // 不可删除
  debug_init();                  // 调试端口初始化

  gpio_init(LED1, GPO, GPIO_HIGH, GPO_PUSH_PULL);
  // 初始化 LED1 输出 默认高电平 推挽输出模式
  imu660ra_init_9();
  imu963ra_init();
  //		icm20602_init();

  pit_ms_init(PIT_CH, 5);
  interrupt_global_enable(0);

  while (1)
  {

    printf("head:%d,%d,%d", (int)head.Angle_X, (int)head.Angle_Y, (int)head.Angle_Z);
    printf("spine:%d,%d,%d", (int)spine.Angle_X, (int)spine.Angle_Y, (int)spine.Angle_Z);
    printf("thigh_l:%d,%d,%d", (int)thigh_l.Angle_X, (int)thigh_l.Angle_Y, (int)thigh_l.Angle_Z);
    printf("thigh_r:%d,%d,%d", (int)thigh_r.Angle_X, (int)thigh_r.Angle_Y, (int)thigh_r.Angle_Z);
    printf("calf_l:%d,%d,%d", (int)calf_l.Angle_X, (int)calf_l.Angle_Y, (int)calf_l.Angle_Z);
    printf("calf_r:%d,%d,%d", (int)calf_r.Angle_X, (int)calf_r.Angle_Y, (int)calf_r.Angle_Z);
    printf("upperarm_l:%d,%d,%d", (int)upperarm_l.Angle_X, (int)upperarm_l.Angle_Y, (int)upperarm_l.Angle_Z);
    printf("upperarm_r:%d,%d,%d", (int)upperarm_r.Angle_X, (int)upperarm_r.Angle_Y, (int)upperarm_r.Angle_Z);
    printf("lowerarm_l:%d,%d,%d", (int)lowerarm_l.Angle_X, (int)lowerarm_l.Angle_Y, (int)lowerarm_l.Angle_Z);
    printf("lowerarm_r:%d,%d,%d\n", (int)lowerarm_r.Angle_X, (int)lowerarm_r.Angle_Y, (int)lowerarm_r.Angle_Z);

    //        gpio_toggle_level(LED1);                                                // 翻转 LED 引脚输出电平 控制 LED 亮灭
    system_delay_ms(200);
  }
}

void pit_handler(void)
{
  Get_Value();
}
