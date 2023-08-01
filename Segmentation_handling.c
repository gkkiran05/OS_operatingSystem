#include <stdio.h>
#include <signal.h>
#include <unistd.h>

int segfault_occurred = 0;

void segfault_handler(int signum) {
    if (!segfault_occurred) {
        printf("Caught segmentation fault signal (SIGSEGV). Skipping error.\n");
        segfault_occurred = 1;
	return;
    }
}

int main() {
    struct sigaction sa;
    sa.sa_handler = segfault_handler;
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = 0;

    if (sigaction(SIGSEGV, &sa, NULL) == -1) {
        perror("Error setting up signal handler");
        return 1;
    }

    int arr[5] = {1, 2, 3, 4, 5};
    int *ptr = NULL; // Pointer pointing to the first element of the array.

    ptr += 10; // Incrementing the pointer to an illegal memory location beyond the array bounds.

    // Attempting to access the value at the new address, which is illegal.
    int value = *ptr;

    // Since the segfault_handler will set segfault_occurred to 1 when it runs,
    // the error message will be printed only once.
    if (!segfault_occurred) {
        printf("Value: %d\n", value);
    }

    return 0;
}

