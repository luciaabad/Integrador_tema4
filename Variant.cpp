//
// Created by Lucia Abad on 15/12/24.
//

#include "Variant.h"
#include <sstream>
#include <stdexcept>

// Convertir Variant a una representación en texto
std::string Variant::to_string() const {
    std::ostringstream oss;
    switch (type) {
        case Symbol: return val;
        case Number: oss << number; return oss.str();
        case Cadena: return "\"" + val + "\"";
        case List: {
            oss << "(";
            for (size_t i = 0; i < list.size(); ++i) {
                oss << list[i].to_string();
                if (i != list.size() - 1) oss << " ";
            }
            oss << ")";
            return oss.str();
        }
        case Proc: return "<procedure>";
        case Lambda: return "<lambda>";
    }
    return "<unknown>";
}

// Convertir Variant a JSON
std::string Variant::to_json_string() const {
    using namespace json11;
    switch (type) {
        case Symbol: return Json(val).dump();
        case Number: return Json(number).dump();
        case Cadena: return Json(val).dump();
        case List: {
            std::vector<Json> json_list;
            for (const auto& item : list) {
                json_list.push_back(Json::parse(item.to_json_string()));
            }
            return Json(json_list).dump();
        }
        case Proc: return "\"<procedure>\"";
        case Lambda: return "\"<lambda>\"";
    }
    return "\"<unknown>\"";
}

// Crear un Variant desde una cadena JSON
Variant Variant::from_json_string(const std::string& json) {
    std::string error;
    auto json_obj = json11::Json::parse(json, error);
    if (!error.empty()) throw std::runtime_error("Error al parsear JSON: " + error);
    return parse_json(json_obj);
}

// Parsear un objeto JSON a un Variant
Variant Variant::parse_json(const jsonlib::Json& json_obj) {
    if (json_obj.is_string()) {
        return Variant(json_obj.string_value());
    } else if (json_obj.is_number()) {
        return Variant(json_obj.number_value());
    } else if (json_obj.is_array()) {
        std::vector<Variant> list;
        for (const auto& item : json_obj.array_items()) {
            list.push_back(parse_json(item));
        }
        return Variant(list);
    } else {
        throw std::runtime_error("Tipo de JSON no soportado");
    }
}