#include "DECEN_OBJ.h"
#include <stdio.h>

CxOOP_DECLARE_METHOD(DECEN_OBJ)
int CONSTRUCTOR_DECEN_OBJ(DECEN_OBJ* obj)
{
    CONSTRUCTOR_CHILD_OBJ(DCAST(CHILD_OBJ,obj));
    CxOOP_INIT_METHOD(DECEN_OBJ,obj);
    return 0;
}

int DESTRUCTOR_DECEN_OBJ(DECEN_OBJ* obj)
{
    DESTRUCTOR_CHILD_OBJ(DCAST(CHILD_OBJ,obj));
    return 0;
}

static int DoAction( DECEN_OBJ* obj)
{
    __OMNI__DECEN_OBJ *oobj=CxOOP_OMNI(DECEN_OBJ,obj);

    int superResult=oobj->SUPER_DoAction((void*)oobj);
    int ret=superResult+20;

    printf("%s call ^ SUPER_GetPublic:%d + 20 = %d \n",__func__,superResult,ret);
    return ret;
}
