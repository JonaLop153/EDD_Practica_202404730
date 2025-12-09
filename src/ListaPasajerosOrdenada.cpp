#include "../include/ListaPasajerosOrdenada.h"
#include <fstream>

ListaPasajerosOrdenada::ListaPasajerosOrdenada(): head(nullptr), sz(0) {}
ListaPasajerosOrdenada::~ListaPasajerosOrdenada() {
    Node* cur = head;
    while (cur) {
        Node* tmp = cur;
        cur = cur->next;
        delete tmp;
    }
    head = nullptr;
    sz = 0;
}

void ListaPasajerosOrdenada::insertarOrdenado(const Pasajero& p) {
    Node* n = new Node(p);
    if (!head) {
        head = n;
        sz++;
        return;
    }
    Node* cur = head;
    while (cur) {
        if (p.vuelo < cur->data.vuelo || (p.vuelo == cur->data.vuelo && p.asiento < cur->data.asiento)) {
            n->next = cur;
            n->prev = cur->prev;
            cur->prev = n;
            if (n->prev) n->prev->next = n;
            else head = n;
            sz++;
            return;
        }
        if (!cur->next) break;
        cur = cur->next;
    }
    cur->next = n;
    n->prev = cur;
    sz++;
}

Pasajero* ListaPasajerosOrdenada::buscarPorPasaporte(const std::string& pas) {
    Node* cur = head;
    while (cur) {
        if (cur->data.numero_de_pasaporte == pas) return &(cur->data);
        cur = cur->next;
    }
    return nullptr;
}

void ListaPasajerosOrdenada::recorrer(std::function<void(const Pasajero&)> f) const {
    Node* cur = head;
    while (cur) {
        f(cur->data);
        cur = cur->next;
    }
}

void ListaPasajerosOrdenada::generarDot(const std::string& archivo, const std::string& titulo) const {
    std::ofstream f(archivo);
    f << "digraph G {\nlabel=\"" << titulo << "\"; labelloc=top; node [shape=record];\n";
    Node* cur = head;
    int idx = 0;
    if (!cur) {
        f << "empty[label=\"Lista vacía\"];\n}\n";
        return;
    }
    while (cur) {
        f << "n" << idx << "[label=\"" << cur->data.numero_de_pasaporte << "\\n" << cur->data.nombre << "\\n" << cur->data.vuelo << "-" << cur->data.asiento << "\"];\n";
        if (cur->next) f << "n" << idx << " -> n" << (idx+1) << " [dir=both];\n";
        cur = cur->next;
        idx++;
    }
    f << "}\n";
    f.close();
}
