#include <stdint.h>
#include <stdio.h>

/* A coloured pixel. */
typedef struct {
    uint8_t red;
    uint8_t green;
    uint8_t blue;
} pixel_t;

/* A picture. */
typedef struct {
    pixel_t *pixels;
    size_t width;
    size_t height;
} bitmap_t;

int save_png_to_file(bitmap_t *bitmap, const char *path);

