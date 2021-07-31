#include <stdlib.h>
#include <stdint.h>
#include "emscripten.h"

int result[2];

extern "C" {


  uint8_t* EMSCRIPTEN_KEEPALIVE createBuffer(int w, int h){
      return (uint8_t *) malloc(w * h * 4 * sizeof(uint8_t));
  }

  void EMSCRIPTEN_KEEPALIVE clearBuffer(uint8_t * p){
      free(p);
  }

 

  void EMSCRIPTEN_KEEPALIVE encode(int ptr , int* buffer, int w, int h, int w2, int h2) {

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

            buffer[dstIndex]     = img[srcIndex];
            buffer[dstIndex + 1] = img[srcIndex + 1];
            buffer[dstIndex + 2] = img[srcIndex + 2];
            buffer[dstIndex + 3] = img[srcIndex + 3];
            dstIndex += 4;
        }
    }
  }


  int EMSCRIPTEN_KEEPALIVE get_result_pointer() {
    return result[0];
  }

  int EMSCRIPTEN_KEEPALIVE get_result_size() {
    return result[1];
  }

}
