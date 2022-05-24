#include <stdio.h>
#include <stdlib.h>

#include "vint.h"
#include "vintcollatz.h"

void writeBinFile(filename, buffer, n)
char filename[];
unsigned char buffer[];
int n;
{
    FILE *write_ptr;

    write_ptr = fopen(filename,"wb");  // w for write, b for binary

    fwrite(buffer,n,1,write_ptr); // write 10 bytes from our buffer
}

void readBinFile(filename, n)
char filename[];
int n;
{
    unsigned char buffer[n];
    FILE *ptr;

    ptr = fopen("test.bin","rb");  // r for read, b for binary

    fread(buffer,n,1,ptr);
}

void maxCollatzIterator()
{
    int len = 1000;
    struct vNatural* maxCollatz;
    struct vNatural* n = malloc(sizeof(struct vNatural) + (len*sizeof(int)));
    n->length = len;

    for (int i = 0; i < len; i++) {
        n->digits[i] = 9;
    }

    while(1 == 1) {
        printVNatural(n);

        maxCollatz = vint_max_collatz(n);
        n = addVNaturals(maxCollatz, CONST_ONE);
        free(maxCollatz);

        if (compare(n, CONST_ZERO) == -1) {
            printVNatural(n);
            break;
        }
    }
}

void collatzIterator()
{
    int len = 200;
    struct vNatural* n = malloc(sizeof(struct vNatural) + (len*sizeof(int)));
    n->length = len;

    for (int i = 0; i < len; i++) {
        n->digits[i] = 9;
    }

    while(1 == 1) {
        if (endsWithZeroes(n, 2)) {
            printVNatural(n);
        }

        struct vNatural* prev = n;
        n = addVNaturals(n, CONST_ONE);
        vint_collatz(prev);

        if (compare(n, CONST_ZERO) == -1) {
            printVNatural(n);
            break;
        }
    }
}

int main()
{
    CONST_ZERO = smallToVNatural(0);
    CONST_ONE = smallToVNatural(1);
    collatzIterator();
    return 0;
}


