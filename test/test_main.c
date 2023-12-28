#include "test.h"

int main(int argc, char * argv[]){
    (void)argc;
    (void)argv;

    printf("Running stack tests\r\n");
    test_stack();
    printf("Running ringbuffer tests\r\n");
    test_ringbuffer();

    return 0;
}