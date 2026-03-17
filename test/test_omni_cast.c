#include <stdio.h>
#include <stdlib.h>
#include "PARENT_OBJ.h"
#include "CHILD_OBJ.h"
#include "DECEN_OBJ.h"

int main(void) {
    int pass = 1;

    /* Test 1: CxOOP_OMNI gives access to private members */
    PARENT_OBJ p = {0};
    CONSTRUCTOR_PARENT_OBJ(&p);
    p.pub = 42;

    __OMNI__PARENT_OBJ *op = CxOOP_OMNI(PARENT_OBJ, &p);
    op->__priv = 99;

    if (op->pub != 42) {
        printf("FAIL: OMNI cast lost public member value\n");
        pass = 0;
    } else {
        printf("PASS: OMNI cast preserves public members\n");
    }

    if (op->__priv != 99) {
        printf("FAIL: OMNI cast cannot write private member\n");
        pass = 0;
    } else {
        printf("PASS: OMNI cast can access private members\n");
    }

    /* Test 2: CxOOP_OMNI on child class with override method */
    CHILD_OBJ c = {0};
    CONSTRUCTOR_CHILD_OBJ(&c);
    c.pub = 50;

    __OMNI__CHILD_OBJ *oc = CxOOP_OMNI(CHILD_OBJ, &c);
    int super_result = oc->SUPER_DoAction((void*)oc);
    if (super_result != 50) {
        printf("FAIL: SUPER_DoAction via OMNI returned %d, expected 50\n", super_result);
        pass = 0;
    } else {
        printf("PASS: SUPER_DoAction accessible via OMNI cast\n");
    }

    /* Test 3: CxOOP_OMNI on descendant class */
    DECEN_OBJ d = {0};
    CONSTRUCTOR_DECEN_OBJ(&d);
    d.pub = 10;

    __OMNI__DECEN_OBJ *od = CxOOP_OMNI(DECEN_OBJ, &d);
    int d_super = od->SUPER_DoAction((void*)od);
    if (d_super != 20) {
        printf("FAIL: DECEN SUPER_DoAction via OMNI returned %d, expected 20\n", d_super);
        pass = 0;
    } else {
        printf("PASS: DECEN SUPER_DoAction accessible via OMNI cast\n");
    }

    DESTRUCTOR_DECEN_OBJ(&d);
    DESTRUCTOR_CHILD_OBJ(&c);
    DESTRUCTOR_PARENT_OBJ(&p);

    if (!pass) {
        printf("\nSOME TESTS FAILED\n");
        return EXIT_FAILURE;
    }
    printf("\nALL TESTS PASSED\n");
    return EXIT_SUCCESS;
}
