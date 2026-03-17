#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "PARENT_OBJ.h"
#include "CHILD_OBJ.h"
#include "DECEN_OBJ.h"

int main(void) {
    int pass = 1;

    /* Test 1: Heap-allocated PARENT_OBJ */
    PARENT_OBJ *hp = (PARENT_OBJ*)calloc(1, sizeof(PARENT_OBJ));
    if (!hp) {
        printf("FAIL: calloc PARENT_OBJ returned NULL\n");
        return EXIT_FAILURE;
    }
    CONSTRUCTOR_PARENT_OBJ(hp);
    hp->pub = 77;
    if (hp->DoAction(hp) != 77) {
        printf("FAIL: heap PARENT_OBJ DoAction returned wrong value\n");
        pass = 0;
    } else {
        printf("PASS: heap PARENT_OBJ works correctly\n");
    }
    DESTRUCTOR_PARENT_OBJ(hp);
    free(hp);

    /* Test 2: Heap-allocated CHILD_OBJ with polymorphism */
    CHILD_OBJ *hc = (CHILD_OBJ*)calloc(1, sizeof(CHILD_OBJ));
    if (!hc) {
        printf("FAIL: calloc CHILD_OBJ returned NULL\n");
        return EXIT_FAILURE;
    }
    CONSTRUCTOR_CHILD_OBJ(hc);
    hc->pub = 50;
    PARENT_OBJ *as_parent = CxOOP_DCAST(PARENT_OBJ, hc);
    int result = as_parent->DoAction(as_parent);
    if (result != 100) {
        printf("FAIL: heap CHILD_OBJ polymorphic DoAction returned %d, expected 100\n", result);
        pass = 0;
    } else {
        printf("PASS: heap CHILD_OBJ polymorphism works (50*2=100)\n");
    }
    DESTRUCTOR_CHILD_OBJ(hc);
    free(hc);

    /* Test 3: Heap-allocated DECEN_OBJ with polymorphic array */
    DECEN_OBJ *hd = (DECEN_OBJ*)calloc(1, sizeof(DECEN_OBJ));
    if (!hd) {
        printf("FAIL: calloc DECEN_OBJ returned NULL\n");
        return EXIT_FAILURE;
    }
    CONSTRUCTOR_DECEN_OBJ(hd);
    hd->pub = 10;
    PARENT_OBJ *as_parent2 = DCAST(PARENT_OBJ, hd);
    int result2 = as_parent2->DoAction(as_parent2);
    /* 10 -> PARENT returns 10, CHILD returns 10*2=20, DECEN returns 20+20=40 */
    if (result2 != 40) {
        printf("FAIL: heap DECEN_OBJ polymorphic DoAction returned %d, expected 40\n", result2);
        pass = 0;
    } else {
        printf("PASS: heap DECEN_OBJ full inheritance chain works (10->20->40)\n");
    }
    DESTRUCTOR_DECEN_OBJ(hd);
    free(hd);

    /* Test 4: NULL DCAST on heap pointer */
    CHILD_OBJ *null_ptr = NULL;
    PARENT_OBJ *null_result = CxOOP_DCAST(PARENT_OBJ, null_ptr);
    if (null_result != NULL) {
        printf("FAIL: DCAST NULL heap pointer returned non-NULL\n");
        pass = 0;
    } else {
        printf("PASS: DCAST NULL heap pointer returns NULL\n");
    }

    if (!pass) {
        printf("\nSOME TESTS FAILED\n");
        return EXIT_FAILURE;
    }
    printf("\nALL TESTS PASSED\n");
    return EXIT_SUCCESS;
}
