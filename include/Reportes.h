#ifndef REPORTES_H
#define REPORTES_H

#include "ListaCircularDoble.h"
#include "ColaPasajeros.h"
#include "PilaEquipaje.h"
#include "ListaPasajerosOrdenada.h"
#include <string>

namespace Reportes {
    void generarReporteAviones(const ListaCircularDoble& lista, const std::string& titulo, const std::string& archivo);
    void generarReporteCola(const ColaPasajeros& cola, const std::string& titulo, const std::string& archivo);
    void generarReportePila(const PilaEquipaje& pila, const std::string& titulo, const std::string& archivo);
    void generarReporteListaPasajeros(const ListaPasajerosOrdenada& lista, const std::string& titulo, const std::string& archivo);

    void dotToPng(const std::string& dotFile, const std::string& pngFile);
    void abrirPNG(const std::string& pngFile);
}

#endif // REPORTES_H
