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
        for(int j = 0; j < WIDTH + 1; j++) { // + 1 so it scans newlines;;
            scanf("%c", &(input)[i][j]);
        }
    }
}

int horizontal_flag(int j) {
    if(j == 0) return -1;
    if(j == WIDTH - 1) return 1;
    return 0;
}

int vertical_flag(int i) {
    if(i == 0) return -1;
    if(i == HEIGHT - 1) return 1;
    return 0;
}

int check_right(char ** input, int i, int j) {
    int res = 0;
    for(int s = 0; s < 3; s++) {
        if(input[i - 1 + s][j + 1] == '*') res++;
    }
    return res;
}

int check_left(char ** input, int i, int j) {
    int res = 0;
    for(int s = 0; s < 3; s++) {
        if(input[i - 1 + s][j - 1] == '*') res++;
    }
    return res;
}

int check_bot(char ** input, int i, int j) {
    if(input[i + 1][j] == '*') return 1;
    return 0;
}

int check_top(char ** input, int i, int j) {
    if(input[i - 1][j] == '*') return 1;
    return 0;
}

int check_neighbours(char ** input, int i, int j) {
    int hf = horizontal_flag(j);
    int vf = vertical_flag(i);
    int sum = 0;
    if(hf == 0 && vf == 0) {
        sum += check_bot(input, i, j);
        sum += check_top(input, i, j);
        sum += check_left(input, i, j);
        sum += check_right(input, i, j);
    }
    return sum;
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
    /* for(int i = 0; i < HEIGHT; i++) { // its for generating empty field with ./main > input/empty_input */
    /*     for(int j = 0; j < WIDTH; j++) { */
    /*         printf("*"); */
    /*     } */
    /*     printf("\n"); */
    /* } */
    input = memall();
    init(input);
    output(input);
    printf("%d\n", check_neighbours(input, 10, 10));
    for(int i = 0; i < HEIGHT; i++) free(input[i]);
    free(input);
    return 0;
}
