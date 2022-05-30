#ifndef PIX2ASCII_VIDEO_STREAM_H
#define PIX2ASCII_VIDEO_STREAM_H

#include "argparsing.h"
#define VIDEO_FRAMERATE 25

int get_frame_data(const char *filepath, int *frame_width, int *frame_height);
FILE *get_camera_stream(int frame_width, int frame_height);

FILE *get_file_stream(const char *file_path, int n_stream_loops);
int start_player(char *file_path, int n_stream_loops, char *player_type);

#endif //PIX2ASCII_VIDEO_STREAM_H
