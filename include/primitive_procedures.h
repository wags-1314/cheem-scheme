#ifndef CHEEM_PRIMITIVE_PROCEDURES_H
#define CHEEM_PRIMITIVE_PROCEDURES_H

#include "object.h"

Object* add_pproc(Object* arguments);
Object* sub_pproc(Object* arguments);
Object* eq_int_pproc(Object* arguments);
Object* mult_pproc(Object* arguments);
Object* quit_pproc(Object* arguments);
Object* eq_pproc(Object* arguments);

#endif