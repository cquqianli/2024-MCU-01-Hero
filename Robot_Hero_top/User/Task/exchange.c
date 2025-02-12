#include "struct_typedef.h"
#include "cmsis_os.h"
#include "exchange.h"
#include "ins_task.h"
#include "miniPC_process.h"

extern INS_t INS;

static Vision_Recv_s *vision_recv_data;

void exchange_task(void const *argument)
{
    Vision_Init_Config_s config = {
        .recv_config = {
            .header = VISION_RECV_HEADER,
        },
        .send_config = {
            .header        = VISION_SEND_HEADER,
            .detect_color  = VISION_DETECT_COLOR_BLUE,
            .reset_tracker = VISION_RESET_TRACKER_NO,
            .is_shoot      = VISION_SHOOTING,
            .tail          = VISION_SEND_TAIL,
        },
        .usart_config = {
            .recv_buff_size = VISION_RECV_SIZE,
            .usart_handle   = &huart6,
        },
    };
    vision_recv_data = VisionInit(&config);

    while (1) {
        VisionSetAltitude(INS.Yaw, INS.Roll, INS.Pitch); // 此处C板由于放置位置的关系， Roll 和 Pitch 对调
        VisionSend();

        osDelay(1);
    }
}