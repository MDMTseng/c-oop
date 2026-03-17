#include <stdio.h>
#include <stdlib.h>
#include "Shape.h"
#include "Circle.h"
#include "Sphere.h"

int main(void)
{
    int i;

    /* ---- 1. Stack allocation ---- */
    printf("==== Stack Allocation & Constructors ====\n");

    Shape  s = {0};
    CONSTRUCTOR_Shape(&s);

    Circle c = {0};
    CONSTRUCTOR_Circle(&c);

    Sphere sp = {0};
    CONSTRUCTOR_Sphere(&sp);

    /* ---- 2. Set radius values ---- */
    c.radius  = 5.0;
    sp.radius = 3.0;

    printf("Shape  name=%s\n", s.name);
    printf("Circle name=%s  radius=%.1f\n", c.name, c.radius);
    printf("Sphere name=%s  radius=%.1f\n", sp.name, sp.radius);

    /* ---- 3. Polymorphic array ---- */
    printf("\n==== Polymorphism (area + describe) ====\n");

    Shape *arr[] = {
        &s,
        DCAST(Shape, &c),
        DCAST(Shape, &sp)
    };

    for (i = 0; i < (int)(sizeof(arr) / sizeof(arr[0])); i++)
    {
        printf("  area = %.4f  ->  ", arr[i]->area(arr[i]));
        arr[i]->describe(arr[i]);
    }

    /* ---- 4. Safe downcast (DCAST) ---- */
    printf("\n==== Safe Downcast (DCAST) ====\n");

    /* Sphere -> Circle: valid (Sphere inherits from Circle) */
    Circle *cc = DCAST(Circle, &sp);
    if (cc)
        printf("Sphere -> Circle downcast OK, radius=%.1f\n", cc->radius);

    /* Sphere -> Shape: valid (Sphere inherits from Shape via Circle) */
    Shape *ss = DCAST(Shape, &sp);
    if (ss)
        printf("Sphere -> Shape  downcast OK, name=%s\n", ss->name);

    /* Note: DCAST(Circle, &s) won't compile — Shape has no Circle lineage.
       This is a compile-time safety check, not a runtime one. */
    printf("Shape  -> Circle downcast blocked at compile time (safe)\n");

    /* ---- 5. sizeof comparison ---- */
    printf("\n==== Object Sizes ====\n");
    printf("sizeof(Shape)  = %d\n", (int)sizeof(Shape));
    printf("sizeof(Circle) = %d\n", (int)sizeof(Circle));
    printf("sizeof(Sphere) = %d\n", (int)sizeof(Sphere));

    /* ---- 6. Virtual destructor ---- */
    printf("\n==== Virtual Destructor (stack) ====\n");
    for (i = 0; i < (int)(sizeof(arr) / sizeof(arr[0])); i++)
    {
        arr[i]->Destroy(arr[i]);
    }
    printf("All destructors called through Shape*.\n");

    /* ---- 7. Heap allocation ---- */
    printf("\n==== Heap: CxOOP_ALLOC / CxOOP_DELETE ====\n");

    Sphere *hs = CxOOP_ALLOC(Sphere);
    CONSTRUCTOR_Sphere(hs);
    hs->radius = 10.0;

    Shape *hp = DCAST(Shape, hs);
    printf("Heap sphere area via Shape*: %.4f\n", hp->area(hp));
    hp->describe(hp);

    CxOOP_DELETE(hp);
    printf("Heap object deleted via Shape*.\n");

    return EXIT_SUCCESS;
}
