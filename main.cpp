#include <iostream>
#include <fstream>
#include <string>
#include "json.hpp"
#include "Avion.h"
#include "Pasajero.h"
#include "ListaCircularDoble.h"
#include "Cola.h"
#include "Pila.h"
#include "ListaDoble.h"

using json = nlohmann::json;

void cargarAviones(ListaCircularDoble<Avion>& disponibles, ListaCircularDoble<Avion>& mantenimiento);
void cargarPasajeros(Cola<Pasajero>& colaRegistro);
void procesarCambios(ListaCircularDoble<Avion>& disponibles, ListaCircularDoble<Avion>& mantenimiento,
                     Cola<Pasajero>& colaRegistro, Pila<int>& pilaEquipaje, ListaDoble<Pasajero>& pasajerosRegistrados);
void mostrarMenu();
void generarReportes(ListaCircularDoble<Avion>& disponibles, ListaCircularDoble<Avion>& mantenimiento,
                     Cola<Pasajero>& colaRegistro, Pila<int>& pilaEquipaje, ListaDoble<Pasajero>& pasajerosRegistrados);
void consultarPasajero(ListaDoble<Pasajero>& pasajerosRegistrados);

int main() {
    ListaCircularDoble<Avion> avionesDisponibles;
    ListaCircularDoble<Avion> avionesMantenimiento;
    Cola<Pasajero> colaRegistro;
    Pila<int> pilaEquipaje;
    ListaDoble<Pasajero> pasajerosRegistrados;

    int opcion;
    bool salir = false;

    while (!salir) {
        mostrarMenu();
        std::cin >> opcion;
        std::cin.ignore();

        switch (opcion) {
            case 1:
                cargarAviones(avionesDisponibles, avionesMantenimiento);
                std::cout << "Aviones cargados exitosamente.\n";
                break;
            case 2:
                cargarPasajeros(colaRegistro);
                std::cout << "Pasajeros cargados exitosamente.\n";
                break;
            case 3:
                procesarCambios(avionesDisponibles, avionesMantenimiento, colaRegistro, pilaEquipaje, pasajerosRegistrados);
                std::cout << "Cambios procesados exitosamente.\n";
                break;
            case 4:
                consultarPasajero(pasajerosRegistrados);
                break;
            case 5:
                generarReportes(avionesDisponibles, avionesMantenimiento, colaRegistro, pilaEquipaje, pasajerosRegistrados);
                break;
            case 6:
                salir = true;
                std::cout << "Saliendo del programa...\n";
                break;
            default:
                std::cout << "Opción inválida. Intente nuevamente.\n";
        }
    }

    return 0;
}

void mostrarMenu() {
    std::cout << "\n-----MENU-----\n";
    std::cout << "1. Carga de aviones\n";
    std::cout << "2. Carga de pasajeros\n";
    std::cout << "3. Carga de movimientos\n";
    std::cout << "4. Consultar pasajero\n";
    std::cout << "5. Visualizar reportes\n";
    std::cout << "6. Salir\n";
    std::cout << "Ingrese su opción: ";
}

void cargarAviones(ListaCircularDoble<Avion>& disponibles, ListaCircularDoble<Avion>& mantenimiento) {
    std::ifstream archivo("aviones.json");
    if (!archivo.is_open()) {
        std::cerr << "Error: No se pudo abrir aviones.json\n";
        return;
    }

    json data = json::parse(archivo);
    archivo.close();

    for (const auto& item : data) {
        Avion avion(
            item["vuelo"],
            item["numero_de_registro"],
            item["modelo"],
            item["fabricante"],
            item["ano_fabricacion"],
            item["capacidad"],
            item["peso_max_despegue"],
            item["aerolinea"],
            item["estado"]
        );

        if (avion.estado == "Disponible") {
            disponibles.insertar(avion);
        } else if (avion.estado == "Mantenimiento") {
            mantenimiento.insertar(avion);
        }
    }
}

void cargarPasajeros(Cola<Pasajero>& colaRegistro) {
    std::ifstream archivo("pasajeros.json");
    if (!archivo.is_open()) {
        std::cerr << "Error: No se pudo abrir pasajeros.json\n";
        return;
    }

    json data = json::parse(archivo);
    archivo.close();

    for (const auto& item : data) {
        Pasajero pasajero(
            item["nombre"],
            item["nacionalidad"],
            item["numero_de_pasaporte"],
            item["vuelo"],
            item["asiento"],
            item["destino"],
            item["origen"],
            item["equipaje_facturado"]
        );
        colaRegistro.encolar(pasajero);
    }
}

