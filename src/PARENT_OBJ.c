
#include "PARENT_OBJ.h"
#include <stdio.h>

CxOOP_DECLARE_METHOD(PARENT_OBJ)

int CONSTRUCTOR_PARENT_OBJ(PARENT_OBJ* obj)
{
    CxOOP_INIT_METHOD(PARENT_OBJ,obj);
    __OMNI__PARENT_OBJ *oobj=(void*)obj;
    return 0;
}

int DESTRUCTOR_PARENT_OBJ(PARENT_OBJ* obj)
{
    return 0;
}
static int PARENT_OBJ_DoAction( PARENT_OBJ* a)
{
    printf("%s get pub:%d \n",__func__,a->pub);
    return a->pub;
}
