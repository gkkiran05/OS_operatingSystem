#include <stdio.h>

int main() {
    int arr[5] = {1, 2, 3, 4, 5};
    int *ptr = &arr[0]; // Pointer pointing to the first element of the array.

    *ptr += 10; // Incrementing the pointer to an illegal memory location beyond the array bounds.

    // Attempting to access the value at the new address, which is illegal.
   //int value = *ptr;

    printf("Value: %d\n", *ptr);

    return 0;
}

