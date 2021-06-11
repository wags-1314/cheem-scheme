#include "primitive_procedures.h"
#include "object.h"

Object* sub_pproc(Object* arguments) {
	long sum = (car(arguments))->integer;
	arguments = cdr(arguments);

	while(!is_null(arguments)) {
		sum -= (car(arguments)) -> integer;
		arguments = cdr(arguments);
	}

	return make_object_integer(sum);
}

Object* add_pproc(Object* arguments) {
	long sum = 0;

	if(is_null(arguments)) {
		return make_object_error("+ needs atleast 1 argument");
	}

	while(!is_null(arguments)) {

		if(!is_integer(car(arguments))) {
			return make_object_error("+ only takes integer arguments");
		}
		sum += (car(arguments)) -> integer;
		arguments = cdr(arguments);
	}

	return make_object_integer(sum);
}

Object* mult_pproc(Object* arguments) {
	long sum = 1;

	while(!is_null(arguments)) {
		sum *= (car(arguments)) -> integer;
		arguments = cdr(arguments);
	}

	return make_object_integer(sum);
}

Object* eq_int_pproc(Object* arguments) {
	auto a = car(arguments);
	auto b = car(cdr(arguments));

	if((a->integer) == (b->integer)) {
		return Constants::True;
	} else {
		return Constants::False;
	}
}

Object* eq_pproc(Object* arguments) {
	auto a = car(arguments);
	auto b = car(cdr(arguments));

	if(a->type != b->type) {
		return Constants::False;
	} else {
		switch(a->type) {
		case ObjectType::O_INTEGER:
			return bool_to_object_bool(a->integer == b->integer);
			break;
		case ObjectType::O_BOOL:
			return bool_to_object_bool(a->boolean == b->boolean);
			break;
		case ObjectType::O_CHARACTER:
			return bool_to_object_bool(a->character == b->character);
			break;
		case ObjectType::O_STRING:
			return bool_to_object_bool(a->string == b->string);
			break;
		case ObjectType::O_NULL:
			return Constants::True;
			break;
		case ObjectType::O_PAIR:
			return bool_to_object_bool((a->car == b->car) && (a->cdr == b->cdr));
			break;
		case ObjectType::O_SYMBOL:
			return bool_to_object_bool(a->string == b->string);
			break;

		case ObjectType::O_PPROC:
			return bool_to_object_bool(a->func == b->func);
			break;

		case ObjectType::O_PROC:
			return bool_to_object_bool((a->car == b->car) && (a->cdr == b->cdr));
			break;

		default:
			return make_object_error("mistake");
	}
	}
}

Object* quit_pproc(Object* arguments) {
	exit(0);
}