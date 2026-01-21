#pragma once
#include <iostream>
#include <cmath>
#include <string>
#include <sstream>

class Rationnel {
private:
    int numerator_;
    int denominator_;

public: 
    // #########################################################
    // #################### Constructeur #######################
    // #########################################################
    Rationnel(int numerator = 0, int denominator = 1) {
        numerator_ = numerator;
        denominator_ = (denominator == 0 ? 1 : denominator);
    }

    Rationnel(double x){
        Rationnel r;
        approx_naive(x, 100000, r);
        numerator_ = r.num();
        denominator_ = r.den();
    }

    // #########################################################
    // #################### Getters / Setters ##################
    // #########################################################
    int num() const;       // getter pour numerator_
    int den() const;       // getter pour denominator_
    
    void setNum(int);      // setter pour numerator_
    void setDen(int);      // setter pour denominator_

    // #########################################################
    // #################### Méthodes ###########################
    // #########################################################
    void normalize();                                       // simplification du rationnel
    static void approx_naive(double, int, Rationnel&);      // approximation d'un réel en rationnel
    static Rationnel approx_naive(double, int);             // approximation d'un réel en rationnel

    // #########################################################
    // #################### Opérateur unaire ###################
    // #########################################################
    Rationnel operator-() const;
    Rationnel& operator+=(const Rationnel& rhs);

    operator double() const{
        return numerator_/denominator_;
    }

    // ----------------- Méthode toString -----------------
    std::string toString() const {
        std::ostringstream oss;
        if (den() == 1) {
            oss << num();
        } else if (num() == 0) {
            oss << 0;
        } else if (num() == den()) {
            oss << 1;
        } else {
            oss << "[ " << num() << " DIV " << den() << " ]";
        }
        return oss.str();
    }
};

// ##################################################################
// #################### Surcharge des opérateurs ####################
// ##################################################################

// Surcharge des opérateurs d'E/S
std::ostream& operator<<(std::ostream& os, const Rationnel& r);
std::istream& operator>>(std::istream& is, Rationnel& r);

// Opérateurs arithmétiques
Rationnel operator+(Rationnel, Rationnel);
Rationnel operator-(Rationnel, Rationnel);
Rationnel operator*(Rationnel, Rationnel);
Rationnel operator/(Rationnel, Rationnel);

// Opérateurs de comparaisons
bool operator<(Rationnel, Rationnel);
bool operator>(Rationnel, Rationnel);
bool operator==(Rationnel, Rationnel);
bool operator!=(Rationnel, Rationnel);
bool operator>=(Rationnel, Rationnel);
bool operator<=(Rationnel, Rationnel);

Rationnel pow(const Rationnel&, int);
