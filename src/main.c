#include <stdio.h>
#include <stdlib.h>
#include <ncurses.h>
#include <unistd.h>
#define WIDTH 40
#define HEIGHT 20

char ** memall() {
    char ** input = malloc(sizeof(char *) * HEIGHT);
    for(int i = 0; i < HEIGHT; i++) input[i] = malloc(sizeof(char) * (WIDTH + 1));
    return input;
}

void copy_arr(char ** input, char ** copy) {
    for(int i = 0; i < HEIGHT; i++) {
        for(int j = 0; j < WIDTH; j++) {
            input[i][j] = copy[i][j];
        }
    }
    for(int i = 0; i < HEIGHT; i++) free(copy[i]);
    free(copy);
}

void init(char ** input) {
    char * str = malloc(sizeof(char) * WIDTH + 2);
    FILE * pfile = fopen("input/glider", "r");
    for(int i = 0; i < HEIGHT; i++) {
        fgets(str, WIDTH + 2, pfile);
        for(int j = 0; j < WIDTH + 1; j++) {
            input[i][j] = str[j];
        }
    }
    fclose(pfile);
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

int check(char ** input, int i, int j) {
    if(input[i][j] == '*') return 1;
    return 0;
}

int check_helper(char ** input, int i, int j, int hf, int vf, int turn) {
    switch(turn) {
        case 0:
            if(hf == -1) j = WIDTH;
            if(vf == -1) i = HEIGHT;
            return check(input, i - 1, j - 1);
            break;
        case 1:
            if(vf == -1) i = HEIGHT;
            return check(input, i - 1, j);
            break;
        case 2:
            if(hf == 1) j = -1;
            if(vf == -1) i = HEIGHT;
            return check(input, i - 1, j + 1);
            break;
        case 3:
            if(hf == 1) j = -1;
            return check(input, i, j + 1);
            break;
        case 4:
            if(hf == 1) j = -1;
            if(vf == 1) i = -1;
            return check(input, i + 1, j + 1);
            break;
        case 5:
            if(vf == 1) i = -1;
            return check(input, i + 1, j);
            break;
        case 6:
            if(hf == -1) j = WIDTH;
            if(vf == 1) i = -1;
            return check(input, i + 1, j - 1);
            break;
        case 7:
            if(hf == -1) j = WIDTH;
            return check(input, i, j - 1);
            break;
    }
    return 0;
}


int check_neighbours(char ** input, int i, int j) {
    int hf = horizontal_flag(j);
    int vf = vertical_flag(i);
    int sum = 0;
    for(int turn = 0; turn < 8; turn++) {
        sum += check_helper(input, i, j, hf, vf, turn);
    }
    return sum;
}

char new_symbol(char old, int neighbours) {
    switch(old) {
        case '*':
            if(neighbours >= 2 && neighbours <= 3) return '*';
            else return '.';
            break;
        case '.':
            if(neighbours == 3) return '*';
            else return '.';
            break;
    }
    return '.';
}

void fill_new_array(char ** input) {
    char ** new_arr = memall();
    for(int i = 0; i < HEIGHT; i++) {
        for(int j = 0; j < WIDTH; j++) {
            int neighbours = check_neighbours(input, i, j);
            new_arr[i][j] = new_symbol(input[i][j], neighbours);
        }
    }
    copy_arr(input, new_arr);
}

void output(char ** input) {
    for(int i = 0; i < HEIGHT; i++) {
        for(int j = 0; j < WIDTH; j++) {
            printw("%c", input[i][j]);
        }
        printw("\n");
    }
    printw("Next turn -> R\n");
    printw("Leave -> L\n");
}

void new_turn(char ** input) {
    char c;
    while(1) {
        clear();
        output(input);
        fill_new_array(input);
        refresh();
        while(1) {
            c = getch();
            printw("%c", c);
            if(c == 'l' || c == 'L') break;
            if(c == 'r' || c == 'R') break;
        }
        if(c == 'l' || c == 'L') break;
        if(c == 'r' || c == 'R') continue;
    }
}

void setup() {
    char ** input;
    initscr();
    cbreak();
    noecho();
    input = memall();
    init(input);
    new_turn(input);
    for(int i = 0; i < HEIGHT; i++) free(input[i]);
    free(input);
}

int main() {
    setup();
    endwin();
    return 0;
}
