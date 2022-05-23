#ifndef PROJECT_INCLUDE_FRAME_UTILS_H_
#define PROJECT_INCLUDE_FRAME_UTILS_H_

#include <ncurses.h>

#include "utils.h"

#define RED_DEPTH 6
#define GREEN_DEPTH 7
#define BLUE_DEPTH 6
#define RED_MULTIPLIER 42   // RED_DEPTH * GREEN_DEPTH
#define GREEN_MULTIPLIER 6  // GREEN_DEPTH
#define BLUE_MULTIPLIER 1
#define COLOR_6_UNITS_MULTIPLIER (1000 / (6 - 1))
#define COLOR_7_UNITS_MULTIPLIER (1000 / (7 - 1))

unsigned char average_chanel_intensity(const unsigned char *video_frame,
                                       unsigned int frame_width,
                                       unsigned long cur_pixel_row,  unsigned long cur_pixel_col,
                                       unsigned long row_step, unsigned long col_step);

unsigned char yuv_intensity(const unsigned char *video_frame,
                            unsigned int frame_width,
                            unsigned long cur_pixel_row,  unsigned long cur_pixel_col,
                            unsigned long row_step, unsigned long col_step);

typedef unsigned char (*region_intensity_t)(const unsigned char *video_frame,
                                            unsigned int frame_width,
                                            unsigned long cur_pixel_row,  unsigned long cur_pixel_col,
                                            unsigned long row_step, unsigned long col_step);

void draw_frame(const unsigned char *video_frame,
                unsigned int frame_width,
                unsigned int trimmed_height,
                unsigned int trimmed_width,
                unsigned int row_downscale_coef,
                unsigned int col_downscale_coef,
                unsigned int left_border_indent,
                const char char_set[],
                unsigned int max_char_set_index,
                region_intensity_t get_region_intensity);

void draw_color_frame(const unsigned char *video_frame,
                      unsigned int frame_width,
                      unsigned int trimmed_height,
                      unsigned int trimmed_width,
                      unsigned int row_downscale_coef,
                      unsigned int col_downscale_coef,
                      unsigned int left_border_indent,
                      const char char_set[],
                      unsigned int max_char_set_index,
                      region_intensity_t get_region_intensity);

#endif  // PROJECT_INCLUDE_FRAME_UTILS_H_
