#include "Circle.h"
#include <stdio.h>

CxOOP_DECLARE_METHOD(Circle)

int CONSTRUCTOR_Circle(Circle* obj)
{
    CONSTRUCTOR_Shape(DCAST(Shape, obj));
    CxOOP_INIT_METHOD(Circle, obj);
    obj->radius = 0.0;
    obj->name = "Circle";
    return 0;
}

int DESTRUCTOR_Circle(Circle* obj)
{
    DESTRUCTOR_Shape(DCAST(Shape, obj));
    return 0;
}

static double area(Circle* self)
{
    return 3.14159265 * self->radius * self->radius;
}
