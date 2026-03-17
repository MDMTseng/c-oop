#include <stdio.h>
#include <stdlib.h>
#include "PARENT_OBJ.h"
#include "CHILD_OBJ.h"
#include "DECEN_OBJ.h"

int main(void) {
    int pass = 1;

    /* Test 1: CxOOP_ALLOC returns non-NULL typed pointer */
    PARENT_OBJ *p = CxOOP_ALLOC(PARENT_OBJ);
    if (!p) {
        printf("FAIL: CxOOP_ALLOC(PARENT_OBJ) returned NULL\n");
        return EXIT_FAILURE;
    }
    CONSTRUCTOR_PARENT_OBJ(p);
    p->pub = 42;
    if (p->pub != 42 || p->DoAction(p) != 42) {
        printf("FAIL: alloc'd PARENT_OBJ not functional\n");
        pass = 0;
    } else {
        printf("PASS: CxOOP_ALLOC + construct PARENT_OBJ\n");
    }
    CxOOP_DELETE(p);
    printf("PASS: CxOOP_DELETE PARENT_OBJ\n");

    /* Test 2: CxOOP_ALLOC + CxOOP_DELETE with child class */
    CHILD_OBJ *c = CxOOP_ALLOC(CHILD_OBJ);
    if (!c) {
        printf("FAIL: CxOOP_ALLOC(CHILD_OBJ) returned NULL\n");
        return EXIT_FAILURE;
    }
    CONSTRUCTOR_CHILD_OBJ(c);
    c->pub = 30;
    PARENT_OBJ *as_parent = DCAST(PARENT_OBJ, c);
    int result = as_parent->DoAction(as_parent);
    if (result != 60) {
        printf("FAIL: alloc'd CHILD_OBJ DoAction got %d, expected 60\n", result);
        pass = 0;
    } else {
        printf("PASS: CxOOP_ALLOC CHILD_OBJ polymorphism (30*2=60)\n");
    }
    CxOOP_DELETE(as_parent);  /* virtual destroy through base ptr + free */
    printf("PASS: CxOOP_DELETE through base pointer\n");

    /* Test 3: CxOOP_DELETE with NULL is safe */
    PARENT_OBJ *null_ptr = NULL;
    CxOOP_DELETE(null_ptr);
    printf("PASS: CxOOP_DELETE(NULL) is safe\n");

    /* Test 4: Full polymorphic array with ALLOC/DELETE */
    PARENT_OBJ *hp = CxOOP_ALLOC(PARENT_OBJ);
    CONSTRUCTOR_PARENT_OBJ(hp);
    CHILD_OBJ *hc = CxOOP_ALLOC(CHILD_OBJ);
    CONSTRUCTOR_CHILD_OBJ(hc);
    DECEN_OBJ *hd = CxOOP_ALLOC(DECEN_OBJ);
    CONSTRUCTOR_DECEN_OBJ(hd);

    hp->pub = hc->pub = hd->pub = 10;
    PARENT_OBJ *arr[] = {hp, DCAST(PARENT_OBJ, hc), DCAST(PARENT_OBJ, hd)};

    int expected[] = {10, 20, 40};
    int i;
    for (i = 0; i < 3; i++) {
        int val = arr[i]->DoAction(arr[i]);
        if (val != expected[i]) {
            printf("FAIL: arr[%d] got %d, expected %d\n", i, val, expected[i]);
            pass = 0;
        }
    }
    if (pass) {
        printf("PASS: polymorphic array dispatch correct\n");
    }

    for (i = 0; i < 3; i++) {
        CxOOP_DELETE(arr[i]);
    }
    printf("PASS: CxOOP_DELETE polymorphic array\n");

    if (!pass) {
        printf("\nSOME TESTS FAILED\n");
        return EXIT_FAILURE;
    }
    printf("\nALL TESTS PASSED\n");
    return EXIT_SUCCESS;
}
