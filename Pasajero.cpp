#include "Pasajero.h"

Pasajero::Pasajero() : nombre(""), nacionalidad(""), numero_de_pasaporte(""), vuelo(""), asiento(0),
                       destino(""), origen(""), equipaje_facturado(0) {}

Pasajero::Pasajero(std::string n, std::string na, std::string np, std::string v, int a, std::string d, std::string o, int ef)
    : nombre(n), nacionalidad(na), numero_de_pasaporte(np), vuelo(v), asiento(a),
      destino(d), origen(o), equipaje_facturado(ef) {}

void Pasajero::mostrar() const {
    std::cout << "Nombre: " << nombre << ", Nacionalidad: " << nacionalidad
              << ", Pasaporte: " << numero_de_pasaporte << ", Vuelo: " << vuelo
              << ", Asiento: " << asiento << ", Destino: " << destino
              << ", Origen: " << origen << ", Equipaje: " << equipaje_facturado << std::endl;
}

// Ordenamiento: primero por vuelo, luego por asiento
bool Pasajero::operator<(const Pasajero& otro) const {
    if (vuelo != otro.vuelo) return vuelo < otro.vuelo;
    return asiento < otro.asiento;
}