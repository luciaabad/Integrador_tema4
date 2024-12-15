//
// Created by Lucia Abad on 15/12/24.
//

#include <iostream>
#include "Variant.h"
#include "Entorno.h"

int main() {
    // Crear un entorno global
    auto global_env = std::make_shared<Entorno>();

    // Asignar variables al entorno
    global_env->asignar("x", Variant(42.0));
    global_env->asignar("name", Variant("TinyLisp"));

    // Buscar y mostrar las variables
    std::cout << "x: " << global_env->buscar("x").to_string() << std::endl;
    std::cout << "name: " << global_env->buscar("name").to_string() << std::endl;

    // Probar conversión a JSON
    Variant json_list = Variant(std::vector<Variant>{Variant(1), Variant(2), Variant(3)});
    std::cout << "JSON: " << json_list.to_json_string() << std::endl;

    return 0;
}