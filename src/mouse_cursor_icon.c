/* Minimal placeholder image for mouse cursor to satisfy linker.
   1x1 transparent ARGB8888 image. */
#include "lvgl/lvgl.h"

static const uint8_t mouse_cursor_icon_map[] = {0x00, 0x00, 0x00, 0x00};

const lv_image_dsc_t mouse_cursor_icon = {
    .header = {
        .magic = LV_IMAGE_HEADER_MAGIC,
        .cf = LV_COLOR_FORMAT_ARGB8888,
        .w = 1,
        .h = 1,
        .stride = 4,
    },
    .data_size = sizeof(mouse_cursor_icon_map),
    .data = mouse_cursor_icon_map,
};
