#ifndef CHEEM_PRINT_H
#define CHEEM_PRINT_H

#include <string>
#include <sstream>
#include "object.h"

//std::string print_object(Object* object);
std::string print_object(Object* object, Stack traceback);
std::string print_pair(Object* object, Stack traceback);

#endif