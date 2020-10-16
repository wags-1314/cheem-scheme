#ifndef CHEEM_ENVIRONMENT_H
#define CHEEM_ENVIRONMENT_H

#include <map>
#include <string>
#include <iostream>
#include "object.h"

class Environment {
	Environment* outer_environment;
public:
	std::map<std::string, Object*> lookup_table;
	Environment(Environment* outer=nullptr) : outer_environment(outer) { }

	/**
	 * @brief      finds the enclosed environment which contains the key
	 *
	 * @param[in]  key   The key
	 *
	 * @return     return enviroment if a environment with the key is found
	 */
	Environment* find(std::string key);

	/**
	 * @brief      gets the value corresponding to the key, by searching all enclosed environments
	 *
	 * @param[in]  key   The key
	 *
	 * @return     returns the corresponding value
	 */
	Object* get(std::string key);

	/**
	 * @brief      sets the value to the given key
	 *
	 * @param[in]  key    The new value
	 * @param      value  The value
	 */
	void set(std::string key, Object* value);
	bool is_key_in_lookup_table(std::string key);
};

#endif