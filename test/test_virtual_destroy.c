#include <stdio.h>
#include <stdlib.h>
#include "PARENT_OBJ.h"
#include "CHILD_OBJ.h"
#include "DECEN_OBJ.h"

int main(void) {
    int pass = 1;

    /* Test 1: Destroy pointer is set after construction */
    PARENT_OBJ p = {0};
    CONSTRUCTOR_PARENT_OBJ(&p);
    if (p.Destroy == NULL) {
        printf("FAIL: PARENT_OBJ Destroy is NULL after construction\n");
        pass = 0;
    } else {
        printf("PASS: PARENT_OBJ Destroy is set\n");
    }

    CHILD_OBJ c = {0};
    CONSTRUCTOR_CHILD_OBJ(&c);
    if (c.Destroy == NULL) {
        printf("FAIL: CHILD_OBJ Destroy is NULL after construction\n");
        pass = 0;
    } else {
        printf("PASS: CHILD_OBJ Destroy is set\n");
    }

    DECEN_OBJ d = {0};
    CONSTRUCTOR_DECEN_OBJ(&d);
    if (d.Destroy == NULL) {
        printf("FAIL: DECEN_OBJ Destroy is NULL after construction\n");
        pass = 0;
    } else {
        printf("PASS: DECEN_OBJ Destroy is set\n");
    }

    /* Test 2: Virtual dispatch — Destroy through base pointer calls correct destructor */
    PARENT_OBJ *as_parent = DCAST(PARENT_OBJ, &c);
    /* Child's Destroy should differ from parent's (different destructor) */
    if (as_parent->Destroy == p.Destroy) {
        printf("FAIL: CHILD via base ptr has same Destroy as PARENT (no override)\n");
        pass = 0;
    } else {
        printf("PASS: CHILD via base ptr has overridden Destroy\n");
    }

    PARENT_OBJ *as_parent2 = DCAST(PARENT_OBJ, &d);
    if (as_parent2->Destroy == p.Destroy || as_parent2->Destroy == as_parent->Destroy) {
        printf("FAIL: DECEN via base ptr Destroy not unique\n");
        pass = 0;
    } else {
        printf("PASS: DECEN via base ptr has its own Destroy\n");
    }

    /* Test 3: Virtual destroy through base pointer doesn't crash */
    CHILD_OBJ *hc = (CHILD_OBJ*)calloc(1, sizeof(CHILD_OBJ));
    CONSTRUCTOR_CHILD_OBJ(hc);
    hc->pub = 42;
    PARENT_OBJ *base = DCAST(PARENT_OBJ, hc);
    base->Destroy(base);  /* virtual call — should invoke DESTRUCTOR_CHILD_OBJ */
    printf("PASS: virtual Destroy through base pointer (CHILD)\n");
    free(hc);

    DECEN_OBJ *hd = (DECEN_OBJ*)calloc(1, sizeof(DECEN_OBJ));
    CONSTRUCTOR_DECEN_OBJ(hd);
    hd->pub = 77;
    PARENT_OBJ *base2 = DCAST(PARENT_OBJ, hd);
    base2->Destroy(base2);  /* virtual call — should invoke DESTRUCTOR_DECEN_OBJ */
    printf("PASS: virtual Destroy through base pointer (DECEN)\n");
    free(hd);

    /* Test 4: Polymorphic array — destroy all through base pointers */
    PARENT_OBJ *hp = (PARENT_OBJ*)calloc(1, sizeof(PARENT_OBJ));
    CONSTRUCTOR_PARENT_OBJ(hp);
    CHILD_OBJ *hc2 = (CHILD_OBJ*)calloc(1, sizeof(CHILD_OBJ));
    CONSTRUCTOR_CHILD_OBJ(hc2);
    DECEN_OBJ *hd2 = (DECEN_OBJ*)calloc(1, sizeof(DECEN_OBJ));
    CONSTRUCTOR_DECEN_OBJ(hd2);

    PARENT_OBJ *arr[] = {hp, DCAST(PARENT_OBJ, hc2), DCAST(PARENT_OBJ, hd2)};
    int i;
    for (i = 0; i < 3; i++) {
        arr[i]->Destroy(arr[i]);
    }
    printf("PASS: polymorphic array virtual Destroy\n");
    free(hp);
    free(hc2);
    free(hd2);

    /* Clean up stack objects */
    d.Destroy(&d);
    c.Destroy(&c);
    p.Destroy(&p);

    if (!pass) {
        printf("\nSOME TESTS FAILED\n");
        return EXIT_FAILURE;
    }
    printf("\nALL TESTS PASSED\n");
    return EXIT_SUCCESS;
}
