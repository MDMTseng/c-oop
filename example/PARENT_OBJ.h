#ifndef PARENT_OBJ_H_
#define PARENT_OBJ_H_

#include "CxOOP.h"

#define PARENT_OBJ_DNA_(X,COBJ)             /* root class — no parent */

#define PARENT_OBJ_PUBLIC_MEMBER_           int pub;
#define PARENT_OBJ_PRIVATE_MEMBER_          int __priv;

#define PARENT_OBJ_PUBLIC_METHOD_(COBJ,MACRO_X) \
        MACRO_X(COBJ,int,DoAction, COBJ* self)

#define PARENT_OBJ_PRIVATE_METHOD_(COBJ,MACRO_X)
#define PARENT_OBJ_OVERRIDE_METHOD_(COBJ,MACRO_X)

CxOOP_OBJECT_DECLARE(PARENT_OBJ)

#endif
