#ifndef LISTA_CIRCULAR_DOBLE_H
#define LISTA_CIRCULAR_DOBLE_H

#include "Avion.h"
#include <functional>
#include <string>

class ListaCircularDoble {
private:
    struct Node {
        Avion data;
        Node* next;
        Node* prev;
        Node(const Avion& a): data(a), next(nullptr), prev(nullptr) {}
    };
    Node* head;
    int sz;
public:
    ListaCircularDoble();
    ~ListaCircularDoble();

    void insertarFinal(const Avion& a);
    bool eliminarPorRegistro(const std::string& reg);
    Avion* buscarPorRegistro(const std::string& reg);
    void recorrer(std::function<void(const Avion&)> f) const;
    int size() const { return sz; }
    bool empty() const { return sz == 0; }

    void generarDot(const std::string& archivo, const std::string& titulo) const;
};

#endif // LISTA_CIRCULAR_DOBLE_H
