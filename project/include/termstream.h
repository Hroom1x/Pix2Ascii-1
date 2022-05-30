#ifndef PIX2ASCII_TERMSTREAM_H
#define PIX2ASCII_TERMSTREAM_H

#include <stdio.h>
#include <stdlib.h>

#include "frame_processing.h"
#include "argparsing.h"

typedef struct {
    size_t uS_elapsed;
    size_t frame_index;
    size_t time_frame_index;
    size_t frame_desync;
    size_t cur_frame_processing_time;
} sync_info_t;

int update_terminal_size(frame_params_t *frame_params,
                         kernel_params_t *kernel_params,
                         terminal_params_t *terminal_params);

void set_color_pairs();

typedef void (*display_method_t)(const char *symbol, unsigned char r, unsigned char g, unsigned char b);

void simple_display(const char *symbol, unsigned char r, unsigned char g, unsigned char b);

void colored_display(const char *symbol, unsigned char r, unsigned char g, unsigned char b);

void draw_frame(const frame_params_t *frame_params,
                const kernel_params_t *kernel_params,
                charset_params_t charset_params,
                int left_border_indent,
                region_intensity_t get_region_intensity,
                display_method_t display_symbol);

void debug(const sync_info_t *debug_info, FILE *logs, display_method_t display_method);

#endif //PIX2ASCII_TERMSTREAM_H
