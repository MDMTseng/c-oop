
#ifndef PARENT_OBJ_H_
#define PARENT_OBJ_H_

#include "CxOOP.h"

#define PARENT_OBJ_PUBLIC_MEMBER_\
        int pub;\


#define PARENT_OBJ_PRIVATE_MEMBER_\
        int __priv;


#define PARENT_OBJ_PUBLIC_METHOD_(PREFIX,MACRO_X)\
        MACRO_X(PREFIX,int,GetPublic, PARENT_OBJ* a)\
        MACRO_X(PREFIX,int,GetPrivate, PARENT_OBJ* a)

#define PARENT_OBJ_PRIVATE_METHOD_(PREFIX,MACRO_X)\
        MACRO_X(PREFIX,int,__GetPrivate, PARENT_OBJ* a)


#define PARENT_OBJ_OVERRIDE_METHOD_(PREFIX,MACRO_X)\

#define PARENT_OBJ_DNA_(X1,X2)  \
		NULL_OBJ_DNA_(X1,X1)\
        X2(PARENT_OBJ)

CxOOP_OBJECT_DECLARE(PARENT_OBJ)


#endif
