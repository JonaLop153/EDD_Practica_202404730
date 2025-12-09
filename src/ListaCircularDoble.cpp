#include "../include/ListaCircularDoble.h"
#include <fstream>

ListaCircularDoble::ListaCircularDoble(): head(nullptr), sz(0) {}
ListaCircularDoble::~ListaCircularDoble() {
    if (!head) return;
    Node* cur = head->next;
    while (cur != head) {
        Node* tmp = cur;
        cur = cur->next;
        delete tmp;
    }
    delete head;
    head = nullptr;
    sz = 0;
}

void ListaCircularDoble::insertarFinal(const Avion& a) {
    Node* n = new Node(a);
    if (!head) {
        head = n;
        head->next = head->prev = head;
    } else {
        Node* tail = head->prev;
        tail->next = n;
        n->prev = tail;
        n->next = head;
        head->prev = n;
    }
    sz++;
}

bool ListaCircularDoble::eliminarPorRegistro(const std::string& reg) {
    if (!head) return false;
    Node* cur = head;
    Node* start = head;
    do {
        if (cur->data.numero_de_registro == reg) {
            if (cur->next == cur) {
                delete cur;
                head = nullptr;
            } else {
                cur->prev->next = cur->next;
                cur->next->prev = cur->prev;
                if (cur == head) head = cur->next;
                delete cur;
            }
            sz--;
            return true;
        }
        cur = cur->next;
    } while (cur != start);
    return false;
}

Avion* ListaCircularDoble::buscarPorRegistro(const std::string& reg) {
    if (!head) return nullptr;
    Node* cur = head;
    Node* start = head;
    do {
        if (cur->data.numero_de_registro == reg) return &(cur->data);
        cur = cur->next;
    } while (cur != start);
    return nullptr;
}

void ListaCircularDoble::recorrer(std::function<void(const Avion&)> f) const {
    if (!head) return;
    Node* cur = head;
    Node* start = head;
    do {
        f(cur->data);
        cur = cur->next;
    } while (cur != start);
}

void ListaCircularDoble::generarDot(const std::string& archivo, const std::string& titulo) const {
    std::ofstream ofs(archivo);
    ofs << "digraph G {\nlabel=\"" << titulo << "\"; labelloc=top; node [shape=record];\n";
    if (!head) {
        ofs << "empty [label=\"(vacío)\"];\n}\n";
        return;
    }
    Node* cur = head;
    Node* start = head;
    int idx = 0;
    do {
        ofs << "n" << idx << " [label=\"" << cur->data.numero_de_registro << "\\n" << cur->data.vuelo << "\"];\n";
        cur = cur->next;
        idx++;
    } while (cur != start);
    for (int i = 0; i < idx; ++i) {
        ofs << "n" << i << " -> n" << ((i+1)%idx) << " [dir=both];\n";
    }
    ofs << "}\n";
    ofs.close();
}
