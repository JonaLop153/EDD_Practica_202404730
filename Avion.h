#ifndef AVION_H
#define AVION_H

#include <string>
#include <iostream>

class Avion {
public:
    std::string vuelo;
    std::string numero_de_registro;
    std::string modelo;
    std::string fabricante;
    int ano_fabricacion;
    int capacidad;
    double peso_max_despegue;
    std::string aerolinea;
    std::string estado;

    Avion();
    Avion(std::string v, std::string nr, std::string m, std::string f, int af, int c, double pmd, std::string a, std::string e);
    void mostrar() const;
};

#endif