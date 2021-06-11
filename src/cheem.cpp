#include <iostream>
#include <string>
#include <fstream>
#include "scanner.h"
#include "parser.h"
#include "eval.h"
#include "object.h"
#include "print.h"
#include "environment.h"
#include "primitive_procedures.h"

Object* read(std::string source) {
    Scanner scanner = Scanner(source);	
    auto tokens = scanner.scan_tokens();
    Reader reader = Reader(tokens);
    Object *object = read_form(reader);
    return object;
}

Object* eval(Object* object, Environment* env, Stack& traceback) {
    return evaluate(object, env, traceback);
}

std::string print(Object* object, Stack traceback) {
    return print_object(object, traceback);
}

int main(int argc, char const *argv[]) {
    Environment* global_environment = new Environment();

    Object* obj_add = make_object_primitive_procedure(add_pproc);
    Object* obj_sub = make_object_primitive_procedure(sub_pproc);
    Object* obj_mult = make_object_primitive_procedure(mult_pproc);
    Object* obj_eq = make_object_primitive_procedure(eq_int_pproc);
    Object* obj_quit = make_object_primitive_procedure(quit_pproc);

    global_environment->set("+", obj_add);
    global_environment->set("=?", obj_eq);
    global_environment->set("-", obj_sub);
    global_environment->set("*", obj_mult);
    global_environment->set("quit", obj_quit);



    int line_number = 0;
    std::ifstream fin("cheem.txt"); // open this file for input

    

    std::string line;
    while(std::getline(fin, line)) {
        std::cout << line << '\n';
    }
    
    std::cout<<"============cheem-scheme v.1============\n";
    std::string source;
    while(true) {
        Stack traceback;
        std::cout << ++line_number << "] cheem> ";
        std::getline(std::cin, source);
        Object* expr = read(source);
        Object* evaluated_expr = eval(expr, global_environment, traceback);
        std::cout << print(evaluated_expr, traceback) << std::endl;
    }
    return 0;
}
