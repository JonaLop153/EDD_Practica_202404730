#ifndef LISTACIRCULARDOBLE_H
#define LISTACIRCULARDOBLE_H

#include "Avion.h"
#include <iostream>
#include <fstream>
#include <string>

template<typename T>
class NodoCircular {
public:
    T dato;
    NodoCircular* siguiente;
    NodoCircular* anterior;

    NodoCircular(const T& d) : dato(d), siguiente(nullptr), anterior(nullptr) {}
};

template<typename T>
class ListaCircularDoble {
private:
    NodoCircular<T>* cabeza;
    int tamano;

public:
    ListaCircularDoble();
    ~ListaCircularDoble();
    void insertar(const T& dato);
    bool eliminar(const std::string& clave);
    void mostrar() const;
    void generarDot(const std::string& nombreArchivo) const;
    T* buscarPorRegistro(const std::string& registro) const;
    int obtenerTamano() const { return tamano; }
    bool estaVacia() const { return tamano == 0; }
};

// === IMPLEMENTACIÓN ===

template<typename T>
ListaCircularDoble<T>::ListaCircularDoble() : cabeza(nullptr), tamano(0) {}

template<typename T>
ListaCircularDoble<T>::~ListaCircularDoble() {
    if (!cabeza) return;
    NodoCircular<T>* actual = cabeza;
    do {
        NodoCircular<T>* siguiente = actual->siguiente;
        delete actual;
        actual = siguiente;
    } while (actual != cabeza);
}

template<typename T>
void ListaCircularDoble<T>::insertar(const T& dato) {
    NodoCircular<T>* nuevo = new NodoCircular<T>(dato);
    if (!cabeza) {
        cabeza = nuevo;
        nuevo->siguiente = nuevo;
        nuevo->anterior = nuevo;
    } else {
        NodoCircular<T>* ultimo = cabeza->anterior;
        nuevo->anterior = ultimo;
        nuevo->siguiente = cabeza;
        ultimo->siguiente = nuevo;
        cabeza->anterior = nuevo;
    }
    tamano++;
}

template<typename T>
bool ListaCircularDoble<T>::eliminar(const std::string& clave) {
    if (!cabeza) return false;

    // Caso: solo un nodo
    if (tamano == 1) {
        if (cabeza->dato.numero_de_registro == clave) {
            delete cabeza;
            cabeza = nullptr;
            tamano = 0;
            return true;
        }
        return false;
    }

    // Buscar el nodo a eliminar
    NodoCircular<T>* actual = cabeza;
    do {
        if (actual->dato.numero_de_registro == clave) {
            // Si es la cabeza, moverla al siguiente
            if (actual == cabeza) {
                cabeza = actual->siguiente;
            }

            // Reconectar los enlaces
            actual->anterior->siguiente = actual->siguiente;
            actual->siguiente->anterior = actual->anterior;

            // Liberar memoria
            delete actual;
            tamano--;
            return true;
        }
        actual = actual->siguiente;
    } while (actual != cabeza);

    return false;
}

template<typename T>
T* ListaCircularDoble<T>::buscarPorRegistro(const std::string& registro) const {
    if (!cabeza) return nullptr;

    NodoCircular<T>* actual = cabeza;
    do {
        if (actual->dato.numero_de_registro == registro) {
            return const_cast<T*>(&(actual->dato));
        }
        actual = actual->siguiente;
    } while (actual != cabeza);

    return nullptr;
}

template<typename T>
void ListaCircularDoble<T>::mostrar() const {
    if (!cabeza) {
        std::cout << "Lista vacía." << std::endl;
        return;
    }

    NodoCircular<T>* actual = cabeza;
    do {
        actual->dato.mostrar();
        actual = actual->siguiente;
    } while (actual != cabeza);
}

template<typename T>
void ListaCircularDoble<T>::generarDot(const std::string& nombreArchivo) const {
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
        NodoCircular<T>* actual = cabeza;
        int i = 0;
        do {
            std::string id = "n" + std::to_string(i);
            archivo << "  " << id << " [label=\"{<f0> " << actual->dato.numero_de_registro
                    << " | <f1> " << actual->dato.modelo << " | <f2> " << actual->dato.estado << "}\"];\n";
            if (i > 0) {
                archivo << "  n" << (i - 1) << ":f2 -> " << id << ":f0 [dir=forward];\n";
                archivo << "  " << id << ":f0 -> n" << (i - 1) << ":f2 [dir=back];\n";
            }
            actual = actual->siguiente;
            i++;
        } while (actual != cabeza);

        // Conectar último con primero para completar la circularidad
        if (i > 1) {
            archivo << "  n" << (i - 1) << ":f2 -> n0:f0 [dir=forward];\n";
            archivo << "  n0:f2 -> n" << (i - 1) << ":f0 [dir=back];\n";
        }
    }

    archivo << "}\n";
    archivo.close();
}

#endif