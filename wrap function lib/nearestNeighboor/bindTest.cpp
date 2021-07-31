#include <stdlib.h>
#include <stdint.h>
#include <emscripten/bind.h>
#include <emscripten/val.h>


using namespace emscripten;


val resizeNearestNeighboor(int ptr , int len, int w, int h, int w2, int h2) {

    uint8_t *img;
    img = (uint8_t *) ptr;

    int xFactor = w / w2;
    int dstPixels[h2 * w2 * 4];


    int yFactor = h / h2;
    int dstIndex = 0; 
    int srcIndex, x, y, offset;

    for (y = 0; y < h2; y += 1) {
        offset = ((y * yFactor) | 0) * w;

        for (x = 0; x < w2; x += 1) {
            srcIndex = (offset + x * xFactor) << 2;

            dstPixels[dstIndex]     = img[srcIndex];
            dstPixels[dstIndex + 1] = img[srcIndex + 1];
            dstPixels[dstIndex + 2] = img[srcIndex + 2];
            dstPixels[dstIndex + 3] = img[srcIndex + 3];
            dstIndex += 4;
        }
    }
    
   return val( typed_memory_view(  h2 * w2 * 4, dstPixels));
}

val trimCanvas(int ptr , int l, int w, int h) {
    uint8_t *pixels;
    pixels = (uint8_t *) ptr;
    double top = -1, left = -1, right = -1, bottom = -1, x, y;
    double res[4];
    int i;

    // Iterate over every pixel to find the highest
    // and where it ends on every axis ()
    for (i = 0; i < l; i += 4) {
        if (pixels[i + 3] != 0) {
            x = (i / 4) % w;
            y = ~~((i / 4) / w);

            if (top == -1) {
                top = y;
            }

            if (left == -1) {
                left = x;
            } else if (x < left) {
                left = x;
            }

            if (right == -1) {
                right = x;
            } else if (right < x) {
                right = x;
            }

            if (bottom == -1) {
                bottom = y;
            } else if (bottom < y) {
                bottom = y;
            }
        }
    }

    // Calculate the height and width of the content
    int trimHeight = bottom - top;
    int trimWidth = right - left;

    res[0] = left;
    res[1] = top;
    res[2] = trimWidth;
    res[3] = trimHeight;

    return val( typed_memory_view( 4, res));
}


EMSCRIPTEN_BINDINGS(my_module) {
    function("resizeNearestNeighboor", &resizeNearestNeighboor);
    function("trimCanvas", &trimCanvas);
}


// em++ --bind -O3 bindTest.cpp