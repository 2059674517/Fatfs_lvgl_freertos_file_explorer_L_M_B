/* image_viewer.h */
#ifndef IMAGE_VIEWER_H
#define IMAGE_VIEWER_H

#include "lvgl.h"

void image_viewer_open(const char* folder_path, const char* filename);
void image_viewer_close(void);

#endif
