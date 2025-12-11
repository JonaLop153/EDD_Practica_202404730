#ifndef PASAJERO_H
#define PASAJERO_H

#include <string>
#include <iostream>

class Pasajero {
public:
    std::string nombre;
    std::string nacionalidad;
    std::string numero_de_pasaporte;
    std::string vuelo;
    int asiento;
    std::string destino;
    std::string origen;
    int equipaje_facturado;

    Pasajero();
    Pasajero(std::string n, std::string na, std::string np, std::string v, int a, std::string d, std::string o, int ef);
    void mostrar() const;
    bool operator<(const Pasajero& otro) const; // Para ordenar en la lista doble
};

#endif