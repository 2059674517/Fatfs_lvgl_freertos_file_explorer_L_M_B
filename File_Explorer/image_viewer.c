/* image_viewer.c */
#include "image_viewer.h"
#include "file_browser.h"
#include "lvgl.h"
#include <string.h>

static lv_obj_t* img_container = NULL;
static lv_obj_t* img_obj = NULL;

static void event_handler(lv_event_t* e) {
    lv_event_code_t code = lv_event_get_code(e);
    if(code == LV_EVENT_CLICKED) {
        image_viewer_close();
    }
}

void image_viewer_close(void) {
    if(img_container) {
        lv_obj_del(img_container);
        img_container = NULL;
    }
}

void image_viewer_open(const char* folder_path, const char* filename) {
    // 确保单实例运行
    if(img_container) return;

    // 创建全屏容器
    img_container = lv_obj_create(lv_scr_act());
    lv_obj_remove_style_all(img_container);       // 清除所有默认样式
    lv_obj_set_size(img_container, DISP_HOR_RES, DISP_VER_RES);
    lv_obj_set_style_bg_opa(img_container, LV_OPA_COVER, 0);
    lv_obj_set_style_bg_color(img_container, lv_color_white(), 0);
    lv_obj_center(img_container);

    // 添加容器点击事件（整个区域可点击）
    lv_obj_add_event_cb(img_container, event_handler, LV_EVENT_CLICKED, NULL);
    lv_obj_add_flag(img_container, LV_OBJ_FLAG_CLICKABLE);

    // 创建文件名标签
    lv_obj_t* label = lv_label_create(img_container);
    lv_label_set_text(label, filename);
    lv_obj_set_width(label, DISP_HOR_RES);
    lv_obj_align(label, LV_ALIGN_TOP_MID, 0, 5);
    lv_obj_set_style_text_align(label, LV_TEXT_ALIGN_CENTER, 0);

    // 构建图片路径
    char full_path[256];
    snprintf(full_path, sizeof(full_path), "%s/%s", folder_path, filename);

    // 创建图片对象
    img_obj = lv_img_create(img_container);
    lv_img_set_src(img_obj, full_path);
    lv_obj_align(img_obj, LV_ALIGN_CENTER, 0, 0);
}
