#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "vNatural.h"

struct vNatural* CONST_ZERO;
struct vNatural* CONST_ONE;

struct vNatural* addVNaturals(x, y)
struct vNatural* x;
struct vNatural* y;
{
    int minDigits, maxDigits;
    bool xLonger = x->length > y->length;
    if (xLonger) {
        minDigits = y->length;
        maxDigits = x->length;
    } else {
        minDigits = x->length;
        maxDigits = y->length;
    }

    struct vNatural* result = malloc(sizeof(struct vNatural) + ((maxDigits + 1) * sizeof(short)));
    result->length = maxDigits;

    int carry = 0;
    int i = 0;
    while(i < maxDigits) {
        if (i < minDigits) {
            int r = x->digits[i] + y->digits[i] + carry;
            if (r < 10) {
                result->digits[i] = r;
                carry = 0;
            } else {
                result->digits[i] = r - 10;
                carry = 1;
            }

        } else {
            int r;
            if (xLonger) {
                r = x->digits[i] + carry;
            } else {
                r = y->digits[i] + carry;
            }
            if (r < 10) {
                result->digits[i] = r;
                carry = 0;
            } else {
                result->digits[i] = r - 10;
                carry = 1;
            }
        }
        i++;
    }

    if (carry == 1) {
        result->digits[i] = 1;
        result->length++;
    }

    return result;
}

void printVNatural(n)
struct vNatural* n;
{
    for (int i = n->length - 1; i >= 0; i--) {
        printf("%d", n->digits[i]);
    }
    printf("\n");
}

struct vNatural* smallToVNatural(n)
int n;
{
    int digits = 1;
    int digitCheck = 10;
    while (n >= digitCheck) {
        digits++;
        digitCheck = digitCheck * 10;
    }

    struct vNatural* result = malloc(sizeof(struct vNatural) + (digits*sizeof(short)));
    result->length = digits;

    for (int i = 0; i < digits; i++) {
        result->digits[i] = n % 10;
        n = (n - (n % 10)) / 10;
    }

    return result;
}

struct vNatural* half(n)
struct vNatural* n;
{
    struct vNatural* result = malloc(sizeof(struct vNatural) + (n->length * sizeof(short)));
    result->length = n->length;

    for (int i = 0; i < n->length; i++) {
        if (n->digits[i] % 2 == 0) {
            result->digits[i] = n->digits[i] / 2;

        } else {
            result->digits[i] = (n->digits[i] - 1) / 2;
            result->digits[i-1] = result->digits[i-1] + 5;
        }
    }

    if (result->length > 1 && result->digits[result->length-1] == 0) {
        result->length--;
    }

    return result;
}

bool isEven(n)
struct vNatural* n;
{
    return n->digits[0] % 2 == 0;
}

int compare(x, y)
struct vNatural* x;
struct vNatural* y;
{
    if(x->length > y->length) {
        return 1;
    }
    if(x->length < y->length) {
        return -1;
    }

    for (int i = x->length - 1; i >= 0; i--) {
        if (x->digits[i] > y->digits[i]) {
            return 1;
        }
        if (x->digits[i] < y->digits[i]) {
            return -1;
        }
    }
    return 0;
}

bool endsWithZeroes(m, n)
struct vNatural* m;
int n;
{
    if (m->length <= n) {
        return false;
    }

    for (int i = 0; i < n; i++) {
        if (m->digits[i] != 0) {
            return false;
        }
    }

    return true;
}
