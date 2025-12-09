#ifndef MENU_H
#define MENU_H

#include "ListaCircularDoble.h"
#include "ColaPasajeros.h"
#include "PilaEquipaje.h"
#include "ListaPasajerosOrdenada.h"
#include <string>

class Menu {
private:
    ListaCircularDoble& disponibles;
    ListaCircularDoble& mantenimiento;
    ColaPasajeros& cola;
    PilaEquipaje& pila;
    ListaPasajerosOrdenada& lista;
public:
    Menu(ListaCircularDoble& d, ListaCircularDoble& m, ColaPasajeros& c, PilaEquipaje& p, ListaPasajerosOrdenada& l);
    void mostrar();
    void procesarCambios(const std::string& archivo);
};

#endif // MENU_H