void procesarCambios(ListaCircularDoble<Avion>& disponibles, ListaCircularDoble<Avion>& mantenimiento,
                     Cola<Pasajero>& colaRegistro, Pila<int>& pilaEquipaje, ListaDoble<Pasajero>& pasajerosRegistrados) {
    std::ifstream archivo("Cambios.txt");
    if (!archivo.is_open()) {
        std::cerr << "Error: No se pudo abrir Cambios.txt\n";
        return;
    }

    std::string linea;
    while (std::getline(archivo, linea)) {
        if (linea.empty()) continue;

        if (linea.find("IngresoEquipajes") != std::string::npos) {
            if (!colaRegistro.estaVacia()) {
                Pasajero pasajero = colaRegistro.desencolar();
                if (pasajero.equipaje_facturado > 0) {
                    pilaEquipaje.apilar(pasajero.equipaje_facturado);
                }
                pasajerosRegistrados.insertarOrdenado(pasajero);
            }
        } else if (linea.find("MantenimientoAviones") != std::string::npos) {
            size_t pos = linea.find(',');
            if (pos == std::string::npos) continue;
            size_t pos2 = linea.find(',', pos + 1);
            if (pos2 == std::string::npos) continue;
            std::string accion = linea.substr(pos + 1, pos2 - pos - 1);
            std::string registro = linea.substr(pos2 + 1);

            // ✅ Eliminar punto y coma al final
            if (!registro.empty() && registro.back() == ';') {
                registro.pop_back();
            }

            if (accion == "Ingreso") {
                Avion* avion = disponibles.buscarPorRegistro(registro);
                if (avion) {
                    Avion copia = *avion;               // ✅ Copia ANTES de eliminar
                    copia.estado = "Mantenimiento";
                    disponibles.eliminar(registro);     // ✅ Elimina el original
                    mantenimiento.insertar(copia);      // ✅ Inserta la copia segura
                }
            } else if (accion == "Salida") {
                Avion* avion = mantenimiento.buscarPorRegistro(registro);
                if (avion) {
                    Avion copia = *avion;
                    copia.estado = "Disponible";
                    mantenimiento.eliminar(registro);
                    disponibles.insertar(copia);
                }
            }
        }
    }
    archivo.close();
}

void consultarPasajero(ListaDoble<Pasajero>& pasajerosRegistrados) {
    std::string pasaporte;
    std::cout << "Ingrese el número de pasaporte: ";
    std::getline(std::cin, pasaporte);

    Pasajero* encontrado = pasajerosRegistrados.buscarPorPasaporte(pasaporte);
    if (encontrado) {
        std::cout << "Pasajero encontrado:\n";
        encontrado->mostrar();
    } else {
        std::cout << "No se encontró ningún pasajero con ese pasaporte.\n";
    }
}

void generarReportes(ListaCircularDoble<Avion>& disponibles, ListaCircularDoble<Avion>& mantenimiento,
                     Cola<Pasajero>& colaRegistro, Pila<int>& pilaEquipaje, ListaDoble<Pasajero>& pasajerosRegistrados) {
    system("mkdir -p reportes");

    disponibles.generarDot("reportes/aviones_disponibles.dot");
    mantenimiento.generarDot("reportes/aviones_mantenimiento.dot");
    colaRegistro.generarDot("reportes/cola_registro.dot");
    pilaEquipaje.generarDot("reportes/pila_equipaje.dot");
    pasajerosRegistrados.generarDot("reportes/pasajeros_registrados.dot");

    // Intentar generar PNGs (silenciar errores si dot no está)
    system("dot -Tpng reportes/aviones_disponibles.dot -o reportes/aviones_disponibles.png 2>nul");
    system("dot -Tpng reportes/aviones_mantenimiento.dot -o reportes/aviones_mantenimiento.png 2>nul");
    system("dot -Tpng reportes/cola_registro.dot -o reportes/cola_registro.png 2>nul");
    system("dot -Tpng reportes/pila_equipaje.dot -o reportes/pila_equipaje.png 2>nul");
    system("dot -Tpng reportes/pasajeros_registrados.dot -o reportes/pasajeros_registrados.png 2>nul");

    std::cout << "Reportes generados en la carpeta 'reportes'.\n";
}