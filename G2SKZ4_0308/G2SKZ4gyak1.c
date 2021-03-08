#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(void) {
    system("date");
    // nem létező
    system("hello");

    return 0;
}
