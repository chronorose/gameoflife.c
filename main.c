#include <stdio.h>
#include <stdlib.h>
#define WIDTH 80
#define HEIGHT 30

int ** memall() {
    int ** input = malloc(sizeof(char *) * HEIGHT);
    for(int i = 0; i < WIDTH; i++) input[i] = malloc(sizeof(char));
    for(int i = 0; i < HEIGHT; i++) {
        for(int j = 0; j < WIDTH; j++) {
            input[i][j] = 1;
        }
    }
    return input;
}

void output(int ** input) {
    for(int i = 0; i < HEIGHT; i++) {
        for(int j = 0; j < WIDTH; j++) {
            printf("%d", input[i][j]);
        }
        printf("\n");
    }
}

int main() {
    int ** input;
    input = memall();
    output(input);
    free(input);
    return 0;
}
