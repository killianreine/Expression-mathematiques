#pragma once
#include "Objet.hpp"
#include <string>
#include <iostream>

template <typename T>
class Const : public Objet<T> {
    public:
        using string = std::string;

    private:
        string name_;
        T value_;

    public:
        Const(const string& name, T value){
            name_ = name;
            value_ = value;
        }

        string name() const { return name_; }
        T value() const { return value_; }

        void setName(const string& n) { name_ = n; }
        void setValue(T v) { value_ = v; }

        string view() const {
            return std::to_string(value_);
        }

        T evaluation() const {
            return value_;
        }

        Objet<T>* derivative(const string&) const {
            // dérivée d'une constante c est 0
            return new Const<T>("0", T(0));
        }

        void printTree(std::ostream& os, std::string path = "", int spacing = 4) const override {
            printTreeHelper(this, os);
        }
};