/*
 ============================================================================
 Name        : OBJ_TEST.c
 Author      : MDM
 Version     :
 Copyright   : copy to death
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include "PARENT_OBJ.h"
#include "CHILD_OBJ.h"
#include "DECEN_OBJ.h"


int main(void) {

    int i;
    PARENT_OBJ p={0};
    CONSTRUCTOR_PARENT_OBJ(&p);

    CHILD_OBJ c={0};

    CONSTRUCTOR_CHILD_OBJ(&c);

    DECEN_OBJ d={0};
    CONSTRUCTOR_DECEN_OBJ(&d);

    printf("\n===============Safe DownCast & polymorphism==============\n");
    p.pub=
    c.pub=
    d.pub=100;
    PARENT_OBJ *obj_arr[]={&p,CxOOP_DCAST(PARENT_OBJ,&c) ,DCAST(PARENT_OBJ,&d)};

    for(i=0;i<sizeof(obj_arr)/sizeof(obj_arr[0]);i++)
    {
        printf("DoAction!!!::%d\n",obj_arr[i]->DoAction(obj_arr[i]));
    }

    printf("\n===============Object size==============\n");
    printf("!!!Hello sizeof!!!::%d..%d..%d\n",(int)sizeof(PARENT_OBJ),(int)sizeof(CHILD_OBJ),(int)sizeof(DECEN_OBJ));

    printf("\n===============Virtual Destroy==============\n");
    for(i=0;i<sizeof(obj_arr)/sizeof(obj_arr[0]);i++)
    {
        obj_arr[i]->Destroy(obj_arr[i]);
    }

    return EXIT_SUCCESS;
}
