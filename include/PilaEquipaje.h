#ifndef PILA_EQUIPAJE_H
#define PILA_EQUIPAJE_H

#include <string>
#include <functional>

struct EquipajeInfo {
    std::string numero_de_pasaporte;
    int cantidad;

    std::string toString() const {
        return numero_de_pasaporte + " (" + std::to_string(cantidad) + ")";
    }
};

class PilaEquipaje {
private:
    struct Node {
        EquipajeInfo data;
        Node* next;
        Node(const EquipajeInfo& e): data(e), next(nullptr) {}
    };
    Node* topNode;
    int sz;
public:
    PilaEquipaje();
    ~PilaEquipaje();

    void push(const EquipajeInfo& e);
    bool pop(EquipajeInfo& out);

    void recorrer(std::function<void(const EquipajeInfo&)> f) const;
    int size() const { return sz; }
    bool isEmpty() const { return sz == 0; }

    void generarDot(const std::string& archivo, const std::string& titulo) const;
};

#endif // PILA_EQUIPAJE_H
