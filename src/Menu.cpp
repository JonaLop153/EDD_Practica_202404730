#include "../include/Menu.h"
#include "../include/Reportes.h"
#include <iostream>
#include <fstream>
#include <sstream>

Menu::Menu(ListaCircularDoble& d, ListaCircularDoble& m, ColaPasajeros& c, PilaEquipaje& p, ListaPasajerosOrdenada& l)
: disponibles(d), mantenimiento(m), cola(c), pila(p), lista(l) {}

void Menu::mostrar() {
    int op;
    do {
        std::cout << "\n--- MENU PRINCIPAL ---\n";
        std::cout << "Aviones disponibles: " << disponibles.size() << "  |  Mantenimiento: " << mantenimiento.size() << "\n";
        std::cout << "Cola pasajeros: " << cola.size() << "  |  Pila equipaje: " << pila.size() << "  |  Lista pasajeros: " << lista.size() << "\n";
        std::cout << "1. Aviones disponibles\n";
        std::cout << "2. Aviones en mantenimiento\n";
        std::cout << "3. Cola de pasajeros\n";
        std::cout << "4. Pila de equipaje\n";
        std::cout << "5. Lista de pasajeros\n";
        std::cout << "6. Procesar Cambios.txt\n";
        std::cout << "7. Generar reportes\n";
        std::cout << "8. Buscar pasajero\n";
        std::cout << "9. Salir\n";
        std::cout << "Opción: ";
        std::cin >> op;
        std::cin.ignore();

        if (op == 1) {
            disponibles.recorrer([](const Avion& a){ std::cout << a.toString() << "\n"; });
        } else if (op == 2) {
            mantenimiento.recorrer([](const Avion& a){ std::cout << a.toString() << "\n"; });
        } else if (op == 3) {
            cola.recorrer([](const Pasajero& p){ std::cout << p.toString() << "\n"; });
        } else if (op == 4) {
            pila.recorrer([](const EquipajeInfo& e){ std::cout << e.toString() << "\n"; });
        } else if (op == 5) {
            lista.recorrer([](const Pasajero& p){ std::cout << p.toString() << "\n"; });
        } else if (op == 6) {
            std::string fname = "data/Cambios.txt";
            procesarCambios(fname);
        } else if (op == 7) {
            // Generar reportes a archivos en reportes/
            Reportes::generarReporteAviones(disponibles, "Aviones Disponibles", "reportes/disp.dot");
            Reportes::generarReporteAviones(mantenimiento, "Aviones Mantenimiento", "reportes/mant.dot");
            Reportes::generarReporteCola(cola, "Cola Pasajeros", "reportes/cola.dot");
            Reportes::generarReportePila(pila, "Pila Equipaje", "reportes/pila.dot");
            Reportes::generarReporteListaPasajeros(lista, "Lista Pasajeros", "reportes/lista.dot");

            // Intento generar PNG (si dot instalado)
            Reportes::dotToPng("reportes/disp.dot", "reportes/disp.png");
            Reportes::dotToPng("reportes/mant.dot", "reportes/mant.png");
            Reportes::dotToPng("reportes/cola.dot", "reportes/cola.png");
            Reportes::dotToPng("reportes/pila.dot", "reportes/pila.png");
            Reportes::dotToPng("reportes/lista.dot", "reportes/lista.png");

            std::cout << "Reportes generados.\n";
        } else if (op == 8) {
            std::string pas;
            std::cout << "Pasaporte: ";
            std::getline(std::cin, pas);
            Pasajero* p = lista.buscarPorPasaporte(pas);
            if (p) std::cout << p->toString() << "\n";
            else std::cout << "No encontrado.\n";
        }
    } while (op != 9);
}

void Menu::procesarCambios(const std::string& archivo) {
    std::ifstream f(archivo);
    if (!f.is_open()) {
        std::cout << "No se pudo abrir: " << archivo << "\n";
        return;
    }
    std::string line;
    while (std::getline(f, line)) {
        if (line.empty()) continue;
        if (line.back() == ';') line.pop_back();
        // Si es IngresoEquipajes (sin parámetros)
        if (line == "IngresoEquipajes") {
            Pasajero p;
            if (cola.dequeue(p)) {
                if (p.equipaje_facturado > 0) {
                    pila.push({p.numero_de_pasaporte, p.equipaje_facturado});
                }
                lista.insertarOrdenado(p);
                std::cout << "Procesado pasajero: " << p.numero_de_pasaporte << "\n";
            } else {
                std::cout << "Cola vacía al intentar IngresoEquipajes\n";
            }
        } else if (line.find("MantenimientoAviones") == 0) {
            std::stringstream ss(line);
            std::string cmd, accion, registro;
            getline(ss, cmd, ',');
            getline(ss, accion, ',');
            getline(ss, registro, ',');
            // trim registro
            size_t start = registro.find_first_not_of(" \t\r\n");
            size_t end = registro.find_last_not_of(" \t\r\n");
            if (start != std::string::npos) registro = registro.substr(start, end - start + 1);
            if (accion == "Ingreso") {
                Avion* a = disponibles.buscarPorRegistro(registro);
                if (a) {
                    Avion copia = *a;
                    copia.estado = "Mantenimiento";
                    disponibles.eliminarPorRegistro(registro);
                    mantenimiento.insertarFinal(copia);
                    std::cout << "Avion " << registro << " movido a Mantenimiento\n";
                } else {
                    std::cout << "No se encontró avión disponible " << registro << "\n";
                }
            } else if (accion == "Salida") {
                Avion* a = mantenimiento.buscarPorRegistro(registro);
                if (a) {
                    Avion copia = *a;
                    copia.estado = "Disponible";
                    mantenimiento.eliminarPorRegistro(registro);
                    disponibles.insertarFinal(copia);
                    std::cout << "Avion " << registro << " movido a Disponible\n";
                } else {
                    std::cout << "No se encontró avión en mantenimiento " << registro << "\n";
                }
            } else {
                std::cout << "Acción desconocida: " << accion << "\n";
            }
        } else {
            std::cout << "Comando no reconocido: " << line << "\n";
        }
    }
    f.close();
}
