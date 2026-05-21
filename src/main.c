#include <SDL.h>
#include <Windows.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "hal/hal.h"
#include "lvgl/lvgl.h"
#include "myui.h"

int main(int argc, char ** argv) {
    lv_init();
    sdl_hal_init(320, 240);

    start_myui();  // test UI

    while (1) {
        uint32_t sleep_time_ms = lv_timer_handler();
        if (sleep_time_ms == LV_NO_TIMER_READY) {
            sleep_time_ms = LV_DEF_REFR_PERIOD;
        }

        usleep(sleep_time_ms * 1000);
    }

    return 0;
}
