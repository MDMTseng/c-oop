#include <stdio.h>
#include <stdlib.h>
#include "Shape.h"
#include "Circle.h"
#include "Sphere.h"

int main(void) {
    int pass = 1;

    /* Test 1: CxOOP_ALLOC returns non-NULL */
    Shape *hs = CxOOP_ALLOC(Shape);
    if (!hs) { printf("FAIL: CxOOP_ALLOC(Shape) returned NULL\n"); return EXIT_FAILURE; }
    CONSTRUCTOR_Shape(hs);
    if (hs->area(hs) != 0.0) { printf("FAIL: alloc'd Shape area != 0\n"); pass = 0; }
    else printf("PASS: CxOOP_ALLOC + construct Shape\n");
    CxOOP_DELETE(hs);
    printf("PASS: CxOOP_DELETE Shape\n");

    /* Test 2: CxOOP_ALLOC + CxOOP_DELETE with child class */
    Circle *hc = CxOOP_ALLOC(Circle);
    if (!hc) { printf("FAIL: CxOOP_ALLOC(Circle) returned NULL\n"); return EXIT_FAILURE; }
    CONSTRUCTOR_Circle(hc);
    hc->radius = 1.0;
    Shape *as_shape = DCAST(Shape, hc);
    double result = as_shape->area(as_shape);
    double expected = 3.14159265;
    if (result < expected - 0.01 || result > expected + 0.01) {
        printf("FAIL: alloc'd Circle area got %.4f, expected %.4f\n", result, expected); pass = 0;
    } else {
        printf("PASS: CxOOP_ALLOC Circle polymorphism works\n");
    }
    CxOOP_DELETE(as_shape);
    printf("PASS: CxOOP_DELETE through base pointer\n");

    /* Test 3: CxOOP_DELETE with NULL is safe */
    Shape *null_ptr = NULL;
    CxOOP_DELETE(null_ptr);
    printf("PASS: CxOOP_DELETE(NULL) is safe\n");

    /* Test 4: Full polymorphic array with ALLOC/DELETE */
    Shape *hp = CxOOP_ALLOC(Shape); CONSTRUCTOR_Shape(hp);
    Circle *hc2 = CxOOP_ALLOC(Circle); CONSTRUCTOR_Circle(hc2); hc2->radius = 2.0;
    Sphere *hsp = CxOOP_ALLOC(Sphere); CONSTRUCTOR_Sphere(hsp); hsp->radius = 1.0;

    Shape *arr[] = {hp, DCAST(Shape, hc2), DCAST(Shape, hsp)};

    double expected_vals[] = {0.0, 3.14159265 * 4.0, 4.0 * 3.14159265};
    int i;
    for (i = 0; i < 3; i++) {
        double val = arr[i]->area(arr[i]);
        if (val < expected_vals[i] - 0.1 || val > expected_vals[i] + 0.1) {
            printf("FAIL: arr[%d] got %.4f, expected %.4f\n", i, val, expected_vals[i]); pass = 0;
        }
    }
    if (pass) printf("PASS: polymorphic array dispatch correct\n");

    for (i = 0; i < 3; i++) CxOOP_DELETE(arr[i]);
    printf("PASS: CxOOP_DELETE polymorphic array\n");

    if (!pass) { printf("\nSOME TESTS FAILED\n"); return EXIT_FAILURE; }
    printf("\nALL TESTS PASSED\n");
    return EXIT_SUCCESS;
}
