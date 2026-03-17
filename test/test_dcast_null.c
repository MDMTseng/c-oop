#include <stdio.h>
#include <stdlib.h>
#include "Shape.h"
#include "Circle.h"
#include "Sphere.h"

int main(void) {
    int pass = 1;

    /* Test 1: DCAST with valid pointer */
    Circle c = {0};
    CONSTRUCTOR_Circle(&c);
    Shape *p = CxOOP_DCAST(Shape, &c);
    if (p == NULL) {
        printf("FAIL: DCAST valid pointer returned NULL\n");
        pass = 0;
    } else {
        printf("PASS: DCAST valid pointer returned non-NULL\n");
    }

    /* Test 2: DCAST with NULL pointer should return NULL */
    Circle *null_child = NULL;
    Shape *result = CxOOP_DCAST(Shape, null_child);
    if (result != NULL) {
        printf("FAIL: DCAST NULL pointer returned non-NULL\n");
        pass = 0;
    } else {
        printf("PASS: DCAST NULL pointer returned NULL\n");
    }

    /* Test 3: DCAST shorthand macro */
    Sphere sp = {0};
    CONSTRUCTOR_Sphere(&sp);
    Shape *dp = DCAST(Shape, &sp);
    if (dp == NULL) {
        printf("FAIL: DCAST shorthand returned NULL for valid ptr\n");
        pass = 0;
    } else {
        printf("PASS: DCAST shorthand works for valid ptr\n");
    }

    sp.Destroy(&sp);
    c.Destroy(&c);

    if (!pass) {
        printf("\nSOME TESTS FAILED\n");
        return EXIT_FAILURE;
    }
    printf("\nALL TESTS PASSED\n");
    return EXIT_SUCCESS;
}
