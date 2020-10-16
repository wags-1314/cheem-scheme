#include "print.h"

#include <sstream>
#include <iostream>

/*
std::string print_object(Object* object) {
	std::stringstream ss;
	return print(object, ss);
}
*/

std::string print_pair(Object* object) {
	std::stringstream ss;
	ss << print_object(object->car);
	if(is_pair(object->cdr)) {
		ss << " ";
		ss << print_pair(object->cdr);
	} else if(is_null(object->cdr)) {
		ss << "";
	} else {
		ss << " . ";
		ss << print_object(object->cdr);
	}
	return ss.str();
}

std::string print_object(Object* object) {
	std::stringstream ss;
	//print_object_type(object->type, std::cout);
	if(is_integer(object)) {
		ss << object->integer;
	} else if (is_boolean(object)) {
		if(is_true(object)) {
			ss << "#t";
		} else {
			ss << "#f";
		}
	} else if(is_character(object)) {
		if(object->character == '\n') {
			ss << "#\\newline";
		} else if(object->character == ' ') {
			ss << "#\\space";
		} else {
			ss << "#\\" << object->character;
		}
	} else if(is_string(object)) {
		ss << "\"" << object->string << "\"";
	} else if(is_pair(object)) {
		ss << "(";
		ss << print_pair(object);
		ss << ")";
	} else if(is_null(object)) {
		ss << "()";
	} else if(is_symbol(object)) {
		ss << object->string;
	} else if(is_error(object)) {
		ss << object->string;
	}

	return ss.str();
}