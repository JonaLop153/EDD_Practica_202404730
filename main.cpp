#include <iostream>
#include "include/ListaCircularDoble.h"
#include "include/ColaPasajeros.h"
#include "include/PilaEquipaje.h"
#include "include/ListaPasajerosOrdenada.h"
#include "include/JsonLoader.h"
#include "include/Menu.h"
#include "include/Reportes.h"

int main() {
    ListaCircularDoble disponibles;
    ListaCircularDoble mantenimiento;
    ColaPasajeros colaRegistro;
    PilaEquipaje pilaEquipaje;
    ListaPasajerosOrdenada listaPasajeros;

    // Cargar datos iniciales (archivos en data/)
    JsonLoader::cargarAviones("data/aviones.json", disponibles, mantenimiento);
    JsonLoader::cargarPasajeros("data/pasajeros.json", colaRegistro);

    // Crear carpeta reportes si no existe (solo intento)
    #ifdef _WIN32
    system("mkdir reportes 2>nul");
    #else
    system("mkdir -p reportes 2>/dev/null");
    #endif

    // Snapshot inicial: reportes del estado antes de procesar cambios
    Reportes::generarReporteAviones(disponibles, "Aviones Disponibles (Inicial)", "reportes/disp_initial.dot");
    Reportes::generarReporteAviones(mantenimiento, "Aviones Mantenimiento (Inicial)", "reportes/mant_initial.dot");

    // generar snapshot de la cola SIN vaciarla
    auto snapshot = colaRegistro.toVector();
    ColaPasajeros::generarDotDesdeVector(snapshot, "reportes/cola_initial.dot", "Cola Pasajeros (Inicial)");
    Reportes::dotToPng("reportes/cola_initial.dot", "reportes/cola_initial.png");

    // Iniciar menú
    Menu menu(disponibles, mantenimiento, colaRegistro, pilaEquipaje, listaPasajeros);
    menu.mostrar();

    return 0;
}
