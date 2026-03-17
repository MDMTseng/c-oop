#include "Shape.h"
#include <stdio.h>

CxOOP_DECLARE_METHOD(Shape)

static int _shape_next_id = 1;

int CONSTRUCTOR_Shape(Shape* obj)
{
    CxOOP_INIT_METHOD(Shape, obj);
    obj->name = "Shape";

    __OMNI__Shape *oobj = CxOOP_OMNI(Shape, obj);
    oobj->_id = _shape_next_id++;

    return 0;
}

int DESTRUCTOR_Shape(Shape* obj)
{
    return 0;
}

static double area(Shape* self)
{
    return 0.0;
}

static int describe(Shape* self)
{
    printf("[Shape] name=%s area=%.2f\n", self->name, self->area(self));
    return 0;
}

static int getID(Shape* self)
{
    __OMNI__Shape *oself = CxOOP_OMNI(Shape, self);
    return oself->_id;
}
