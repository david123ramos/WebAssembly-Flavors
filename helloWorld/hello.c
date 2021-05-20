#include <stdio.h>

int main(){
    printf("Hello, world. From WebAssembly!");
    return 0;
}

// emcc -s NO_EXIT_RUNTIME=0 hello.c -o hello.html  