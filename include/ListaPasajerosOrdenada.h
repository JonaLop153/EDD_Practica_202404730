#ifndef LISTA_PASAJEROS_ORDENADA_H
#define LISTA_PASAJEROS_ORDENADA_H

#include "Pasajero.h"
#include <functional>
#include <string>

class ListaPasajerosOrdenada {
private:
    struct Node {
        Pasajero data;
        Node* next;
        Node* prev;
        Node(const Pasajero& p): data(p), next(nullptr), prev(nullptr) {}
    };
    Node* head;
    int sz;
public:
    ListaPasajerosOrdenada();
    ~ListaPasajerosOrdenada();

    void insertarOrdenado(const Pasajero& p); // criterio: vuelo asc, asiento asc
    Pasajero* buscarPorPasaporte(const std::string& pas);
    void recorrer(std::function<void(const Pasajero&)> f) const;
    int size() const { return sz; }

    void generarDot(const std::string& archivo, const std::string& titulo) const;
};

#endif // LISTA_PASAJEROS_ORDENADA_H
