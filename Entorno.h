#ifndef TINY_LISP_ENTORNO_H
#define TINY_LISP_ENTORNO_H

#include <map>
#include <string>
#include <memory>
#include "Variant.h"

// Clase para manejar el entorno de ejecución
struct Entorno {
    std::shared_ptr<Entorno> parent;            // Entorno padre
    std::map<std::string, Variant> variables;  // Variables locales

    Entorno(std::shared_ptr<Entorno> parent = nullptr)
        : parent(parent) {}

    // Buscar una variable en el entorno actual o en los padres
    Variant buscar(const std::string& nombre) const {
        if (variables.find(nombre) != variables.end()) {
            return variables.at(nombre);
        } else if (parent) {
            return parent->buscar(nombre);
        }
        throw std::runtime_error("Variable no encontrada: " + nombre);
    }

    // Asignar una variable en el entorno actual
    void asignar(const std::string& nombre, const Variant& valor) {
        variables[nombre] = valor;
    }
};

#endif // TINY_LISP_ENTORNO_H
