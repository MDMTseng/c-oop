# CxOOP - Lightweight OOP for C

Single-header macro library (~85 lines) that brings classes, inheritance, polymorphism, and encapsulation to plain C with zero runtime overhead.

## Features

- **Encapsulation** - public and private members/methods per class
- **Single inheritance** - unlimited depth via `CxOOP_EXTENDS_` / `CxOOP_EXTENDS2_`
- **Polymorphism** - virtual method dispatch through function pointers
- **Method override with SUPER access** - call the parent implementation via `SUPER_methodName`
- **Safe downcast** - `DCAST(TargetClass, ptr)` returns `NULL` on type mismatch
- **Virtual destructor** - `Destroy()` always calls the most-derived destructor
- **Heap helpers** - `CxOOP_ALLOC` / `CxOOP_DELETE` for heap-allocated objects
- **Stack-friendly** - objects can live on the stack with zero-init + constructor

## Quick Start

```bash
make            # build example
./bin/example   # run

make test       # run all tests
```

Expected output:

```
==== Stack Allocation & Constructors ====
Shape  name=Shape
Circle name=Circle  radius=5.0
Sphere name=Sphere  radius=3.0

==== Polymorphism (area + describe) ====
  area = 0.0000  ->  [Shape] name=Shape area=0.00
  area = 78.5398  ->  [Shape] name=Circle area=78.54
  area = 113.0973  ->  [Sphere] name=Sphere surface_area=113.10

==== Safe Downcast (DCAST) ====
Sphere -> Circle downcast OK, radius=3.0
Sphere -> Shape  downcast OK, name=Sphere
Shape  -> Circle downcast blocked at compile time (safe)
...
```

## Defining a Class (Root)

Every class needs a header with seven macros and a `CxOOP_OBJECT_DECLARE` call.

**Shape.h**

```c
#ifndef SHAPE_H_
#define SHAPE_H_

#include "CxOOP.h"

/* Root class: DNA_ macro is empty */
#define Shape_DNA_(X,COBJ)

/* Public members — accessible from any pointer to Shape */
#define Shape_PUBLIC_MEMBER_            const char* name;

/* Private members — only accessible via __OMNI__Shape inside the .c file */
#define Shape_PRIVATE_MEMBER_           int _id;

/* Public methods — virtual, dispatched through function pointers */
#define Shape_PUBLIC_METHOD_(COBJ,MACRO_X) \
        MACRO_X(COBJ, double, area, COBJ* self) \
        MACRO_X(COBJ, int, describe, COBJ* self)

/* Private methods — stored in the hidden private space */
#define Shape_PRIVATE_METHOD_(COBJ,MACRO_X) \
        MACRO_X(COBJ, int, getID, COBJ* self)

/* Override methods — empty for root class */
#define Shape_OVERRIDE_METHOD_(COBJ,MACRO_X)

CxOOP_OBJECT_DECLARE(Shape)
int CONSTRUCTOR_Shape(Shape* obj);

#endif
```

**Shape.c**

```c
#include "Shape.h"
#include <stdio.h>

CxOOP_DECLARE_METHOD(Shape)

int CONSTRUCTOR_Shape(Shape* obj)
{
    CxOOP_INIT_METHOD(Shape, obj);
    obj->name = "Shape";
    return 0;
}

int DESTRUCTOR_Shape(Shape* obj)
{
    return 0;
}

static double area(Shape* self)
{
    return 0.0;
}

static int describe(Shape* self)
{
    printf("[Shape] name=%s area=%.2f\n", self->name, self->area(self));
    return 0;
}

static int getID(Shape* self)
{
    __OMNI__Shape *oself = CxOOP_OMNI(Shape, self);
    return oself->_id;
}
```

## Inheriting a Class

Use `CxOOP_EXTENDS_` in the DNA macro. List overridden methods in `OVERRIDE_METHOD_`.

**Circle.h**

```c
#ifndef CIRCLE_H_
#define CIRCLE_H_

#include "CxOOP.h"
#include "Shape.h"

/* Inherit from Shape using EXTENDS_ */
#define Circle_DNA_(X,COBJ)             CxOOP_EXTENDS_(Shape,X,COBJ)

#define Circle_PUBLIC_MEMBER_           double radius;
#define Circle_PRIVATE_MEMBER_

#define Circle_PUBLIC_METHOD_(COBJ,MACRO_X)
#define Circle_PRIVATE_METHOD_(COBJ,MACRO_X)

/* Override Shape's area() */
#define Circle_OVERRIDE_METHOD_(COBJ,MACRO_X) \
        MACRO_X(COBJ, double, area, COBJ* self)

CxOOP_OBJECT_DECLARE(Circle)
int CONSTRUCTOR_Circle(Circle* obj);

#endif
```

