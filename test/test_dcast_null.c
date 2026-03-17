#include <stdio.h>
#include <stdlib.h>
#include "PARENT_OBJ.h"
#include "CHILD_OBJ.h"
#include "DECEN_OBJ.h"

int main(void) {
    int pass = 1;

    /* Test 1: DCAST with valid pointer */
    CHILD_OBJ c = {0};
    CONSTRUCTOR_CHILD_OBJ(&c);
    PARENT_OBJ *p = CxOOP_DCAST(PARENT_OBJ, &c);
    if (p == NULL) {
        printf("FAIL: DCAST valid pointer returned NULL\n");
        pass = 0;
    } else {
        printf("PASS: DCAST valid pointer returned non-NULL\n");
    }

    /* Test 2: DCAST with NULL pointer should return NULL, not crash */
    CHILD_OBJ *null_child = NULL;
    PARENT_OBJ *result = CxOOP_DCAST(PARENT_OBJ, null_child);
    if (result != NULL) {
        printf("FAIL: DCAST NULL pointer returned non-NULL\n");
        pass = 0;
    } else {
        printf("PASS: DCAST NULL pointer returned NULL\n");
    }

    /* Test 3: DCAST shorthand macro */
    DECEN_OBJ d = {0};
    CONSTRUCTOR_DECEN_OBJ(&d);
    PARENT_OBJ *dp = DCAST(PARENT_OBJ, &d);
    if (dp == NULL) {
        printf("FAIL: DCAST shorthand returned NULL for valid ptr\n");
        pass = 0;
    } else {
        printf("PASS: DCAST shorthand works for valid ptr\n");
    }

    DESTRUCTOR_DECEN_OBJ(&d);
    DESTRUCTOR_CHILD_OBJ(&c);

    if (!pass) {
        printf("\nSOME TESTS FAILED\n");
        return EXIT_FAILURE;
    }
    printf("\nALL TESTS PASSED\n");
    return EXIT_SUCCESS;
}
