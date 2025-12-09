#ifndef JSON_LOADER_H
#define JSON_LOADER_H

#include "ListaCircularDoble.h"
#include "ColaPasajeros.h"
#include <string>

namespace JsonLoader {
    bool cargarAviones(const std::string& file, ListaCircularDoble& disp, ListaCircularDoble& mant);
    bool cargarPasajeros(const std::string& file, ColaPasajeros& cola);
}

#endif // JSON_LOADER_H
