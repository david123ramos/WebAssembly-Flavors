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


EMSCRIPTEN_BINDINGS(my_module) {
    function("resizeNearestNeighboor", &resizeNearestNeighboor);
}


// em++ --bind -O3 bindTest.cpp