#include "object.h"
#include <iostream>

/*void print_object_type(ObjectType type, std::ostream& os) {
	switch(type) {
		case ObjectType::O_INTEGER:
			os << "int" << std::endl;
			break;
		case ObjectType::O_BOOL:
			os << "bool" << std::endl;
			break;
		case ObjectType::O_CHARACTER:
			os << "char" << std::endl;
			break;
		case ObjectType::O_ERROR:
			os << "err" << std::endl;
			break;
		case ObjectType::O_STRING:
			os << "str" << std::endl;
			break;
		case ObjectType::O_NULL:
			os << "null" << std::endl;
			break;
		case ObjectType::O_DEFAULT:
			os << "def" << std::endl;
			break;
		case ObjectType::O_PAIR:
			os << "pair" << std::endl;
			break;
		case ObjectType::O_SYMBOL:
			os << "sym" << std::endl;
			break;
	}
}*/

Object* make_object_integer(long integer) {
	Object* object = new Object();
	object->type = ObjectType::O_INTEGER;
	object->integer = integer;
	return object;
}

Object* make_object_bool(bool boolean) {
	Object* object = new Object();
	object->type = ObjectType::O_BOOL;
	object->boolean = boolean;
	return object;
}

Object* make_object_character(char character) {
	Object* object = new Object();
	object->type = ObjectType::O_CHARACTER;
	object->character = character;
	return object;
}

Object* make_object_string(std::string string) {
	Object* object = new Object();
	object->type = ObjectType::O_STRING;
	object->string = string;
	return object;
} 

Object* cons(Object* car, Object* cdr) {
	Object* object = new Object();
	object->type = ObjectType::O_PAIR;
	object->car = car;
	object->cdr = cdr;
	return object;
}

Object* make_object_symbol(std::string symbol) {
	Object* object = new Object();
	object->type = ObjectType::O_SYMBOL;
	object->string = symbol;
	return object;
}

Object* make_object_error(std::string error_message) {
	Object* object = new Object();
	object->type = ObjectType::O_ERROR;
	object->string = error_message;
	return object;
}

Object* make_object_primitive_procedure(Object* (*func)(Object* arguments)) {
	Object* object = new Object();
	object->type = ObjectType::O_PPROC;
	object->func = func;
	return object;
}

Object* make_object_procedure(Object* params, Object* body) {
	Object* object = new Object();
	object->type = ObjectType::O_PROC;
	object->car = params;
	object->cdr = body;
	return object;
}

bool is_integer(Object *obj) {
	return obj->type == ObjectType::O_INTEGER;
}

bool is_boolean(Object *obj) {
	return obj->type == ObjectType::O_BOOL;
}

bool is_character(Object *obj) {
	return obj->type == ObjectType::O_CHARACTER;
}

bool is_string(Object* obj) {
	return obj->type == ObjectType::O_STRING;
}

bool is_null(Object* obj) {
	return obj->type == ObjectType::O_NULL;
}

bool is_true(Object *obj) {
	return obj->type == ObjectType::O_BOOL && obj->boolean;
}

bool is_pair(Object* obj) {
	return obj->type == ObjectType::O_PAIR;
}

bool is_symbol(Object* obj) {
	return obj->type == ObjectType::O_SYMBOL;
}

bool is_error(Object* obj) {
	return obj->type == ObjectType::O_ERROR;
}

bool is_primitive_procedure(Object* obj) {
	return obj->type == ObjectType::O_PPROC;
}

bool is_procedure(Object* obj) {
	return obj->type == ObjectType::O_PROC;
}

Object* car(Object* pair) {
	return pair->car;
}

Object* cdr(Object* pair) {
	return pair->cdr;
}

Object* Constants::Null = new Object(ObjectType::O_NULL);
Object* Constants::False = new Object(false);
Object* Constants::True = new Object(true);