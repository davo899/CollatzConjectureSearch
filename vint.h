#include <stdbool.h>

struct vNatural {
    int length;
    int digits[];
};

extern struct vNatural* CONST_ZERO;
extern struct vNatural* CONST_ONE;

struct vNatural* addVNaturals();
struct vNatural* smallToVNatural();
struct vNatural* half();
bool isEven();
bool endsWithZeroes();
int compare();
void printVNatural();

