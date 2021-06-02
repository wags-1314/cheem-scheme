#include <iostream>
#include <string>
#include <fstream>
#include "scanner.h"
#include "parser.h"
#include "eval.h"
#include "object.h"
#include "print.h"
#include "environment.h"

Object* read(std::string source) {
    Scanner scanner = Scanner(source);	
    auto tokens = scanner.scan_tokens();
    Reader reader = Reader(tokens);
    Object *object = read_form(reader);
    return object;
}

Object* eval(Object* object, Environment* env) {
    return evaluate(object, env);
}

std::string print(Object* object) {
    return print_object(object);
}

int main(int argc, char const *argv[]) {
    Environment* global_environment = new Environment();

    Object* obj_add = make_object_primitive_procedure(add_pproc);

    global_environment->set("+", obj_add);



    int line_number = 0;
    std::ifstream fin("cheem.txt"); // open this file for input

    std::string line;
    while(std::getline(fin, line)) {
        std::cout << line << '\n';
    }


    
    std::cout<<"============cheem-scheme v.1============\n";
    std::string source;
    while(true) {
        std::cout << ++line_number << "] cheem> ";
        std::getline(std::cin, source);
        Object* expr = read(source);
        Object* evaluated_expr = eval(expr, global_environment);
        std::cout << print(evaluated_expr) << std::endl;
    }
    return 0;
}
