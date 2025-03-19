/* media_player.c */
#include "media_player.h"

static lv_obj_t* media_cont;
static lv_obj_t* progress_bar;

static void control_event(lv_event_t* e) {
    const char* txt = lv_label_get_text(lv_obj_get_child(e->target, 0));
    
    if(strcmp(txt, LV_SYMBOL_CLOSE) == 0) {
        lv_obj_del(media_cont);
        media_cont = NULL;
    }
}

void media_player_open(const char* path) {
    if(media_cont) return;
    
    media_cont = lv_obj_create(lv_scr_act());
    lv_obj_set_size(media_cont, 200, 150);
    lv_obj_align(media_cont, LV_ALIGN_CENTER, 0, 0);
    
    // 进度条
    progress_bar = lv_bar_create(media_cont);
    lv_obj_set_size(progress_bar, 180, 20);
    lv_obj_align(progress_bar, LV_ALIGN_TOP_MID, 0, 10);
    
    // 控制按钮
    const char* btns[] = {LV_SYMBOL_PLAY, LV_SYMBOL_PAUSE, LV_SYMBOL_CLOSE};
    for(uint8_t i=0; i<3; i++) {
        lv_obj_t* btn = lv_btn_create(media_cont);
        lv_obj_align(btn, LV_ALIGN_BOTTOM_MID, i*70-70, -10);
        lv_obj_t* label = lv_label_create(btn);
        lv_label_set_text(label, btns[i]);
        lv_obj_add_event_cb(btn, control_event, LV_EVENT_CLICKED, NULL);
    }
}
