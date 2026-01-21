#include "../includes/rationnel.hpp"
#include <sstream>
#include <numeric> 
#include <cmath>

// ##################################################################
// #################### Getters et setters ##########################
// ##################################################################

int Rationnel::num() const { return numerator_; }
int Rationnel::den() const { return denominator_; }

void Rationnel::setNum(int n) { numerator_ = n; }
void Rationnel::setDen(int d) { denominator_ = (d == 0 ? 1 : d); }

// ##################################################################
// #################### Normalisation ###############################
// ##################################################################

void Rationnel::normalize() {
    int gcd_val = std::gcd(numerator_, denominator_);
    numerator_ /= gcd_val;
    denominator_ /= gcd_val;
    if (denominator_ < 0) { 
        numerator_ = -numerator_;
        denominator_ = -denominator_;
    }
}

// ##################################################################
// #################### Approximation d'un réel #####################
// ##################################################################

void Rationnel::approx_naive(double value, int epsilon, Rationnel &res) {
    // ε (epsilon) = dénominateur max (contrôle la précision)
    int a = std::floor(value);
    int p_prev = 1, q_prev = 0;
    int p = a, q = 1;

    double x = value;
    int iter = 0;
    const int MAX_ITER = 1000;

    while (std::abs(x - a) > 1e-12 && q <= epsilon && iter < MAX_ITER) {
        x = 1.0 / (x - a);
        a = std::floor(x);

        int p_new = a * p + p_prev;
        int q_new = a * q + q_prev;

        if (q_new > epsilon)
            break;

        p_prev = p;
        q_prev = q;
        p = p_new;
        q = q_new;

        iter++;
    }

    res.setNum(p);
    res.setDen(q);
    res.normalize();
}

Rationnel Rationnel::approx_naive(double value, int epsilon) {
    Rationnel res;
    approx_naive(value, epsilon, res);
    return res;
}

// ##################################################################
// #################### Surcharge des opérateurs ###################
// ##################################################################

// ----------------- Opérateurs d'E/S -------------------------------
std::ostream& operator<<(std::ostream& os, const Rationnel& r) {
    if (r.den() == 1) {
        os << r.num();
    } else if (r.num() == 0) {
        os << 0;
    } else if (r.num() == r.den()) {
        os << 1;
    } else {
        os << "[ " << r.num() << " DIV " << r.den() << " ]";
    }
    return os;
}

// ----------------- Opérateurs pow <cmath> -------------------------------
Rationnel pow(const Rationnel& r, int n) {
    if (n == 0) return Rationnel(1, 1);
    int numResult = std::pow(r.num(), std::abs(n));
    int denResult = std::pow(r.den(), std::abs(n));
    if (n < 0) std::swap(numResult, denResult);
    Rationnel res = Rationnel(numResult, denResult);
    res.normalize();
    return res;
}

std::istream& operator>>(std::istream& is, Rationnel& r) {
    std::string input;
    is >> input;

    size_t slashPos = input.find('/');
    if (slashPos != std::string::npos) {
        int num = 0, den = 1;
        std::istringstream(input.substr(0, slashPos)) >> num;
        std::istringstream(input.substr(slashPos + 1)) >> den;
        if (den == 0) den = 1;
        r.setNum(num);
        r.setDen(den);
    } else {
        int num = 0;
        std::istringstream(input) >> num;
        r.setNum(num);
        r.setDen(1);
    }

    r.normalize(); 
    return is;
}

// ----------------- Opérateurs arithmétiques -----------------------
Rationnel operator+(Rationnel r1, Rationnel r2) {
    int nv_den = r1.den() * r2.den();
    int nv_num = r1.num() * r2.den() + r2.num() * r1.den();
    Rationnel r(nv_num, nv_den);
    r.normalize();
    return r;
}

Rationnel operator-(Rationnel r1, Rationnel r2) {
    int nv_den = r1.den() * r2.den();
    int nv_num = r1.num() * r2.den() - r2.num() * r1.den();
    Rationnel r(nv_num, nv_den);
    r.normalize();
    return r;
}

Rationnel& Rationnel::operator+=(const Rationnel& r) {
    int nv_den = denominator_ * r.denominator_;
    int nv_num = numerator_ * r.denominator_ + r.numerator_ * denominator_;
    numerator_ = nv_num;
    denominator_ = nv_den;
    normalize();
    return *this;
}

// ----------------- Opérateur unaire - ----------------------------
Rationnel Rationnel::operator-() const {
    return Rationnel(-numerator_, denominator_);
}

Rationnel operator*(Rationnel r1, Rationnel r2) {
    Rationnel r(r1.num() * r2.num(), r1.den() * r2.den());
    r.normalize();
    return r;
}

Rationnel operator/(Rationnel r1, Rationnel r2) {
    Rationnel r(r1.num() * r2.den(), r1.den() * r2.num());
    r.normalize();
    return r;
}

// ----------------- Opérateurs de comparaison ---------------------
bool operator<(Rationnel a, Rationnel b) {
    return a.num() * b.den() < b.num() * a.den();
}

bool operator>(Rationnel a, Rationnel b) {
    return a.num() * b.den() > b.num() * a.den();
}

bool operator==(Rationnel a, Rationnel b) {
    a.normalize();
    b.normalize();
    return (a.num() == b.num()) && (a.den() == b.den());
}

bool operator!=(Rationnel a, Rationnel b) {
    return !(a == b);
}

bool operator>=(Rationnel a, Rationnel b) {
    return !(a < b);
}

bool operator<=(Rationnel a, Rationnel b) {
    return !(a > b);
}
