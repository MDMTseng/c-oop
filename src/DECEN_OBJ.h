
#ifndef DECEN_OBJ_H_
#define DECEN_OBJ_H_

#include "CxOOP.h"
#include "CHILD_OBJ.h"

#define DECEN_OBJ_PUBLIC_MEMBER_\
        int decendent_data;

#define DECEN_OBJ_PRIVATE_MEMBER_\

#define DECEN_OBJ_PUBLIC_METHOD_(PREFIX,MACRO_X)\

#define DECEN_OBJ_PRIVATE_METHOD_(PREFIX,MACRO_X)\

#define DECEN_OBJ_OVERRIDE_METHOD_(PREFIX,MACRO_X)\
        MACRO_X(PREFIX,int,DoAction, DECEN_OBJ* a)\

#define DECEN_OBJ_DNA_(X1,X2)  \
        CHILD_OBJ_DNA_(X1,X1)\
        X2(DECEN_OBJ)

CxOOP_OBJECT_DECLARE(DECEN_OBJ)

#endif

