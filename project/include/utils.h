#ifndef PIX2ASCII_UTILS_H
#define PIX2ASCII_UTILS_H

typedef struct {
    int n_rows;
    int n_cols;
    char *characters;
} ScreenData;

ScreenData *InitializeData(int n_rows, int n_cols);
int free_screen(ScreenData *screen);


#endif //PIX2ASCII_UTILS_H
