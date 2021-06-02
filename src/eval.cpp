#include "eval.h"
#include "util.h"
#include "print.h"
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
	return does_list_start_with(object, "def");
}

bool is_set(Object* object) {
	return does_list_start_with(object, "set!");
}

bool is_lambda(Object* object) {
	return does_list_start_with(object, "lambda");
}

Object* add_pproc(Object* arguments) {
	long sum = 0;

	while(!is_null(arguments)) {
		sum += (car(arguments)) -> integer;
		arguments = cdr(arguments);
	}

	return make_object_integer(sum);
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
			// check if quote
			return quote(object);

		} else if(is_definition(object)) {
			return define_variable(object, env);

		} else if(is_set(object)) {
			return set_variable(object, env);

		} else if(is_lambda(object)) {
			auto params = car(cdr(object));
			auto body = cdr(cdr(object));
			return make_object_procedure(params, body);

		} else if(is_pair(object)) {
			// this then should be a function
			// so we get the first item of the list and search the environment for it
			// if its a function we try to evaluate it
			// else we pass an error
			auto procedure = evaluate(car(object), env);

			if(is_primitive_procedure(procedure)) {
				auto arguments = evaluate_list(cdr(object), env);
				return (procedure->func)(arguments);			

			} else if(is_procedure(procedure)) {
				auto arguments = evaluate_list(cdr(object), env);
				auto params = car(procedure);
				auto body = car(cdr(procedure));

				// assume len(arguments) == len(params), will add check later
				Environment* proc_scope = new Environment(env);
				proc_scope->set_list(params, arguments);
				return evaluate(body, proc_scope);
			} else {
				return make_object_error("test");
			}
		}

		else {
			return make_object_error("unknown");

		}
	
}

Object* evaluate_list(Object* list, Environment* env) {
	if(is_null(list)) {
		return Constants::Null;
	} else {
		return cons(evaluate(car(list), env), evaluate_list(cdr(list), env));
	}
}