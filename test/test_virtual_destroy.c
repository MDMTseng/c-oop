#include <stdio.h>
#include <stdlib.h>
#include "Shape.h"
#include "Circle.h"
#include "Sphere.h"

int main(void) {
    int pass = 1;

    /* Test 1: Destroy pointer is set after construction */
    Shape s = {0}; CONSTRUCTOR_Shape(&s);
    Circle c = {0}; CONSTRUCTOR_Circle(&c);
    Sphere sp = {0}; CONSTRUCTOR_Sphere(&sp);

    if (!s.Destroy) { printf("FAIL: Shape Destroy is NULL\n"); pass = 0; }
    else printf("PASS: Shape Destroy is set\n");

    if (!c.Destroy) { printf("FAIL: Circle Destroy is NULL\n"); pass = 0; }
    else printf("PASS: Circle Destroy is set\n");

    if (!sp.Destroy) { printf("FAIL: Sphere Destroy is NULL\n"); pass = 0; }
    else printf("PASS: Sphere Destroy is set\n");

    /* Test 2: Virtual dispatch — child Destroy differs from parent */
    Shape *as_shape = DCAST(Shape, &c);
    if (as_shape->Destroy == s.Destroy) {
        printf("FAIL: Circle via base has same Destroy as Shape\n"); pass = 0;
    } else {
        printf("PASS: Circle via base has overridden Destroy\n");
    }

    Shape *as_shape2 = DCAST(Shape, &sp);
    if (as_shape2->Destroy == s.Destroy || as_shape2->Destroy == as_shape->Destroy) {
        printf("FAIL: Sphere via base Destroy not unique\n"); pass = 0;
    } else {
        printf("PASS: Sphere via base has its own Destroy\n");
    }

    /* Test 3: Virtual destroy on heap objects through base pointer */
    Circle *hc = CxOOP_ALLOC(Circle);
    CONSTRUCTOR_Circle(hc);
    Shape *base = DCAST(Shape, hc);
    base->Destroy(base);
    printf("PASS: virtual Destroy through base pointer (Circle)\n");
    free(hc);

    Sphere *hsp = CxOOP_ALLOC(Sphere);
    CONSTRUCTOR_Sphere(hsp);
    Shape *base2 = DCAST(Shape, hsp);
    base2->Destroy(base2);
    printf("PASS: virtual Destroy through base pointer (Sphere)\n");
    free(hsp);

    /* Test 4: Polymorphic array destroy */
    Shape *hp = CxOOP_ALLOC(Shape); CONSTRUCTOR_Shape(hp);
    Circle *hc2 = CxOOP_ALLOC(Circle); CONSTRUCTOR_Circle(hc2);
    Sphere *hsp2 = CxOOP_ALLOC(Sphere); CONSTRUCTOR_Sphere(hsp2);

    Shape *arr[] = {hp, DCAST(Shape, hc2), DCAST(Shape, hsp2)};
    int i;
    for (i = 0; i < 3; i++) arr[i]->Destroy(arr[i]);
    printf("PASS: polymorphic array virtual Destroy\n");
    free(hp); free(hc2); free(hsp2);

    /* Clean up stack objects */
    sp.Destroy(&sp); c.Destroy(&c); s.Destroy(&s);

    if (!pass) { printf("\nSOME TESTS FAILED\n"); return EXIT_FAILURE; }
    printf("\nALL TESTS PASSED\n");
    return EXIT_SUCCESS;
}
