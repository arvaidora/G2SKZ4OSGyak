#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>

#define BUFFER_SIZE 255

int main(void) {
    char buffer[BUFFER_SIZE];
    do 
    {
        printf(">");
        fgets(buffer, BUFFER_SIZE,  stdin);
        system(buffer);
    }
    while (1);

    return 0;
}
