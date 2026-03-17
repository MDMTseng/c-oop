#include <stdio.h>
#include <stdlib.h>
#include "Shape.h"
#include "Circle.h"
#include "Sphere.h"

int main(void) {
    int pass = 1;

    /* Test 1: CxOOP_EXTENDS_ — Circle inherits Shape members */
    Circle c = {0};
    CONSTRUCTOR_Circle(&c);
    c.name = "TestCircle";
    Shape *pc = DCAST(Shape, &c);
    if (pc->name != c.name) {
        printf("FAIL: EXTENDS_ — parent member not accessible via DCAST\n"); pass = 0;
    } else {
        printf("PASS: EXTENDS_ — parent member accessible via DCAST\n");
    }

    /* Test 2: CxOOP_EXTENDS2_ — Sphere inherits through 2 levels */
    Sphere sp = {0};
    CONSTRUCTOR_Sphere(&sp);
    sp.name = "TestSphere";
    Shape *psp = DCAST(Shape, &sp);
    if (psp->name != sp.name) {
        printf("FAIL: EXTENDS2_ — grandparent member not accessible via DCAST\n"); pass = 0;
    } else {
        printf("PASS: EXTENDS2_ — grandparent member accessible via DCAST\n");
    }

    /* Test 3: Polymorphic dispatch through both EXTENDS levels */
    c.radius = 1.0;
    sp.radius = 1.0;
    pc = DCAST(Shape, &c);
    psp = DCAST(Shape, &sp);

    double circle_area = pc->area(pc);
    double sphere_area = psp->area(psp);
    double pi = 3.14159265;

    if (circle_area < pi - 0.01 || circle_area > pi + 0.01) {
        printf("FAIL: EXTENDS_ polymorphism — got %.4f expected %.4f\n", circle_area, pi); pass = 0;
    } else {
        printf("PASS: EXTENDS_ polymorphism works (pi*r^2)\n");
    }

    double expected_4pi = 4.0 * pi;
    if (sphere_area < expected_4pi - 0.01 || sphere_area > expected_4pi + 0.01) {
        printf("FAIL: EXTENDS2_ polymorphism — got %.4f expected %.4f\n", sphere_area, expected_4pi); pass = 0;
    } else {
        printf("PASS: EXTENDS2_ polymorphism works (4*pi*r^2)\n");
    }

    /* Test 4: Virtual Destroy through both levels */
    psp->Destroy(psp);
    pc->Destroy(pc);
    printf("PASS: virtual Destroy through EXTENDS_/EXTENDS2_ chain\n");

    if (!pass) { printf("\nSOME TESTS FAILED\n"); return EXIT_FAILURE; }
    printf("\nALL TESTS PASSED\n");
    return EXIT_SUCCESS;
}
