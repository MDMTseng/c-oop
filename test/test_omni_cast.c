#include <stdio.h>
#include <stdlib.h>
#include "Shape.h"
#include "Circle.h"
#include "Sphere.h"

int main(void) {
    int pass = 1;

    /* Test 1: CxOOP_OMNI gives access to private members */
    Shape s = {0};
    CONSTRUCTOR_Shape(&s);

    __OMNI__Shape *os = CxOOP_OMNI(Shape, &s);
    os->_id = 99;
    if (os->_id != 99) {
        printf("FAIL: OMNI cast cannot write private member\n");
        pass = 0;
    } else {
        printf("PASS: OMNI cast can access private members\n");
    }

    /* Test 2: CxOOP_OMNI preserves public members */
    s.name = "test";
    if (os->name != s.name) {
        printf("FAIL: OMNI cast lost public member value\n");
        pass = 0;
    } else {
        printf("PASS: OMNI cast preserves public members\n");
    }

    /* Test 3: CxOOP_OMNI on child class with SUPER method */
    Sphere sp = {0};
    CONSTRUCTOR_Sphere(&sp);
    sp.radius = 2.0;

    __OMNI__Sphere *osp = CxOOP_OMNI(Sphere, &sp);
    double super_area = osp->SUPER_area((void*)osp);
    double expected = 3.14159265 * 2.0 * 2.0;
    if (super_area < expected - 0.01 || super_area > expected + 0.01) {
        printf("FAIL: SUPER_area via OMNI returned %.4f, expected %.4f\n", super_area, expected);
        pass = 0;
    } else {
        printf("PASS: SUPER_area accessible via OMNI cast\n");
    }

    DESTRUCTOR_Sphere(&sp);
    DESTRUCTOR_Shape(&s);

    if (!pass) { printf("\nSOME TESTS FAILED\n"); return EXIT_FAILURE; }
    printf("\nALL TESTS PASSED\n");
    return EXIT_SUCCESS;
}