**Circle.c**

```c
#include "Circle.h"

CxOOP_DECLARE_METHOD(Circle)

int CONSTRUCTOR_Circle(Circle* obj)
{
    CONSTRUCTOR_Shape(DCAST(Shape, obj));   /* call parent constructor */
    CxOOP_INIT_METHOD(Circle, obj);         /* wire up Circle's methods */
    obj->radius = 0.0;
    obj->name = "Circle";
    return 0;
}

int DESTRUCTOR_Circle(Circle* obj)
{
    DESTRUCTOR_Shape(DCAST(Shape, obj));    /* chain to parent destructor */
    return 0;
}

static double area(Circle* self)
{
    return 3.14159265 * self->radius * self->radius;
}
```

## Multi-Level Inheritance and SUPER Access

For the third level, alternate to `CxOOP_EXTENDS2_`. Use `SUPER_methodName` to call the parent version.

**Sphere.h** (extends Circle)

```c
#define Sphere_DNA_(X,COBJ)             CxOOP_EXTENDS2_(Circle,X,COBJ)

#define Sphere_OVERRIDE_METHOD_(COBJ,MACRO_X) \
        MACRO_X(COBJ, double, area, COBJ* self) \
        MACRO_X(COBJ, int, describe, COBJ* self)
```

**Sphere.c**

```c
static double area(Sphere* self)
{
    __OMNI__Sphere *oself = CxOOP_OMNI(Sphere, self);
    double circle_area = oself->SUPER_area((void*)oself);
    return 4.0 * circle_area;   /* surface area = 4 * pi * r^2 */
}
```

## Using Objects

### Stack allocation

```c
Circle c = {0};
CONSTRUCTOR_Circle(&c);
c.radius = 5.0;
printf("area = %.2f\n", c.area(&c));
```

### Heap allocation

```c
Circle *c = CxOOP_ALLOC(Circle);
CONSTRUCTOR_Circle(c);
c->radius = 5.0;
printf("area = %.2f\n", c->area(c));
CxOOP_DELETE(c);
```

### Polymorphism

```c
Shape *arr[] = { &s, DCAST(Shape, &c), DCAST(Shape, &sp) };
for (int i = 0; i < 3; i++)
    arr[i]->describe(arr[i]);   /* dispatches to correct override */
```

### Safe downcast

```c
Circle *cc = DCAST(Circle, sphere_ptr);  /* returns Circle* or NULL */
```

### Virtual destructor

```c
Shape *p = DCAST(Shape, &sphere);
p->Destroy(p);   /* calls Sphere -> Circle -> Shape destructors */
```

## API Reference

| Macro | Purpose |
|-------|---------|
| `CxOOP_OBJECT_DECLARE(CLASS)` | Generate struct types and destructor prototype |
| `CxOOP_DECLARE_METHOD(CLASS)` | Forward-declare all static method implementations |
| `CxOOP_INIT_METHOD(CLASS, ptr)` | Wire function pointers in constructor |
| `CxOOP_EXTENDS_(PARENT, X, COBJ)` | Inherit from parent (odd levels: 1st, 3rd, ...) |
| `CxOOP_EXTENDS2_(PARENT, X, COBJ)` | Inherit from parent (even levels: 2nd, 4th, ...) |
| `CxOOP_ALLOC(CLASS)` | Heap-allocate a zero-initialized object |
| `CxOOP_DELETE(ptr)` | Destroy + free a heap object |
| `DCAST(ToClass, ptr)` | Safe downcast (returns `NULL` on mismatch) |
| `CxOOP_OMNI(CLASS, ptr)` | Cast to `__OMNI__` view (access private + SUPER) |

## The EXTENDS_ / EXTENDS2_ Alternation Rule

Due to macro expansion mechanics, each inheritance level must alternate between `CxOOP_EXTENDS_` and `CxOOP_EXTENDS2_`:

| Depth | Class | DNA macro |
|-------|-------|-----------|
| 0 | Shape (root) | empty |
| 1 | Circle | `CxOOP_EXTENDS_(Shape, ...)` |
| 2 | Sphere | `CxOOP_EXTENDS2_(Circle, ...)` |
| 3 | NextLevel | `CxOOP_EXTENDS_(Sphere, ...)` |
| 4 | ... | `CxOOP_EXTENDS2_(...)` |

The pattern is: odd depths use `EXTENDS_`, even depths use `EXTENDS2_`.

## License

MIT License. See [LICENSE](LICENSE) for details.
