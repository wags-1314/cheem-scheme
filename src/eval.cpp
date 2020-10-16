#include "eval.h"
#include <iostream>

bool is_self_evaluating(Object* object) {
	switch(object->type) {
		case ObjectType::O_INTEGER:
		case ObjectType::O_BOOL:
		case ObjectType::O_STRING:
		case ObjectType::O_CHARACTER:
		return true;
		break;

		default:
		return false;
	}
}

bool does_list_start_with(Object* object, std::string string) {
	if(is_pair(object)) {
		Object* head = car(object);
		if(is_symbol(head)) {
			return !string.compare(head->string);
		} else {
			return false;
		}
	} else {
		return false;
	}
}

bool is_quoted(Object* object) {
	return does_list_start_with(object, "quote");
}

bool is_definition(Object* object) {
	return does_list_start_with(object, "define");
}

bool is_set(Object* object) {
	return does_list_start_with(object, "set!");
}

Object* lookup_variable(Object* object, Environment* env) {
	Object* value = env->get(object->string);
	if(value != nullptr) {
		return value;
	} else {
		return make_object_error("variable has not been initialized");
	}
}

Object* quote(Object* object) {
	return cdr(object);
}

Object* define_variable(Object* object, Environment* env) {
	Object* binding = cdr(object);
	Object* symbol = car(binding);
	Object* value = evaluate(car(cdr(binding)), env);
	if(!is_symbol(symbol)) {
		return make_object_error("values can only bound to symbols");
	} else {
		env->set(symbol->string, value);
		return value;
	}
}

Object* set_variable(Object* object, Environment* env) {
	Object* binding = cdr(object);
	Object* symbol = car(binding);
	Object* value = evaluate(car(cdr(binding)), env);
	if(!is_symbol(symbol)) {
		return make_object_error("values can only bound to symbols");
	} else {
		Environment* new_env = env->find(symbol->string);
		if(new_env != nullptr) {
			new_env->set(symbol->string, value);
			return value;
		} else {
			return make_object_error("variable has not been initialized");
		}
	}
}


Object* evaluate(Object* object, Environment* env) {
	if(is_self_evaluating(object)) {
		//self evaluating types
		//> integers
		//> booleans
		//> strings
		//> characters
		return object;
	} else if(is_symbol(object)) {
		//checking if its a variable
		return lookup_variable(object, env);
	} else if(is_quoted(object)) {
		return quote(object);
	} else if(is_definition(object)) {
		return define_variable(object,env);
	} else if(is_set(object)) {
		return set_variable(object, env);
	} else {
		return make_object_error("unknown");
	}

	/*else if(is_pair(object)) {
		Object* head = car(object);
		Object* tail = cdr(object);
		if(is_symbol(head)) {
			if(string_eq(head->str, "quote")) {
				return tail;
			} else if(string_eq(head->str, "define")) {
				Object* symbol = car(tail);
				Object* value = cdr(tail);

				//1. check if the symbol is actually a symbol
				if(!is_symbol(symbol)) {
					return make_object_error("");
				}

			} 

			else {
				return make_object_error("unknown procedure");
			}
		} else {
			return make_object_error("unknown procedure");
		}
	}*/
}