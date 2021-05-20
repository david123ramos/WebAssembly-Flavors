#include <stdio.h>

int main() {

    FILE *file = fopen("files/test.txt", "r");

    if(!file){
        puts("Não foi possível abrir o arquivo");
        return -1;
    }

    while (!feof(file)) {
        char letter = fgetc(file);

        if(letter != EOF) {
            putchar(letter);
        }

    }
    fclose(file);
    return 0;
}

//emcc files/file.cpp -o files/files.html --preload-file files/test.txt -s EXIT_RUNTIME=1