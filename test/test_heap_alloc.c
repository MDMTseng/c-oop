#include <stdio.h>
#include <stdlib.h>
#include "Shape.h"
#include "Circle.h"
#include "Sphere.h"

int main(void) {
    int pass = 1;

    /* Test 1: Heap-allocated Shape */
    Shape *hs = (Shape*)calloc(1, sizeof(Shape));
    CONSTRUCTOR_Shape(hs);
    if (hs->area(hs) != 0.0) {
        printf("FAIL: heap Shape area != 0\n"); pass = 0;
    } else {
        printf("PASS: heap Shape works correctly\n");
    }
    DESTRUCTOR_Shape(hs);
    free(hs);

    /* Test 2: Heap-allocated Circle with polymorphism */
    Circle *hc = (Circle*)calloc(1, sizeof(Circle));
    CONSTRUCTOR_Circle(hc);
    hc->radius = 1.0;
    Shape *as_shape = DCAST(Shape, hc);
    double result = as_shape->area(as_shape);
    double expected = 3.14159265;
    if (result < expected - 0.01 || result > expected + 0.01) {
        printf("FAIL: heap Circle area got %.4f, expected %.4f\n", result, expected); pass = 0;
    } else {
        printf("PASS: heap Circle polymorphism works\n");
    }
    DESTRUCTOR_Circle(hc);
    free(hc);

    /* Test 3: Heap-allocated Sphere through full chain */
    Sphere *hsp = (Sphere*)calloc(1, sizeof(Sphere));
    CONSTRUCTOR_Sphere(hsp);
    hsp->radius = 1.0;
    Shape *as_shape2 = DCAST(Shape, hsp);
    double result2 = as_shape2->area(as_shape2);
    double expected2 = 4.0 * 3.14159265;
    if (result2 < expected2 - 0.01 || result2 > expected2 + 0.01) {
        printf("FAIL: heap Sphere area got %.4f, expected %.4f\n", result2, expected2); pass = 0;
    } else {
        printf("PASS: heap Sphere full inheritance chain works\n");
    }
    DESTRUCTOR_Sphere(hsp);
    free(hsp);

    /* Test 4: NULL DCAST on heap pointer */
    Circle *null_ptr = NULL;
    Shape *null_result = CxOOP_DCAST(Shape, null_ptr);
    if (null_result != NULL) {
        printf("FAIL: DCAST NULL heap pointer returned non-NULL\n"); pass = 0;
    } else {
        printf("PASS: DCAST NULL heap pointer returns NULL\n");
    }

    if (!pass) { printf("\nSOME TESTS FAILED\n"); return EXIT_FAILURE; }
    printf("\nALL TESTS PASSED\n");
    return EXIT_SUCCESS;
}
