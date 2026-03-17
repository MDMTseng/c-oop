#include "PARENT_OBJ.h"
#include "CHILD_OBJ.h"
#include <stdio.h>

CxOOP_DECLARE_METHOD(CHILD_OBJ)

int CONSTRUCTOR_CHILD_OBJ(CHILD_OBJ* obj)
{
    CONSTRUCTOR_PARENT_OBJ(DCAST(PARENT_OBJ,obj));
    CxOOP_INIT_METHOD(CHILD_OBJ,obj);
    obj->child_ID=5;
    return 0;
}

int DESTRUCTOR_CHILD_OBJ(CHILD_OBJ* obj)
{
    return 0;
}

static int DoAction( CHILD_OBJ* obj)
{
    __OMNI__CHILD_OBJ *oobj=CxOOP_OMNI(CHILD_OBJ,obj);

    int superResult=oobj->SUPER_DoAction((void*)oobj);
    int ret=superResult*2;

    printf("%s call ^ SUPER_GetPublic:%d *  2 = %d \n",__func__,superResult,ret);

    return ret;
}
