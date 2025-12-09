#include "../include/ColaPasajeros.h"
#include <fstream>

ColaPasajeros::ColaPasajeros(): front(nullptr), rear(nullptr), sz(0) {}
ColaPasajeros::~ColaPasajeros() {
    while (front) {
        Node* tmp = front;
        front = front->next;
        delete tmp;
    }
    rear = nullptr;
    sz = 0;
}

void ColaPasajeros::enqueue(const Pasajero& p) {
    Node* n = new Node(p);
    if (!rear) {
        front = rear = n;
    } else {
        rear->next = n;
        rear = n;
    }
    sz++;
}

bool ColaPasajeros::dequeue(Pasajero& out) {
    if (!front) return false;
    Node* tmp = front;
    out = front->data;
    front = front->next;
    if (!front) rear = nullptr;
    delete tmp;
    sz--;
    return true;
}

void ColaPasajeros::recorrer(std::function<void(const Pasajero&)> f) const {
    Node* cur = front;
    while (cur) {
        f(cur->data);
        cur = cur->next;
    }
}

std::vector<Pasajero> ColaPasajeros::toVector() const {
    std::vector<Pasajero> res;
    Node* cur = front;
    while (cur) {
        res.push_back(cur->data);
        cur = cur->next;
    }
    return res;
}

void ColaPasajeros::generarDotDesdeVector(const std::vector<Pasajero>& v, const std::string& archivo, const std::string& titulo) {
    std::ofstream f(archivo);
    f << "digraph G {\nlabel=\"" << titulo << "\"; labelloc=top; node [shape=record];\n";
    if (v.empty()) {
        f << "empty[label=\"Cola vacía\"];\n}\n";
        return;
    }
    for (size_t i = 0; i < v.size(); ++i) {
        f << "n" << i << " [label=\"" << v[i].numero_de_pasaporte << "\\n" << v[i].nombre << "\"];\n";
        if (i + 1 < v.size()) f << "n" << i << " -> n" << (i+1) << ";\n";
    }
    f << "}\n";
    f.close();
}

void ColaPasajeros::generarDot(const std::string& archivo, const std::string& titulo) const {
    auto v = toVector();
    generarDotDesdeVector(v, archivo, titulo);
}
