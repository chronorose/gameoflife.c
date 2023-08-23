#include <stdio.h>
#include <stdlib.h>
#define WIDTH 40
#define HEIGHT 20

char ** memall() {
    char ** input = malloc(sizeof(char *) * HEIGHT);
    for(int i = 0; i < HEIGHT; i++) input[i] = malloc(sizeof(char) * (WIDTH + 1));
    return input;
}

void init(char ** input) {
    for(int i = 0; i < HEIGHT; i++) {
        for(int j = 0; j < WIDTH + 1; j++) {
            scanf("%c", &(input)[i][j]);
        }
    }
}

void output(char ** input) {
    for(int i = 0; i < HEIGHT; i++) {
        for(int j = 0; j < WIDTH; j++) {
            printf("%c", input[i][j]);
        }
        printf("\n");
    }
}

int main() {
    char ** input;
    /* for(int i = 0; i < HEIGHT; i++) { */
    /*     for(int j = 0; j < WIDTH; j++) { */
    /*         printf("*"); */
    /*     } */
    /*     printf("\n"); */
    /* } */
    input = memall();
    init(input);
    output(input);
    for(int i = 0; i < HEIGHT; i++) free(input[i]);
    free(input);
    return 0;
}
