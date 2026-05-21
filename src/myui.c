#include "myui.h"

#include "lvgl/lvgl.h"
static void btn_event_cb(lv_event_t * e) {
    lv_event_code_t code = lv_event_get_code(e);
    lv_obj_t * btn = lv_event_get_target_obj(e);
    if (code == LV_EVENT_CLICKED) {
        static uint8_t cnt = 0;
        cnt++;

        /*Get the first child of the button which is the label and change its text*/
        lv_obj_t * label = lv_obj_get_child(btn, 0);
        lv_label_set_text_fmt(label, "Button: %d", cnt);
    }
}

void draw_crosshair(void) {
    // 1. 获取屏幕尺寸（适配不同屏幕）
    lv_coord_t scr_w = lv_obj_get_width(lv_screen_active());   // 屏幕宽度
    lv_coord_t scr_h = lv_obj_get_height(lv_screen_active());  // 屏幕高度
    lv_coord_t center_x = scr_w / 2;                           // 屏幕中心X坐标
    lv_coord_t center_y = scr_h / 2;                           // 屏幕中心Y坐标

    static lv_point_precise_t h_points[2];  // 只定义数组，不初始化
    static lv_point_precise_t v_points[2];

    // 运行时给数组赋值（此时scr_w/center_y等已有确定值）
    // 水平线：(0, center_y) → (scr_w, center_y)
    h_points[0].x = 0;
    h_points[0].y = center_y;
    h_points[1].x = scr_w;
    h_points[1].y = center_y;

    // 垂直线：(center_x, 0) → (center_x, scr_h)
    v_points[0].x = center_x;
    v_points[0].y = 0;
    v_points[1].x = center_x;
    v_points[1].y = scr_h;

    // 2. 创建水平线（横线）
    // --------------------------
    lv_obj_t * h_line = lv_line_create(lv_screen_active());  // 创建线条对象
    lv_line_set_points(h_line, h_points, 2);                 // 设置线条顶点（2个点）
    lv_obj_set_style_line_color(h_line, lv_palette_main(LV_PALETTE_RED), LV_PART_MAIN);
    lv_obj_set_style_line_width(h_line, 2,
                                LV_PART_MAIN);  // 设置线条宽度（2像素）

    // --------------------------
    // 3. 创建垂直线（竖线）
    // --------------------------
    lv_obj_t * v_line = lv_line_create(lv_screen_active());
    lv_line_set_points(v_line, v_points, 2);
    lv_obj_set_style_line_color(v_line, lv_palette_main(LV_PALETTE_RED), LV_PART_MAIN);
    lv_obj_set_style_line_width(v_line, 2, LV_PART_MAIN);

    // （可选）让十字线在其他控件上层显示
    lv_obj_move_foreground(h_line);
    lv_obj_move_foreground(v_line);
}

void start_myui(void) {
    lv_obj_set_style_bg_color(lv_screen_active(), lv_color_hex(0xFFFFFF), LV_PART_MAIN);

    draw_crosshair();

    static lv_style_t style;
    lv_style_init(&style);
    lv_style_set_radius(&style, 5);

    /*Make a gradient*/
    lv_style_set_bg_opa(&style, LV_OPA_COVER);
    static lv_grad_dsc_t grad;
    grad.dir = LV_GRAD_DIR_VER;
    grad.stops_count = 2;
    grad.stops[0].color = lv_palette_lighten(LV_PALETTE_GREY, 1);
    grad.stops[0].opa = LV_OPA_COVER;
    grad.stops[1].color = lv_palette_main(LV_PALETTE_BLUE);
    grad.stops[1].opa = LV_OPA_COVER;

    /*Shift the gradient to the bottom*/
    grad.stops[0].frac = 100;
    grad.stops[1].frac = 100;

    lv_style_set_bg_grad(&style, &grad);

    /*Create an object with the new style*/
    lv_obj_t * obj = lv_obj_create(lv_screen_active());
    lv_obj_add_style(obj, &style, 0);
    lv_obj_center(obj);
}
