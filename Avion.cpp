#include "Avion.h"

Avion::Avion() : vuelo(""), numero_de_registro(""), modelo(""), fabricante(""), ano_fabricacion(0),
                 capacidad(0), peso_max_despegue(0.0), aerolinea(""), estado("") {}

Avion::Avion(std::string v, std::string nr, std::string m, std::string f, int af, int c, double pmd, std::string a, std::string e)
    : vuelo(v), numero_de_registro(nr), modelo(m), fabricante(f), ano_fabricacion(af),
      capacidad(c), peso_max_despegue(pmd), aerolinea(a), estado(e) {}

void Avion::mostrar() const {
    std::cout << "Vuelo: " << vuelo << ", Registro: " << numero_de_registro
              << ", Modelo: " << modelo << ", Fabricante: " << fabricante
              << ", Año: " << ano_fabricacion << ", Capacidad: " << capacidad
              << ", Peso Max: " << peso_max_despegue << ", Aerolínea: " << aerolinea
              << ", Estado: " << estado << std::endl;
}