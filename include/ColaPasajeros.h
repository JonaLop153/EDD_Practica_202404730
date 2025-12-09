#ifndef COLA_PASAJEROS_H
#define COLA_PASAJEROS_H

#include "Pasajero.h"
#include <functional>
#include <string>
#include <vector>

class ColaPasajeros {
private:
    struct Node {
        Pasajero data;
        Node* next;
        Node(const Pasajero& p): data(p), next(nullptr) {}
    };
    Node* front;
    Node* rear;
    int sz;
public:
    ColaPasajeros();
    ~ColaPasajeros();

    void enqueue(const Pasajero& p);
    bool dequeue(Pasajero& out);

    void recorrer(std::function<void(const Pasajero&)> f) const;
    int size() const { return sz; }
    bool isEmpty() const { return sz == 0; }

    // utilitarios para snapshot / reportes sin modificar la cola
    std::vector<Pasajero> toVector() const;
    static void generarDotDesdeVector(const std::vector<Pasajero>& v, const std::string& archivo, const std::string& titulo);

    void generarDot(const std::string& archivo, const std::string& titulo) const;
};

#endif // COLA_PASAJEROS_H
