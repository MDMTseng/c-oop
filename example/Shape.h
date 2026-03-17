#ifndef SHAPE_H_
#define SHAPE_H_

#include "CxOOP.h"

#define Shape_DNA_(X,COBJ)                  /* root class — no parent */

#define Shape_PUBLIC_MEMBER_                const char* name;
#define Shape_PRIVATE_MEMBER_               int _id;

#define Shape_PUBLIC_METHOD_(COBJ,MACRO_X) \
        MACRO_X(COBJ, double, area, COBJ* self) \
        MACRO_X(COBJ, int, describe, COBJ* self)

#define Shape_PRIVATE_METHOD_(COBJ,MACRO_X) \
        MACRO_X(COBJ, int, getID, COBJ* self)

#define Shape_OVERRIDE_METHOD_(COBJ,MACRO_X)

CxOOP_OBJECT_DECLARE(Shape)
int CONSTRUCTOR_Shape(Shape* obj);

#endif
