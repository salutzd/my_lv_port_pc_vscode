#ifndef MYUI_H
#define MYUI_H
#include "lvgl/lvgl.h"

void start_myui(void);
static void btn_event_cb(lv_event_t * e);
void draw_crosshair(void);
#endif /* MYUI_H */
