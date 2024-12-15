#include "Variant.h"
#include "libs/json11/json11.h"

std::string Variant::to_string() const {
    switch (type) {
        case Symbol:
        case Cadena:
            return val;
        case Number:
            return std::to_string(number);
        case List: {
            std::string result = "(";
            for (const auto& item : list) {
                result += item.to_string() + " ";
            }
            if (!list.empty()) {
                result.pop_back(); // Eliminar el último espacio
            }
            result += ")";
            return result;
        }
        default:
            return "<unknown>";
    }
}

std::string Variant::to_json_string() const {
    switch (type) {
        case Symbol:
        case Cadena:
            return "\"" + val + "\"";
        case Number:
            return std::to_string(number);
        case List: {
            std::string result = "[";
            for (const auto& item : list) {
                result += item.to_json_string() + ", ";
            }
            if (!list.empty()) {
                result.erase(result.size() - 2); // Eliminar la última coma
            }
            result += "]";
            return result;
        }
        default:
            return "<unknown>";
    }
}

Variant Variant::from_json_string(const std::string& json) {
    std::string err;
    json11::Json parsed = json11::Json::parse(json, err);
    if (!err.empty()) {
        throw std::runtime_error("Error parsing JSON: " + err);
    }
    return parse_json(parsed);
}

Variant Variant::parse_json(const json11::Json& json_obj) {
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
    } else if (json_obj.is_object()) {
        // Caso para representar objetos de algún tipo
        return Variant(); // Necesitarás definir cómo manejar objetos si es necesario
    }
    throw std::runtime_error("Unsupported JSON type");
}
