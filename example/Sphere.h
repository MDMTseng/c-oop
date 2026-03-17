#ifndef SPHERE_H_
#define SPHERE_H_

#include "CxOOP.h"
#include "Circle.h"

#define Sphere_DNA_(X,COBJ)                 CxOOP_EXTENDS2_(Circle,X,COBJ)

#define Sphere_PUBLIC_MEMBER_
#define Sphere_PRIVATE_MEMBER_

#define Sphere_PUBLIC_METHOD_(COBJ,MACRO_X)
#define Sphere_PRIVATE_METHOD_(COBJ,MACRO_X)
#define Sphere_OVERRIDE_METHOD_(COBJ,MACRO_X) \
        MACRO_X(COBJ, double, area, COBJ* self) \
        MACRO_X(COBJ, int, describe, COBJ* self)

CxOOP_OBJECT_DECLARE(Sphere)
int CONSTRUCTOR_Sphere(Sphere* obj);

#endif
