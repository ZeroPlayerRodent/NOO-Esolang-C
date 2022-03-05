#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

unsigned char tape[10000] = {0}; //You can change this to better fit your program's size
unsigned char *ptr = tape;

int stack1[10000] = {0};
int stack2[10000] = {0};

int top1 = -1;
int top2 = -1;

int acc = 0;

int randomnumber;

int last = 0;

void pop1() { top1 = top1 - 1; }

void pop2() { top2 = top2 - 1; }

void push1(int data) {
    top1 = top1 + 1;
    stack1[top1] = data;
}

void push2(int data) {
    top2 = top2 + 1;
    stack2[top2] = data;
}

void interpret(char *input) {
    char current_char;
    size_t i;
    size_t loop;

    for (i = 0; input[i] != 0; i++) {
        current_char = input[i];
        if (current_char == 'N') {
            ++ptr;
        } else if (current_char == 'O') {
            ++*ptr;
        }
    }
}

int main(int argc, char **argv) {
    srand(time(NULL));

    if (argc < 2)
        puts("No file given."), exit(0);
    FILE *file = fopen(argv[1], "r");
    if (file == NULL)
        puts("File does not exist."), exit(0);
    if (fseek(file, 0, SEEK_END) != 0)
        puts("INSERT VAGUE ERROR HERE"), exit(0);
    int posn = ftell(file);
    if (posn == -1)
        puts("INSERT VAGUE ERROR HERE"), exit(0);
    rewind(file);
    char *fileconts = malloc(posn);
    if (fileconts == NULL)
        puts("INSERT VAGUE ERROR HERE"), exit(0);
    for (int i = 0, c; EOF != (c = fgetc(file)); fileconts[i] = c, i++)
        ;
    fclose(file);
    interpret(fileconts);

    ptr = tape;
    while (1) {
        ++ptr;
        //printf("ptr is %d\n", *ptr);
        if (*ptr == 10 && stack1[top1] == acc) {
            ptr+=2;
        } if (*ptr == 11 && stack1[top1] != acc) {
            ptr+=2;
        } if (*ptr == 0) {
            acc += 1;
        } if (*ptr == 1) {
            stack1[top1] += 1;
        } if (*ptr == 2) {
            stack1[top1] += 10;
        } if (*ptr == 3) {
            putchar(stack1[top1]);
        } if (*ptr == 4) {
            stack1[top1] = getchar();
        } if (*ptr == 5) {
            ptr -= acc;
            // if (*ptr >= 5) {
            //     ptr--;
            // }
        } if (*ptr == 6) {
            push1(0);
        } if (*ptr == 7) {
            randomnumber = rand() % stack1[top1];
            top1 = top1 - randomnumber;
        } if (*ptr == 8) {
            ptr += acc;
        } if (*ptr == 9) {
            pop1();
        } if (*ptr == 12) {
            acc -= 1;
        } else if (*ptr == 13) {
            acc = 0;
        } if (*ptr == 14) {
            acc = stack1[top1];
        } if (*ptr == 15) {
            push1(acc);
        } if (*ptr == 16) {
            printf("%d", stack1[top1]);
        } if (*ptr == 17) {
            push2(stack1[top1]);
        } if (*ptr == 18) {
            push1(stack2[top2]);
        } if (*ptr == 19) {
            pop2();
        } if (*ptr == 20) {
            stack1[top1] -= 1;
        } if (*ptr == 21) {
            return 0;
        }
    }
}
