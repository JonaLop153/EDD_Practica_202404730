#ifndef PILA_H
#define PILA_H

#include <iostream>

template<typename T>
class NodoPila {
public:
    T dato;
    NodoPila* siguiente;

    NodoPila(const T& d) : dato(d), siguiente(nullptr) {}
};

template<typename T>
class Pila {
private:
    NodoPila<T>* cima;
    int tamano;

public:
    Pila();
    ~Pila();
    void apilar(const T& dato);
    T desapilar();
    bool estaVacia() const;
    void mostrar() const;
    void generarDot(const std::string& nombreArchivo) const;
    int obtenerTamano() const { return tamano; }
};

template<typename T>
Pila<T>::Pila() : cima(nullptr), tamano(0) {}

template<typename T>
Pila<T>::~Pila() {
    while (!estaVacia()) {
        desapilar();
    }
}

template<typename T>
void Pila<T>::apilar(const T& dato) {
    NodoPila<T>* nuevo = new NodoPila<T>(dato);
    nuevo->siguiente = cima;
    cima = nuevo;
    tamano++;
}

template<typename T>
T Pila<T>::desapilar() {
    if (estaVacia()) throw std::runtime_error("Pila vacía");
    NodoPila<T>* temp = cima;
    T dato = temp->dato;
    cima = cima->siguiente;
    delete temp;
    tamano--;
    return dato;
}

template<typename T>
bool Pila<T>::estaVacia() const {
    return cima == nullptr;
}

template<typename T>
void Pila<T>::mostrar() const {
    if (estaVacia()) {
        std::cout << "Pila vacía." << std::endl;
        return;
    }

    NodoPila<T>* actual = cima;
    while (actual) {
        std::cout << "Equipaje: " << actual->dato << std::endl;
        actual = actual->siguiente;
    }
}

template<typename T>
void Pila<T>::generarDot(const std::string& nombreArchivo) const {
    std::ofstream archivo(nombreArchivo);
    if (!archivo.is_open()) {
        std::cerr << "No se pudo abrir el archivo: " << nombreArchivo << std::endl;
        return;
    }

    archivo << "digraph G {\n";
    archivo << "  rankdir=TB;\n";
    archivo << "  node [shape=box];\n";

    if (estaVacia()) {
        archivo << "  \"Pila Vacía\";\n";
    } else {
        NodoPila<T>* actual = cima;
        int i = 0;
        while (actual) {
            std::string id = "n" + std::to_string(i);
            archivo << "  " << id << " [label=\"" << actual->dato << "\"];\n";
            if (i > 0) {
                archivo << "  n" << (i-1) << " -> " << id << " [dir=forward];\n";
            }
            actual = actual->siguiente;
            i++;
        }
    }

    archivo << "}\n";
    archivo.close();
}

#endif