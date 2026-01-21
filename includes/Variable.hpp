#pragma once
#include "Objet.hpp"
#include "const.hpp"
#include <string>
#include <iostream>

template <typename T>
class Variable : public Objet<T> {
    public:
        using string = std::string;

    private:
        string name_;

    public:
        Variable(const string& name) : name_(name) {}
        string name() const { return name_; }
        void setName(const string& n) { name_ = n; }
        string view() const  {
            return name_;
        }

        T evaluation() const  {
            // La valeur d'une variable n'est pas définie !
            throw std::runtime_error("Évaluation de la bariable non définie.");
        }

        Objet<T>* derivative(const string& var) const  {
            if (var == name_) {
                return new Const<T>("1", 1.0);
            } else {
                return new Const<T>("0", 0.0);
            }
        }

        void printTree(std::ostream& os, std::string prefix = "", int spacing = 4) const override {
            // Une variable est une feuille, on affiche juste son nom
            os << prefix << "+-- " << name_ << "\n";
        }
};