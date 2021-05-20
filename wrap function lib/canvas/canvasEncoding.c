#include <stdlib.h>
#include <stdint.h>
#include "emscripten.h"
#include "src/webp/encode.h"

int result[2];

EMSCRIPTEN_KEEPALIVE
int version(){
    return WebPGetEncoderVersion();
}


EMSCRIPTEN_KEEPALIVE
uint8_t* createBuffer(int w, int h){
    return malloc(w * h * 4 * sizeof(uint8_t));
}

EMSCRIPTEN_KEEPALIVE
void clearBuffer(uint8_t * p){
    free(p);
}


EMSCRIPTEN_KEEPALIVE
void encode(uint8_t *img, int w, int h, float quality) {
    uint8_t * out; //buffer de saída da imagem
    size_t size; //tamanho do buffer alocado para a saída

    size = WebPEncodeRGBA(img, w, h, w * 4, quality, &out);
    result[0] = (int) out;
    result[1] = size;
}

EMSCRIPTEN_KEEPALIVE
void free_result(uint8_t* result) {
  WebPFree(result);
}

EMSCRIPTEN_KEEPALIVE
int get_result_pointer() {
  return result[0];
}

EMSCRIPTEN_KEEPALIVE
int get_result_size() {
  return result[1];
}

/*
emcc -O3 -s WASM=1 -s EXTRA_EXPORTED_RUNTIME_METHODS='["cwrap"]' \
    -I libwebp \
    webp.c \
    libwebp/src/{dec,dsp,demux,enc,mux,utils}/*.c
*/