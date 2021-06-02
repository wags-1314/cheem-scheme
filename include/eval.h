#ifndef CHEEM_EVAL_H
#define CHEEM_EVAL_H

#include "object.h"
#include "environment.h"

bool is_self_evaluating(Object* object);
bool does_list_start_with(Object* object, std::string string);
bool is_quoted(Object* object);
bool is_definition(Object* object);
bool is_set(Object* object);
bool is_lambda(Object* object);

Object* add_pproc(Object* arguments);

/**
 * @brief      looks up value of symbol in environment
 *
 * @param      object  The object
 * @param      env     The environment
 *
 * @return     returns value if symbol has been initialized
 */
Object* lookup_variable(Object* object, Environment* env);

/**
 * @brief      quotes the object
 *
 * @param      object  The object
 *
 * @return     quoted object
 */
Object* quote(Object* object);

/**
 * @brief      defines a variable
 *
 * @param      object  The object
 * @param      env     The environment
 *
 * @return     value of defines variable
 */
Object* define_variable(Object* object, Environment* env);

/**
 * @brief      Sets the variable.
 *
 * @param      object  The object
 * @param      env     The new value
 *
 * @return     sets the variable if it has been already initialized
 */
Object* set_variable(Object* object, Environment* env);

/**
 * @brief      evaluates a cheem-scheme object
 *
 * @param      object  The object
 * @param      env     The environment
 *
 * @return     returns evaluated object
 */
Object* evaluate(Object* object, Environment* env);

Object* evaluate_list(Object* list, Environment* env);

#endif