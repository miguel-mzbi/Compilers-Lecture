#include <stdio.h>

#define GRAVITY 9.81

int main(int argc, char const *argv[]) {
    float result = 1000/GRAVITY;
    printf("This is an example of a macro\n");
    printf("%f\n", result);
    return 0;
}
