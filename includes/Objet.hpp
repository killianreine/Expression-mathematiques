#pragma once
#include <string>
#include "rationnel.hpp"

// INTERFACE OBJET
template <typename T>
class Objet {
    public:
        using string = std::string;

        virtual ~Objet() = default;

        virtual string view() const = 0;
        virtual T evaluation() const = 0;
        virtual Objet<T>* derivative(const string& var) const = 0;
        virtual void printTree(std::ostream& os, std::string path = "", int spacing = 4) const = 0;
        // virtual bool compare(Objet<T>* express_) = 0; TODO
};

template <typename T>
std::ostream& operator<<(std::ostream& os, const Objet<T>& obj) {
    obj.printTree(os);
    return os;
}