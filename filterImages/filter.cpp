#include <iostream>
#include <ImageMagick-7/Magick++.h>
#include "emscripten.h"

using namespace std; 
using namespace Magick;

int result[2];

EMSCRIPTEN_KEEPALIVE
uint8_t* createBuffer(int w, int h){
    return malloc(w * h * 4 * sizeof(uint8_t));
}

EMSCRIPTEN_KEEPALIVE
void clearBuffer(uint8_t * p){
    free(p);
}



EMSCRIPTEN_KEEPALIVE
void sepia(uint8_t *img, int w, int h, float quality, char ** argv) {

    InitializeMagick(*argv);

    Image image; 
    image.read(w,h,"RGB",CharPixel, img);
    image.addNoise(GaussianNoise); 
    PixelPacket *pixels = image.getPixels(0, 0, w, h);
    int *out = malloc(w * h * 4 * sizeof(int));

    for(int i =0; i<w; i++) {
        for(int j =0; j < h; j++) {
            unsigned offset = image.channels() * (w * i + j);
            
            out[i] = pixels[offset + 0];
            out[i+1] = pixels[offset + 1];
            out[i+2] = pixels[offset + 2];

        }
    }


    result[0] = (int) out;
    result[1] = sizeof(out);
}

 
