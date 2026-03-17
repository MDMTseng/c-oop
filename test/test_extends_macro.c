#include <stdio.h>
#include <stdlib.h>
#include "PARENT_OBJ.h"
#include "CHILD_OBJ.h"
#include "DECEN_OBJ.h"

int main(void) {
    int pass = 1;

    /* Test 1: CxOOP_EXTENDS_ — CHILD_OBJ inherits PARENT_OBJ members */
    CHILD_OBJ c = {0};
    CONSTRUCTOR_CHILD_OBJ(&c);
    c.pub = 42;
    PARENT_OBJ *pc = DCAST(PARENT_OBJ, &c);
    if (pc->pub != 42) {
        printf("FAIL: EXTENDS_ — parent member not accessible via DCAST\n");
        pass = 0;
    } else {
        printf("PASS: EXTENDS_ — parent member accessible via DCAST\n");
    }

    /* Test 2: CxOOP_EXTENDS2_ — DECEN_OBJ inherits through 2 levels */
    DECEN_OBJ d = {0};
    CONSTRUCTOR_DECEN_OBJ(&d);
    d.pub = 99;
    PARENT_OBJ *pd = DCAST(PARENT_OBJ, &d);
    if (pd->pub != 99) {
        printf("FAIL: EXTENDS2_ — grandparent member not accessible via DCAST\n");
        pass = 0;
    } else {
        printf("PASS: EXTENDS2_ — grandparent member accessible via DCAST\n");
    }

    /* Test 3: Polymorphic dispatch works through both EXTENDS levels */
    c.pub = 10;
    d.pub = 10;
    pc = DCAST(PARENT_OBJ, &c);
    pd = DCAST(PARENT_OBJ, &d);

    int child_result = pc->DoAction(pc);
    int decen_result = pd->DoAction(pd);

    if (child_result != 20) {
        printf("FAIL: EXTENDS_ polymorphism — got %d expected 20\n", child_result);
        pass = 0;
    } else {
        printf("PASS: EXTENDS_ polymorphism works (10*2=20)\n");
    }

    if (decen_result != 40) {
        printf("FAIL: EXTENDS2_ polymorphism — got %d expected 40\n", decen_result);
        pass = 0;
    } else {
        printf("PASS: EXTENDS2_ polymorphism works (10->20->40)\n");
    }

    /* Test 4: Virtual Destroy works through both EXTENDS levels */
    pd->Destroy(pd);
    pc->Destroy(pc);
    printf("PASS: virtual Destroy through EXTENDS_/EXTENDS2_ chain\n");

    if (!pass) {
        printf("\nSOME TESTS FAILED\n");
        return EXIT_FAILURE;
    }
    printf("\nALL TESTS PASSED\n");
    return EXIT_SUCCESS;
}
