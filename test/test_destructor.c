#include <stdio.h>
#include <stdlib.h>
#include "Shape.h"
#include "Circle.h"
#include "Sphere.h"

int main(void) {
    int pass = 1;
    int ret;

    Shape s = {0};
    ret = CONSTRUCTOR_Shape(&s);
    if (ret != 0) { printf("FAIL: Shape constructor returned %d\n", ret); pass = 0; }
    ret = DESTRUCTOR_Shape(&s);
    if (ret != 0) { printf("FAIL: Shape destructor returned %d\n", ret); pass = 0; }
    else { printf("PASS: Shape construct/destruct cycle\n"); }

    Circle c = {0};
    ret = CONSTRUCTOR_Circle(&c);
    if (ret != 0) { printf("FAIL: Circle constructor returned %d\n", ret); pass = 0; }
    ret = DESTRUCTOR_Circle(&c);
    if (ret != 0) { printf("FAIL: Circle destructor returned %d\n", ret); pass = 0; }
    else { printf("PASS: Circle construct/destruct cycle\n"); }

    Sphere sp = {0};
    ret = CONSTRUCTOR_Sphere(&sp);
    if (ret != 0) { printf("FAIL: Sphere constructor returned %d\n", ret); pass = 0; }
    ret = DESTRUCTOR_Sphere(&sp);
    if (ret != 0) { printf("FAIL: Sphere destructor returned %d\n", ret); pass = 0; }
    else { printf("PASS: Sphere construct/destruct cycle\n"); }

    if (!pass) { printf("\nSOME TESTS FAILED\n"); return EXIT_FAILURE; }
    printf("\nALL TESTS PASSED\n");
    return EXIT_SUCCESS;
}
