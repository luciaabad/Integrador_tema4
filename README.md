# Integrador_tema4
https://github.com/luciaabad/Integrador_tema4.git
Proyecto: Tiny Lisp - Intérprete en C++

Descripción:
Este proyecto es un intérprete simple de Lisp basado en C++, que utiliza una clase Variant para representar diferentes tipos de datos, como símbolos, números, listas y procedimientos. También implementa la capacidad de parsear y generar JSON utilizando la biblioteca json11.

Estructura del Proyecto:

/tiny-lisp
├── CMakeLists.txt
├── README.txt
├── main.cpp
├── Variant.h
├── Variant.cpp
├── Entorno.h
└── libs/
└── json11/
├── json11.h
└── json11.cpp

1. main.cpp: Contiene el código principal y las pruebas.
2. Variant.h: Define la clase Variant, que maneja los diferentes tipos de datos de Lisp.
3. Variant.cpp: Implementa los métodos de la clase Variant.
4. Entorno.h: Define la estructura del entorno (Entorno), que mantiene las variables y sus valores.*
5. libs/json11/: Contiene el código de la biblioteca json11, con los archivos json11.h y json11.cpp.

*no incluimos Entorno.cpp  porque no necesitamos agregar ninguna implementación adicional ya que todo se maneja en el archivo de cabecera Entorno.h.

Instrucciones de Instalación:

1. Incluir json11:
   Incluir la biblioteca json11 en la carpeta libs/json11. Se ha descargado del enlace: https://github.com/dropbox/json11/blob/master/json11

2. Crear el archivo CMakeLists.txt:
   El archivo CMakeLists.txt debe estar correctamente configurado para compilar todo el proyecto.

3. Crear el resto de archivos que aparecen en la estructura del proyecto.

4. Ejecutar el Programa:
   Una vez que el proyecto se haya compilado correctamente, puedes ejecutar el programa.

Se mostrarán los resultados de las pruebas definidas en main.cpp.

Cómo usar el intérprete:

El programa permite probar los siguientes tipos de datos y operaciones:

1. Números: Puedes asignar y operar con números.
2. Símbolos: Puedes usar símbolos como variables.
3. Listas: Soporta la manipulación de listas.
4. Procedimientos: Puedes definir y llamar procedimientos (funciones).
5. JSON: Puedes convertir entre objetos Lisp y representaciones JSON usando parse_json() y to_json_string().

Ejemplo de Uso:

1. Asignación de variables:
   global_env->asignar("x", Variant(42.0));

2. Definición de un procedimiento (función):
   Variant test_proc(const std::vector<Variant>& args, Entorno& env) {
   if (args.size() == 2 && args[0].is_number() && args[1].is_number()) {
   return Variant(args[0].number + args[1].number);  // Suma de dos números
   }
   return Variant("Error: invalid arguments");
   }

3. Conversión a JSON:
   std::string json_str = R"({"name": "TinyLisp", "x": 42.0})";
   json11::Json json_obj = json11::Json::parse(json_str, err);
   Variant parsed_variant = Variant::parse_json(json_obj);