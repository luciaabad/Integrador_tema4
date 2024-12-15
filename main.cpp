#include <iostream>
#include "Variant.h"
#include "Entorno.h"
#include "libs/json11/json11.h"

// Función auxiliar de ejemplo para "Proc" (procedimientos)
Variant test_proc(const std::vector<Variant>& args, Entorno& env) {
    if (args.size() == 2 && args[0].is_number() && args[1].is_number()) {
        return Variant(args[0].number + args[1].number);  // Suma de dos números
    }
    return Variant("Error: invalid arguments");
}

int main() {
    // Crear un entorno global
    auto global_env = std::make_shared<Entorno>();

    // Asignar variables al entorno
    global_env->asignar("x", Variant(42.0));         // Número
    global_env->asignar("name", Variant("TinyLisp")); // Cadena
    global_env->asignar("add", Variant(test_proc));   // Procedimiento (función de suma)

    // Mostrar valores de las variables
    std::cout << "x: " << global_env->buscar("x").to_string() << std::endl;
    std::cout << "name: " << global_env->buscar("name").to_string() << std::endl;

    // Test: Procedimiento (sumar dos números)
    Variant sum_result = global_env->buscar("add").proc({Variant(5), Variant(7)}, *global_env);
    std::cout << "Sum result: " << sum_result.to_string() << std::endl;

    // Test: Lista
    Variant list_variant = Variant(std::vector<Variant>{Variant(1), Variant(2), Variant(3)});
    std::cout << "List: " << list_variant.to_string() << std::endl;

    // Test: JSON con distintos tipos
    std::string json_str = R"({
        "name": "TinyLisp",
        "x": 42.0,
        "list": [1, 2, 3],
        "symbol": "my_symbol"
    })";

    // Convertir JSON a un objeto Variant usando parse_json
    std::string err;
    json11::Json json_obj = json11::Json::parse(json_str, err);

    if (!err.empty()) {
        std::cerr << "Error parsing JSON: " << err << std::endl;
        return 1;
    }

    Variant parsed_variant = Variant::parse_json(json_obj);

    // Mostrar el resultado del parseo del JSON
    std::cout << "Parsed Variant (from JSON): " << parsed_variant.to_string() << std::endl;

    // Test: Parse de un número
    std::string num_json = "42";
    json11::Json num_obj = json11::Json::parse(num_json, err);
    Variant parsed_num = Variant::parse_json(num_obj);
    std::cout << "Parsed number: " << parsed_num.to_string() << std::endl;

    // Test: Parse de una cadena
    std::string str_json = "\"Hello, world!\"";
    json11::Json str_obj = json11::Json::parse(str_json, err);
    Variant parsed_str = Variant::parse_json(str_obj);
    std::cout << "Parsed string: " << parsed_str.to_string() << std::endl;

    // Test: Parse de una lista
    std::string list_json = "[1, 2, 3, 4]";
    json11::Json list_obj = json11::Json::parse(list_json, err);
    Variant parsed_list = Variant::parse_json(list_obj);
    std::cout << "Parsed list: " << parsed_list.to_string() << std::endl;

    return 0;
}