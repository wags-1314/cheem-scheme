#include "environment.h"

Environment* Environment::find(std::string key) {
	Environment* curr_env = this;
	while(true) {
		if(curr_env->is_key_in_lookup_table(key)) {
			return curr_env;
		} else {
			if(curr_env->outer_environment != nullptr) {
				curr_env = curr_env->outer_environment;
			} else {
				return nullptr;
			}
		}
	}
}

Object* Environment::get(std::string key) {
	Environment* env = find(key);
	if(env != nullptr) {
		return env->lookup_table[key];
	} else {
		return nullptr;
	}
}

void Environment::set(std::string key, Object* value) {
	lookup_table[key] = value;
}

bool Environment::is_key_in_lookup_table(std::string key) {
	return lookup_table.find(key) != lookup_table.end();
}
