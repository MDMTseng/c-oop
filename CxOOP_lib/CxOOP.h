#ifndef C_X_OOP_H_
#define C_X_OOP_H_

#define CxOOP__METHOD__DECLARE(PREFIX,RET,FUNCNAME,...)\
        static RET FUNCNAME ( __VA_ARGS__ );
#define CxOOP__METHOD__SPAN(PREFIX,RET,FUNCNAME,...)\
        const RET (* FUNCNAME )( __VA_ARGS__ );
#define CxOOP__METHOD__OVERRIDE_SPAN(PREFIX,RET,FUNCNAME,...)\
        const RET (* SUPER_##FUNCNAME )( __VA_ARGS__ );

#define CxOOP_STRUCT_PUB_(CLASSNAME,COBJ)\
        CLASSNAME##_PUBLIC_MEMBER_\
        CLASSNAME##_PUBLIC_METHOD_(COBJ,CxOOP__METHOD__SPAN)\

#define CxOOP_STRUCT_PRIV_(CLASSNAME,COBJ)\
        CLASSNAME##_PRIVATE_MEMBER_\
        CLASSNAME##_PRIVATE_METHOD_(COBJ,CxOOP__METHOD__SPAN)\
        CLASSNAME##_OVERRIDE_METHOD_(COBJ,CxOOP__METHOD__OVERRIDE_SPAN)\

#define CxOOP_STRUCT_OBJ_(CLASSNAME,COBJ)\
        CxOOP_STRUCT_PUB_(CLASSNAME,COBJ)\
        const char ___##CLASSNAME##_priv_space[sizeof(struct _PRIVATE_SPACE_##CLASSNAME)];\

#define CxOOP_STRUCT___OMNI__OBJ_(CLASSNAME,COBJ)\
        CxOOP_STRUCT_PUB_(CLASSNAME,COBJ)\
        CxOOP_STRUCT_PRIV_(CLASSNAME,COBJ)

#define CxOOP_OBJECT_DECLARE(CLASSNAME) \
        typedef struct _##CLASSNAME CLASSNAME;\
        typedef struct ___OMNI__##CLASSNAME __OMNI__##CLASSNAME;\
        struct  _PRIVATE_SPACE_##CLASSNAME\
        {\
            CxOOP_STRUCT_PRIV_(CLASSNAME,CLASSNAME)\
        };\
        struct ___OMNI__##CLASSNAME/* A struct to access all members, use it carefully */\
        {\
            CLASSNAME##_DNA_(CxOOP_STRUCT_OBJ_,CLASSNAME)\
            CxOOP_STRUCT___OMNI__OBJ_(CLASSNAME,CLASSNAME)\
        };\
        struct _##CLASSNAME/* A struct to provide encapsulation */\
        {\
            CLASSNAME##_DNA_(CxOOP_STRUCT_OBJ_,CLASSNAME)\
            CxOOP_STRUCT_OBJ_(CLASSNAME,CLASSNAME)\
        };\
        int CONSTRUCTOR_##CLASSNAME( CLASSNAME * obj);\
        int DESTRUCTOR_##CLASSNAME( CLASSNAME * obj);

#define CxOOP_DECLARE_METHOD(CLASSNAME) \
        CLASSNAME##_PUBLIC_METHOD_(CLASSNAME,CxOOP__METHOD__DECLARE)\
        CLASSNAME##_PRIVATE_METHOD_(CLASSNAME,CxOOP__METHOD__DECLARE)\
        CLASSNAME##_OVERRIDE_METHOD_(CLASSNAME,CxOOP__METHOD__DECLARE)\

#define CxOOP__METHOD__SETTING(PREFIX,RET,FUNCNAME,...)\
        *(void**)&(omni_obj_____->FUNCNAME)=(void*)FUNCNAME;\

#define CxOOP__METHOD__OVERRIDE_SETTING(PREFIX,RET,FUNCNAME,...)\
        *(void**)&(omni_obj_____->SUPER_##FUNCNAME)=(void*)omni_obj_____->FUNCNAME;\
        *(void**)&(omni_obj_____->FUNCNAME)=(void*)FUNCNAME;\

#define CxOOP_INIT_METHOD(CLASSNAME,obj_ptr)\
        __OMNI__##CLASSNAME *omni_obj_____=(void*)obj_ptr;\
        CLASSNAME##_PUBLIC_METHOD_(CLASSNAME,CxOOP__METHOD__SETTING)\
        CLASSNAME##_PRIVATE_METHOD_(CLASSNAME,CxOOP__METHOD__SETTING)\
        CLASSNAME##_OVERRIDE_METHOD_(CLASSNAME,CxOOP__METHOD__OVERRIDE_SETTING)\

#define CxOOP_DCAST(toCLASS,obj_PTR)  ((obj_PTR) ? ((toCLASS*)((void*)((obj_PTR)+(  0*(unsigned long)((obj_PTR)->___##toCLASS##_priv_space)  )))) : (toCLASS*)0)
#define DCAST(toCLASS,obj_PTR)  CxOOP_DCAST(toCLASS,obj_PTR)

#define CxOOP_OMNI(CLASSNAME,obj_ptr) ((__OMNI__##CLASSNAME*)((CLASSNAME*)(obj_ptr)))

#endif  //C_X_OOP_H_
