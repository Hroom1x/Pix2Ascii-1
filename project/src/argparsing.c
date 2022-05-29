#include <stdio.h>
#include <string.h>
#include <ncurses.h>
#include <stdlib.h>

#include "argparsing.h"
#include "frame_processing.h"
#include "error.h"


typedef enum {CHARSET_SHARP, CHARSET_OPTIMAL, CHARSET_STANDART, CHARSET_LONG, CHARSET_N} t_char_set;
static charset_data_t charsets[CHARSET_N] = {
        {"@%#*+=-:. ", 9},
        {"NBUa1|^` ", 8},
        {"N@#W$9876543210?!abc;:+=-,._ ", 28},
        {"$@B%8&WM#*oahkbdpqwmZO0QLCJUYXzcvunxrjft/\\|()1{}[]?-_+~<>i!lI;:,\"^`'. ", 69}
};

typedef enum {PLAYER_OFF, PLAYER_VIDEO, PLAYER_AUDIO, PLAYER_ALL, PLAYER_COUNT} player_t;
static char *player_flags[PLAYER_COUNT] = {NULL, "-an", "-nodisp", ""};

int argparse(user_params_t *user_params, int argc, char *argv[]) {
    if (argc == 1) {
        fprintf(stderr, "Bad number of arguments!\n");
        return ARG_COUNT_ERROR;
    }
    // flags:
    // -f <Media path>
    // -c : (camera support)
    // -set [sharp | optimal | standard | long] : ascii set
    // -method [average | yuv] : grayscale conversion methods
    // -color : enable color support
    // -nl : loop video; -1 for infinite loop
    // -player [0 - off; 1 - only video; 2 - only audio; 3 - video and audio]
    // -filter [naive | gauss]
    user_params->charset_data = charsets[CHARSET_OPTIMAL];
    user_params->pixel_block_processing_method = average_chanel_intensity;
    user_params->color_flag = 0;
    user_params->n_stream_loops = 0;
    user_params->player_flag = NULL;
    user_params->kernel_update = update_gaussian;
    for (int i=1; i<argc;) {
        if (argv[i][0] != '-') {
            fprintf(stderr, "Invalid argument! Value is given without a corresponding flag!\n");
            return FLAG_ERROR;
        }

        if (!strcmp(&argv[i][1], "c")) {
            user_params->reading_type = SOURCE_CAMERA;
            ++i;
        } else if (!strcmp(&argv[i][1], "f")) {
            if (i == argc - 1 || argv[i + 1][0] == '-') {
                fprintf(stderr, "Invalid argument! File path was not given!\n");
                return FILE_PATH_ERROR;
            } else {
                user_params->reading_type = SOURCE_FILE;
                user_params->file_path = argv[i + 1];
                i += 2;
            }
        } else if (!strcmp(&argv[i][1], "set")) {
            if (i == argc - 1 || argv[i + 1][0] == '-') {
                fprintf(stderr, "Invalid argument! ASCII set is not given!\n");
                return FLAG_ERROR;
            }

            if (!strcmp(argv[i + 1], "sharp")) {
                user_params->charset_data = charsets[CHARSET_SHARP];
            } else if (!strcmp(argv[i + 1], "optimal")) {
                user_params->charset_data = charsets[CHARSET_OPTIMAL];
            } else if (!strcmp(argv[i + 1], "standard")) {
                user_params->charset_data = charsets[CHARSET_STANDART];
            } else if (!strcmp(argv[i + 1], "long")) {
                user_params->charset_data = charsets[CHARSET_LONG];
            } else {
                fprintf(stderr, "Invalid argument! Unsupported scheme!\n");
                return FLAG_ERROR;
            }
            i += 2;
        } else if (!strcmp(&argv[i][1], "method")) {
            if (i == argc - 1 || argv[i + 1][0] == '-') {
                fprintf(stderr, "Invalid argument! Color scheme is not given!\n");
                return FLAG_ERROR;
            }

            if (!strcmp(argv[i + 1], "average")) {
                user_params->pixel_block_processing_method = average_chanel_intensity;
            } else if (!strcmp(argv[i + 1], "yuv")) {
                user_params->pixel_block_processing_method = yuv_intensity;
            } else {
                fprintf(stderr, "Invalid argument! Unsupported grayscale method!\n");
                return FLAG_ERROR;
            }
            i += 2;
        } else if (!strcmp(&argv[i][1], "color")) {
            if (has_colors()) {
                fprintf(stderr, "Sorry, but your terminal doesn't support colors!\n");
                return TERMINAL_COLORS_ERROR;
            } else if (can_change_color()) {
                fprintf(stderr, "Sorry, but your terminal doesn't support color change!\n");
                return COLOR_CHANGING_ERROR;
            }
            user_params->color_flag = 1;
            ++i;
        } else if (!strcmp(&argv[i][1], "nl")) {
            user_params->n_stream_loops = atoi(argv[i + 1]);
            i += 2;
        } else if (!strcmp(&argv[i][1], "player")) {
            if (i == argc - 1 || argv[i + 1][0] == '-') {
                fprintf(stderr, "Invalid argument! Player type wasn't given!\n");
                return FLAG_ERROR;
            }

            if (!strcmp(argv[i + 1], "off")) {
                user_params->player_flag = player_flags[PLAYER_OFF];
            } else if (!strcmp(argv[i + 1], "video")) {
                user_params->player_flag = player_flags[PLAYER_VIDEO];
            } else if (!strcmp(argv[i + 1], "audio")) {
                user_params->player_flag = player_flags[PLAYER_AUDIO];
            } else if (!strcmp(argv[i + 1], "all")) {
                user_params->player_flag = player_flags[PLAYER_ALL];
            } else {
                fprintf(stderr, "Invalid argument! Unsupported player type!\n");
                return FLAG_ERROR;
            }
            i += 2;
        } else if (!strcmp(&argv[i][1], "filter")) {
            if (i == argc - 1 || argv[i + 1][0] == '-') {
                fprintf(stderr, "Invalid argument! Filter type is not given!\n");
                return FLAG_ERROR;
            }

            if (!strcmp(argv[i + 1], "naive")) {
                user_params->kernel_update = update_naive;
            } else if (!strcmp(argv[i + 1], "gauss")) {
                user_params->kernel_update = update_gaussian;
            } else {
                fprintf(stderr, "Invalid argument! Unsupported scheme!\n");
                return FLAG_ERROR;
            }
            i += 2;
        } else {
            fprintf(stderr, "Unknown flag!\n");
            return FLAG_ERROR;
        }
    }
    return SUCCESS;
}
