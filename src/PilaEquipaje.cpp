#include "../include/PilaEquipaje.h"
#include <fstream>

PilaEquipaje::PilaEquipaje(): topNode(nullptr), sz(0) {}
PilaEquipaje::~PilaEquipaje() {
    while (topNode) {
        Node* tmp = topNode;
        topNode = topNode->next;
        delete tmp;
    }
    sz = 0;
}

void PilaEquipaje::push(const EquipajeInfo& e) {
    Node* n = new Node(e);
    n->next = topNode;
    topNode = n;
    sz++;
}

bool PilaEquipaje::pop(EquipajeInfo& out) {
    if (!topNode) return false;
    out = topNode->data;
    Node* tmp = topNode;
    topNode = topNode->next;
    delete tmp;
    sz--;
    return true;
}

void PilaEquipaje::recorrer(std::function<void(const EquipajeInfo&)> f) const {
    Node* cur = topNode;
    while (cur) {
        f(cur->data);
        cur = cur->next;
    }
}

void PilaEquipaje::generarDot(const std::string& archivo, const std::string& titulo) const {
    std::ofstream f(archivo);
    f << "digraph G {\nlabel=\"" << titulo << "\"; labelloc=top; node [shape=record];\n";
    if (!topNode) {
        f << "empty[label=\"Pila vacía\"];\n}\n";
        return;
    }
    Node* cur = topNode;
    int idx = 0;
    while (cur) {
        f << "n" << idx << " [label=\"" << cur->data.numero_de_pasaporte << "\\n" << cur->data.cantidad << "\"];\n";
        if (cur->next) f << "n" << idx << " -> n" << (idx+1) << ";\n";
        cur = cur->next;
        idx++;
    }
    f << "}\n";
    f.close();
}
