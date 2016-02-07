
#ifndef CHILD_OBJ_H_
#define CHILD_OBJ_H_

#include "OBJECT_MACRO.h"
#include "PARENT_OBJ.h"

#define CHILD_OBJ_PUBLIC_MEMBER_\
		int child_ID;\
		int array[100];

#define CHILD_OBJ_PRIVATE_MEMBER_\


#define CHILD_OBJ_PUBLIC_METHOD_(PREFIX,MACRO_X)\

#define CHILD_OBJ_PRIVATE_METHOD_(PREFIX,MACRO_X)\

#define CHILD_OBJ_OVERRIDE_METHOD_(PREFIX,MACRO_X)\
        MACRO_X(PREFIX,int,GetPublic, CHILD_OBJ* a)\



OBJECT_INHERIT_DECLARE(CHILD_OBJ,PARENT_OBJ)

//#define CHILD_OBJ_INH_      OBJECT_INHERIT_STRUCT_PRIDELCARE_(CHILD_OBJ,PARENT_OBJ)


#define CHILD_OBJ_INH_  \
        PARENT_OBJ_INH_\
        OBJECT_INHERIT_STRUCT_PRIDELCAREX_(CHILD_OBJ)


#endif
