#ifndef AVION_H
#define AVION_H

#include <string>
#include <sstream>

struct Avion {
    std::string vuelo;
    std::string numero_de_registro;
    std::string modelo;
    std::string fabricante;
    int ano_fabricacion = 0;
    int capacidad = 0;
    int peso_max_despegue = 0;
    std::string aerolinea;
    std::string estado; // "Disponible" o "Mantenimiento"

    std::string toString() const {
        std::ostringstream oss;
        oss << "Vuelo: " << vuelo
            << ", Registro: " << numero_de_registro
            << ", Modelo: " << modelo
            << ", Fabricante: " << fabricante
            << ", Año: " << ano_fabricacion
            << ", Capacidad: " << capacidad
            << ", PesoMax:" << peso_max_despegue
            << ", Aerolinea: " << aerolinea
            << ", Estado: " << estado;
        return oss.str();
    }
};

#endif // AVION_H
