#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

#include "vint.h"

struct vNatural* vint_next_collatz(n)
struct vNatural* n;
{
    struct vNatural* result;
    if (isEven(n)) {
        result = half(n);
    } else {
        struct vNatural* r1 = addVNaturals(n, n);
        struct vNatural* r2 = addVNaturals(r1, n);
        result = addVNaturals(r2, CONST_ONE);

        free(r1);
        free(r2);
    }

    return result;
}

void vint_collatz(n)
struct vNatural* n;
{
    struct vNatural* prev;
    while(compare(n, CONST_ONE) != 0) {
        prev = n;
        n = vint_next_collatz(n);
        free(prev);
    }
}

struct vNatural* vint_max_collatz(n)
struct vNatural* n;
{
    struct vNatural* prev;
    struct vNatural* max = smallToVNatural(0);
    while(compare(n, CONST_ONE) != 0) {

        if (compare(n, max) == 1) {
            free(max);
            max = n;
            n = vint_next_collatz(n);

        } else {
            prev = n;
            n = vint_next_collatz(n);
            free(prev);
        }
    }

    return max;
}
