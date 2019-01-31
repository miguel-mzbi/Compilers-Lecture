#include <stdio.h>
#include <stdlib.h>

int main(int argc, char const *argv[]) {
    
    printf("%.2f °F\n", atof(argv[argc-1]));
    printf("%.2f °C\n", (5.0/9)*(atof(argv[argc-1])-32));

    return 0;
}