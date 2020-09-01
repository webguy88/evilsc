#include <stdio.h>
#include <stdlib.h>
#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include "evilpng.h"

int main(int argc, char *argv[])
{
    // Get display and window attributes
    Display *display = XOpenDisplay(NULL);
    Window root = RootWindow(display, DefaultScreen(display));
    XWindowAttributes attr;
    XGetWindowAttributes(display, root, &attr);

    // Get image
    XImage *ximage = XGetImage(display, root, 0, 0, attr.width, attr.height, AllPlanes, ZPixmap);

    // Getting pixels


	bitmap_t image;
	image.width = ximage->width;
	image.height = ximage->height;
	image.pixels = calloc(image.width * image.height, sizeof(pixel_t));

	for(int y = 0; y < ximage->height; y++){
        for(int x = 0; x < ximage->width; x++){
            unsigned long pixel = XGetPixel(ximage, x, y);
            unsigned char blue = pixel&ximage->blue_mask;
            unsigned char green = (pixel&ximage->green_mask) >> 8;
            unsigned char red = (pixel&ximage->red_mask) >> 16;

            pixel_t *px = &image.pixels[y * image.width + x];
			px->red = red;
			px->green = green;
			px->blue = blue;
        }
    }


	save_png_to_file(&image, "evil.png");
	free(image.pixels);

    if (ximage == NULL) {
        fprintf(stderr, "Error: cannot get root window image.");
        exit(1);
    }

    XCloseDisplay(display);
}
