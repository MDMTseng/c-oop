#include <stdio.h>
#include <stdlib.h>
#include "Shape.h"
#include "Circle.h"
#include "Sphere.h"

/*
 * Test: insert Ellipse between Shape and Circle using EXTENDS3_
 * This proves that adding a 3rd variant allows middle-class insertion
 * without re-numbering existing classes.
 *
 * Hierarchy: Shape -> Ellipse(EXTENDS3_) -> Circle(EXTENDS_) -> Sphere(EXTENDS2_)
 *
 * Note: Circle still uses EXTENDS_(Shape,...) so we make Ellipse
 * extend Shape with EXTENDS3_, and stand alone (not in the Circle chain).
 * This tests that EXTENDS3_ works identically to the other two.
 */

/* --- Ellipse: extends Shape via EXTENDS3_ --- */

#define Ellipse_DNA_(X,COBJ)              CxOOP_EXTENDS3_(Shape,X,COBJ)

#define Ellipse_PUBLIC_MEMBER_            double semi_a; double semi_b;
#define Ellipse_PRIVATE_MEMBER_

#define Ellipse_PUBLIC_METHOD_(COBJ,MACRO_X)
#define Ellipse_PRIVATE_METHOD_(COBJ,MACRO_X)
#define Ellipse_OVERRIDE_METHOD_(COBJ,MACRO_X) \
        MACRO_X(COBJ, double, area, COBJ* self)

CxOOP_OBJECT_DECLARE(Ellipse)

static double area(Ellipse* self)
{
    return 3.14159265 * self->semi_a * self->semi_b;
}

CxOOP_DECLARE_METHOD(Ellipse)

int CONSTRUCTOR_Ellipse(Ellipse* obj)
{
    CONSTRUCTOR_Shape(DCAST(Shape, obj));
    CxOOP_INIT_METHOD(Ellipse, obj);
    obj->name = "Ellipse";
    obj->semi_a = 0.0;
    obj->semi_b = 0.0;
    return 0;
}

int DESTRUCTOR_Ellipse(Ellipse* obj)
{
    DESTRUCTOR_Shape(DCAST(Shape, obj));
    return 0;
}

int main(void)
{
    int pass = 1;

    /* Test 1: Ellipse constructed via EXTENDS3_ works */
    Ellipse e = {0};
    CONSTRUCTOR_Ellipse(&e);
    e.semi_a = 5.0;
    e.semi_b = 3.0;
    double result = e.area(&e);
    double expected = 3.14159265 * 5.0 * 3.0;
    if (result < expected - 0.01 || result > expected + 0.01) {
        printf("FAIL: Ellipse area got %.4f, expected %.4f\n", result, expected);
        pass = 0;
    } else {
        printf("PASS: Ellipse (EXTENDS3_) area works\n");
    }

    /* Test 2: DCAST Ellipse -> Shape works */
    Shape *as_shape = DCAST(Shape, &e);
    if (!as_shape) {
        printf("FAIL: DCAST(Shape, &ellipse) returned NULL\n");
        pass = 0;
    } else {
        printf("PASS: DCAST Ellipse -> Shape works\n");
    }

    /* Test 3: Polymorphic dispatch through Shape* */
    double poly_result = as_shape->area(as_shape);
    if (poly_result < expected - 0.01 || poly_result > expected + 0.01) {
        printf("FAIL: polymorphic area got %.4f\n", poly_result);
        pass = 0;
    } else {
        printf("PASS: Ellipse polymorphic area through Shape*\n");
    }

    /* Test 4: Virtual Destroy works */
    as_shape->Destroy(as_shape);
    printf("PASS: Ellipse virtual Destroy via Shape*\n");

    /* Test 5: Existing classes still work unchanged */
    Circle c = {0};
    CONSTRUCTOR_Circle(&c);
    c.radius = 1.0;

    Sphere sp = {0};
    CONSTRUCTOR_Sphere(&sp);
    sp.radius = 1.0;

    Shape *sc = DCAST(Shape, &c);
    Shape *ssp = DCAST(Shape, &sp);

    double c_area = sc->area(sc);
    double sp_area = ssp->area(ssp);
    double pi = 3.14159265;

    if (c_area < pi - 0.01 || c_area > pi + 0.01) {
        printf("FAIL: Circle still broken after EXTENDS3_ addition\n");
        pass = 0;
    } else {
        printf("PASS: Circle unchanged after EXTENDS3_ addition\n");
    }

    if (sp_area < 4*pi - 0.01 || sp_area > 4*pi + 0.01) {
        printf("FAIL: Sphere still broken after EXTENDS3_ addition\n");
        pass = 0;
    } else {
        printf("PASS: Sphere unchanged after EXTENDS3_ addition\n");
    }

    /* Test 6: Heap alloc/delete with EXTENDS3_ class */
    Ellipse *he = CxOOP_ALLOC(Ellipse);
    CONSTRUCTOR_Ellipse(he);
    he->semi_a = 2.0;
    he->semi_b = 2.0;
    Shape *hp = DCAST(Shape, he);
    double heap_area = hp->area(hp);
    double heap_expected = 3.14159265 * 4.0;
    if (heap_area < heap_expected - 0.01 || heap_area > heap_expected + 0.01) {
        printf("FAIL: heap Ellipse area got %.4f\n", heap_area);
        pass = 0;
    } else {
        printf("PASS: heap Ellipse via CxOOP_ALLOC works\n");
    }
    CxOOP_DELETE(hp);
    printf("PASS: CxOOP_DELETE heap Ellipse\n");

    ssp->Destroy(ssp);
    sc->Destroy(sc);

    if (!pass) {
        printf("\nSOME TESTS FAILED\n");
        return EXIT_FAILURE;
    }
    printf("\nALL TESTS PASSED\n");
    return EXIT_SUCCESS;
}
