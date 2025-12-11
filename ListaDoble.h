#ifndef LISTADOBLE_H
#define LISTADOBLE_H

#include "Pasajero.h"
#include <iostream>

template<typename T>
class NodoDoble {
public:
    T dato;
    NodoDoble* siguiente;
    NodoDoble* anterior;

    NodoDoble(const T& d) : dato(d), siguiente(nullptr), anterior(nullptr) {}
};

template<typename T>
class ListaDoble {
private:
    NodoDoble<T>* cabeza;
    int tamano;

public:
    ListaDoble();
    ~ListaDoble();
    void insertarOrdenado(const T& dato);
    void mostrar() const;
    T* buscarPorPasaporte(const std::string& pasaporte) const;
    void generarDot(const std::string& nombreArchivo) const;
    int obtenerTamano() const { return tamano; }
    bool estaVacia() const { return tamano == 0; }
};

template<typename T>
ListaDoble<T>::ListaDoble() : cabeza(nullptr), tamano(0) {}

template<typename T>
ListaDoble<T>::~ListaDoble() {
    while (cabeza) {
        NodoDoble<T>* temp = cabeza;
        cabeza = cabeza->siguiente;
        delete temp;
    }
}

template<typename T>
void ListaDoble<T>::insertarOrdenado(const T& dato) {
    NodoDoble<T>* nuevo = new NodoDoble<T>(dato);

    if (!cabeza || dato < cabeza->dato) {
        nuevo->siguiente = cabeza;
        if (cabeza) cabeza->anterior = nuevo;
        cabeza = nuevo;
    } else {
        NodoDoble<T>* actual = cabeza;
        while (actual->siguiente && !(dato < actual->siguiente->dato)) {
            actual = actual->siguiente;
        }
        nuevo->siguiente = actual->siguiente;
        nuevo->anterior = actual;
        if (actual->siguiente) actual->siguiente->anterior = nuevo;
        actual->siguiente = nuevo;
    }
    tamano++;
}

template<typename T>
void ListaDoble<T>::mostrar() const {
    if (!cabeza) {
        std::cout << "Lista vacía." << std::endl;
        return;
    }

    NodoDoble<T>* actual = cabeza;
    while (actual) {
        actual->dato.mostrar();
        actual = actual->siguiente;
    }
}

template<typename T>
T* ListaDoble<T>::buscarPorPasaporte(const std::string& pasaporte) const {
    NodoDoble<T>* actual = cabeza;
    while (actual) {
        if (actual->dato.numero_de_pasaporte == pasaporte) {
            return &(actual->dato);
        }
        actual = actual->siguiente;
    }
    return nullptr;
}

template<typename T>
void ListaDoble<T>::generarDot(const std::string& nombreArchivo) const {
    std::ofstream archivo(nombreArchivo);
    if (!archivo.is_open()) {
        std::cerr << "No se pudo abrir el archivo: " << nombreArchivo << std::endl;
        return;
    }

    archivo << "digraph G {\n";
    archivo << "  node [shape=record];\n";

    if (!cabeza) {
        archivo << "  \"Lista Vacía\";\n";
    } else {
        NodoDoble<T>* actual = cabeza;
        int i = 0;
        while (actual) {
            std::string id = "n" + std::to_string(i);
            archivo << "  " << id << " [label=\"{<f0> " << actual->dato.nombre
                    << " | <f1> " << actual->dato.numero_de_pasaporte << " | <f2> " << actual->dato.vuelo << " | <f3> " << actual->dato.asiento << "}\"];\n";
            if (i > 0) {
                archivo << "  n" << (i-1) << ":f3 -> " << id << ":f0 [dir=forward];\n";
                archivo << "  " << id << ":f0 -> n" << (i-1) << ":f3 [dir=back];\n";
            }
            actual = actual->siguiente;
            i++;
        }
    }

    archivo << "}\n";
    archivo.close();
}

#endif