#include <stdio.h>
#include <stdlib.h>
#include "PARENT_OBJ.h"
#include "CHILD_OBJ.h"
#include "DECEN_OBJ.h"

int main(void) {
    int pass = 1;
    int ret;

    /* Test 1: PARENT_OBJ constructor and destructor */
    PARENT_OBJ p = {0};
    ret = CONSTRUCTOR_PARENT_OBJ(&p);
    if (ret != 0) {
        printf("FAIL: PARENT_OBJ constructor returned %d\n", ret);
        pass = 0;
    }
    ret = DESTRUCTOR_PARENT_OBJ(&p);
    if (ret != 0) {
        printf("FAIL: PARENT_OBJ destructor returned %d\n", ret);
        pass = 0;
    } else {
        printf("PASS: PARENT_OBJ construct/destruct cycle\n");
    }

    /* Test 2: CHILD_OBJ constructor and destructor */
    CHILD_OBJ c = {0};
    ret = CONSTRUCTOR_CHILD_OBJ(&c);
    if (ret != 0) {
        printf("FAIL: CHILD_OBJ constructor returned %d\n", ret);
        pass = 0;
    }
    ret = DESTRUCTOR_CHILD_OBJ(&c);
    if (ret != 0) {
        printf("FAIL: CHILD_OBJ destructor returned %d\n", ret);
        pass = 0;
    } else {
        printf("PASS: CHILD_OBJ construct/destruct cycle\n");
    }

    /* Test 3: DECEN_OBJ constructor and destructor */
    DECEN_OBJ d = {0};
    ret = CONSTRUCTOR_DECEN_OBJ(&d);
    if (ret != 0) {
        printf("FAIL: DECEN_OBJ constructor returned %d\n", ret);
        pass = 0;
    }
    ret = DESTRUCTOR_DECEN_OBJ(&d);
    if (ret != 0) {
        printf("FAIL: DECEN_OBJ destructor returned %d\n", ret);
        pass = 0;
    } else {
        printf("PASS: DECEN_OBJ construct/destruct cycle\n");
    }

    if (!pass) {
        printf("\nSOME TESTS FAILED\n");
        return EXIT_FAILURE;
    }
    printf("\nALL TESTS PASSED\n");
    return EXIT_SUCCESS;
}
