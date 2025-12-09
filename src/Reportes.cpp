#include "../include/Reportes.h"
#include <cstdlib>
#include <iostream>

#ifdef _WIN32
#include <windows.h>
#include <shellapi.h>
#endif

namespace Reportes {

void generarReporteAviones(const ListaCircularDoble& lista, const std::string& titulo, const std::string& archivo) {
    lista.generarDot(archivo, titulo);
}

void generarReporteCola(const ColaPasajeros& cola, const std::string& titulo, const std::string& archivo) {
    cola.generarDot(archivo, titulo);
}

void generarReportePila(const PilaEquipaje& pila, const std::string& titulo, const std::string& archivo) {
    pila.generarDot(archivo, titulo);
}

void generarReporteListaPasajeros(const ListaPasajerosOrdenada& lista, const std::string& titulo, const std::string& archivo) {
    lista.generarDot(archivo, titulo);
}

void dotToPng(const std::string& dotFile, const std::string& pngFile) {
    std::string cmd = "dot -Tpng \"" + dotFile + "\" -o \"" + pngFile + "\"";
    int r = std::system(cmd.c_str());
    if (r != 0) {
        std::cerr << "Advertencia: dot no pudo generar PNG. Asegure Graphviz instalado.\n";
    }
}

void abrirPNG(const std::string& pngFile) {
#ifdef _WIN32
    ShellExecuteA(NULL, "open", pngFile.c_str(), NULL, NULL, SW_SHOWNORMAL);
#else
    std::string cmd = "xdg-open \"" + pngFile + "\"";
    std::system(cmd.c_str());
#endif
}

} // namespace Reportes
