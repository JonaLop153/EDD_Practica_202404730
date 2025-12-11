#ifndef COLA_H
#define COLA_H

#include "Pasajero.h"
#include <iostream>

template<typename T>
class NodoCola {
public:
    T dato;
    NodoCola* siguiente;

    NodoCola(const T& d) : dato(d), siguiente(nullptr) {}
};

template<typename T>
class Cola {
private:
    NodoCola<T>* frente;
    NodoCola<T>* final;
    int tamano;

public:
    Cola();
    ~Cola();
    void encolar(const T& dato);
    T desencolar();
    bool estaVacia() const;
    void mostrar() const;
    void generarDot(const std::string& nombreArchivo) const;
    int obtenerTamano() const { return tamano; }
};

template<typename T>
Cola<T>::Cola() : frente(nullptr), final(nullptr), tamano(0) {}

template<typename T>
Cola<T>::~Cola() {
    while (!estaVacia()) {
        desencolar();
    }
}

template<typename T>
void Cola<T>::encolar(const T& dato) {
    NodoCola<T>* nuevo = new NodoCola<T>(dato);
    if (estaVacia()) {
        frente = nuevo;
        final = nuevo;
    } else {
        final->siguiente = nuevo;
        final = nuevo;
    }
    tamano++;
}

template<typename T>
T Cola<T>::desencolar() {
    if (estaVacia()) throw std::runtime_error("Cola vacía");
    NodoCola<T>* temp = frente;
    T dato = temp->dato;
    frente = frente->siguiente;
    if (!frente) final = nullptr;
    delete temp;
    tamano--;
    return dato;
}

template<typename T>
bool Cola<T>::estaVacia() const {
    return frente == nullptr;
}

template<typename T>
void Cola<T>::mostrar() const {
    if (estaVacia()) {
        std::cout << "Cola vacía." << std::endl;
        return;
    }

    NodoCola<T>* actual = frente;
    while (actual) {
        actual->dato.mostrar();
        actual = actual->siguiente;
    }
}

template<typename T>
void Cola<T>::generarDot(const std::string& nombreArchivo) const {
    std::ofstream archivo(nombreArchivo);
    if (!archivo.is_open()) {
        std::cerr << "No se pudo abrir el archivo: " << nombreArchivo << std::endl;
        return;
    }

    archivo << "digraph G {\n";
    archivo << "  rankdir=LR;\n";
    archivo << "  node [shape=record];\n";

    if (estaVacia()) {
        archivo << "  \"Cola Vacía\";\n";
    } else {
        NodoCola<T>* actual = frente;
        int i = 0;
        while (actual) {
            std::string id = "n" + std::to_string(i);
            archivo << "  " << id << " [label=\"{<f0> " << actual->dato.nombre
                    << " | <f1> " << actual->dato.vuelo << " | <f2> " << actual->dato.equipaje_facturado << "}\"];\n";
            if (i > 0) {
                archivo << "  n" << (i-1) << ":f2 -> " << id << ":f0 [dir=forward];\n";
            }
            actual = actual->siguiente;
            i++;
        }
    }

    archivo << "}\n";
    archivo.close();
}

#endif