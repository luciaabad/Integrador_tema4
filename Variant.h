#ifndef TINY_LISP_VARIANT_H
#define TINY_LISP_VARIANT_H

#include <string>
#include <vector>
#include <map>
#include <memory>
#include "libs/json11/json11.h" // Usamos json11 en lugar de jsonlib

enum variant_type { Symbol, Number, List, Proc, Lambda, Cadena };

// Declaración adelantada de Entorno
struct Entorno;

class Variant {
public:
    // Definición de tipos
    using proc_type = Variant(*)(const std::vector<Variant>&, Entorno&);

    variant_type type;             // Tipo de la variante
    std::string val;               // Valor del símbolo o cadena
    double number;                 // Valor numérico (para Number)
    std::vector<Variant> list;     // Lista de Variants (para List)
    proc_type proc;                // Puntero a función (para Proc)
    std::shared_ptr<Entorno> env;  // Entorno asociado (para Lambda)

    // Constructores
    Variant(variant_type type = Symbol)
        : type(type), val(""), number(0), proc(nullptr), env(nullptr) {}
    Variant(const std::string& val)
        : type(Cadena), val(val), number(0), proc(nullptr), env(nullptr) {}
    Variant(double num)
        : type(Number), val(""), number(num), proc(nullptr), env(nullptr) {}
    Variant(proc_type func)
        : type(Proc), val(""), number(0), proc(func), env(nullptr) {}
    Variant(const std::vector<Variant>& lst)
        : type(List), val(""), number(0), proc(nullptr), list(lst), env(nullptr) {}

    // Métodos principales
    std::string to_string() const;
    std::string to_json_string() const;
    static Variant from_json_string(const std::string& json);
    static Variant parse_json(const json11::Json& json_obj);

    // Métodos auxiliares
    bool is_number() const { return type == Number; }
    bool is_symbol() const { return type == Symbol; }
    bool is_string() const { return type == Cadena; }
    bool is_list() const { return type == List; }
};

#endif // TINY_LISP_VARIANT_H
