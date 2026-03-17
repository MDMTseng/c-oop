#ifndef CIRCLE_H_
#define CIRCLE_H_

#include "CxOOP.h"
#include "Shape.h"

#define Circle_DNA_(X,COBJ)                 CxOOP_EXTENDS_(Shape,X,COBJ)

#define Circle_PUBLIC_MEMBER_               double radius;
#define Circle_PRIVATE_MEMBER_

#define Circle_PUBLIC_METHOD_(COBJ,MACRO_X)
#define Circle_PRIVATE_METHOD_(COBJ,MACRO_X)
#define Circle_OVERRIDE_METHOD_(COBJ,MACRO_X) \
        MACRO_X(COBJ, double, area, COBJ* self)

CxOOP_OBJECT_DECLARE(Circle)
int CONSTRUCTOR_Circle(Circle* obj);

#endif
