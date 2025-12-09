#include "../include/JsonLoader.h"
#include "../json.hpp"
#include <fstream>
#include <iostream>

using json = nlohmann::json;

bool JsonLoader::cargarAviones(const std::string& file, ListaCircularDoble& disp, ListaCircularDoble& mant) {
    std::ifstream f(file);
    if (!f.is_open()) {
        std::cerr << "No se pudo abrir " << file << "\n";
        return false;
    }
    json j;
    try {
        f >> j;
    } catch (...) {
        std::cerr << "Error leyendo JSON en " << file << "\n";
        return false;
    }
    if (!j.is_array()) return false;
    for (auto& x : j) {
        Avion a;
        a.vuelo = x.value("vuelo", "");
        a.numero_de_registro = x.value("numero_de_registro", "");
        a.modelo = x.value("modelo", "");
        a.fabricante = x.value("fabricante", "");
        a.ano_fabricacion = x.value("ano_fabricacion", 0);
        a.capacidad = x.value("capacidad", 0);
        a.peso_max_despegue = x.value("peso_max_despegue", 0);
        a.aerolinea = x.value("aerolinea", "");
        a.estado = x.value("estado", "Disponible");
        if (a.estado == "Disponible") disp.insertarFinal(a);
        else mant.insertarFinal(a);
    }
    return true;
}

bool JsonLoader::cargarPasajeros(const std::string& file, ColaPasajeros& cola) {
    std::ifstream f(file);
    if (!f.is_open()) {
        std::cerr << "No se pudo abrir " << file << "\n";
        return false;
    }
    json j;
    try {
        f >> j;
    } catch (...) {
        std::cerr << "Error leyendo JSON en " << file << "\n";
        return false;
    }
    if (!j.is_array()) return false;
    for (auto& x : j) {
        Pasajero p;
        p.nombre = x.value("nombre", "");
        p.nacionalidad = x.value("nacionalidad", "");
        p.numero_de_pasaporte = x.value("numero_de_pasaporte", "");
        p.vuelo = x.value("vuelo", "");
        p.asiento = x.value("asiento", 0);
        p.destino = x.value("destino", "");
        p.origen = x.value("origen", "");
        p.equipaje_facturado = x.value("equipaje_facturado", 0);
        cola.enqueue(p);
    }
    return true;
}
