#include "Sphere.h"
#include <stdio.h>

CxOOP_DECLARE_METHOD(Sphere)

int CONSTRUCTOR_Sphere(Sphere* obj)
{
    CONSTRUCTOR_Circle(DCAST(Circle, obj));
    CxOOP_INIT_METHOD(Sphere, obj);
    obj->name = "Sphere";
    return 0;
}

int DESTRUCTOR_Sphere(Sphere* obj)
{
    DESTRUCTOR_Circle(DCAST(Circle, obj));
    return 0;
}

static double area(Sphere* self)
{
    __OMNI__Sphere *oself = CxOOP_OMNI(Sphere, self);
    double circle_area = oself->SUPER_area((void*)oself);
    return 4.0 * circle_area;
}

static int describe(Sphere* self)
{
    printf("[Sphere] name=%s surface_area=%.2f\n", self->name, self->area(self));
    return 0;
}
