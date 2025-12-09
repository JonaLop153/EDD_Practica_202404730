#ifndef PASAJERO_H
#define PASAJERO_H

#include <string>
#include <sstream>

struct Pasajero {
    std::string nombre;
    std::string nacionalidad;
    std::string numero_de_pasaporte;
    std::string vuelo;
    int asiento = 0;
    std::string destino;
    std::string origen;
    int equipaje_facturado = 0;

    std::string toString() const {
        std::ostringstream oss;
        oss << "Nombre: " << nombre
            << ", Pasaporte: " << numero_de_pasaporte
            << ", Vuelo: " << vuelo
            << ", Asiento: " << asiento
            << ", Origen: " << origen
            << ", Destino: " << destino
            << ", Equipaje: " << equipaje_facturado;
        return oss.str();
    }
};

#endif // PASAJERO_H
