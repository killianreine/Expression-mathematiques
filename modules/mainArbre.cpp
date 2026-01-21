#include <iostream>
#include "../includes/Objet.hpp"
#include "../includes/const.hpp"
#include "../includes/BinaryOperator.hpp"
#include "../includes/UnaryOperator.hpp"
#include <string>
#include <stdexcept>
#include "../includes/Variable.hpp"
#include "../includes/rationnel.hpp"

template <typename T>
void printTreeHelper(const Objet<T>* node, std::ostream& os, const std::string& prefix = "", bool isLeft = true) {
    if (!node) return;

    if (auto* bin = dynamic_cast<const BinaryOperator<T>*>(node)) {
        // Sous-arbre droit
        printTreeHelper(bin->getRight(), os, prefix + (isLeft ? "│   " : "    "), false);

        // Affichage du parent
        os << prefix << (isLeft ? "└-- " : "┌-- ");
        switch (bin->getOperator()) {
            case BinaryOperator<T>::Operator::ADD:  os << "+"; break;
            case BinaryOperator<T>::Operator::DIFF: os << "-"; break;
            case BinaryOperator<T>::Operator::PROD: os << "*"; break;
            case BinaryOperator<T>::Operator::DIV:  os << "/"; break;
            case BinaryOperator<T>::Operator::PUISS:  os << "^"; break;
        }
        os << "\n";

        // Sous-arbre gauche
        printTreeHelper(bin->getLeft(), os, prefix + (isLeft ? "    " : "│   "), true);
    }
    else if (auto* un = dynamic_cast<const UnaryOperator<T>*>(node)) {
        // Sous-arbre unique
        printTreeHelper(un->getOperand(), os, prefix + (isLeft ? "│   " : "    "), false);

        // Affichage du noeud unaire
        os << prefix << (isLeft ? "└-- " : "┌-- ");
        switch (un->getOperator()) {
            case UnaryOperator<T>::Operator::SIN: os << "sin"; break;
            case UnaryOperator<T>::Operator::COS: os << "cos"; break;
            case UnaryOperator<T>::Operator::EXP: os << "exp"; break;
            case UnaryOperator<T>::Operator::LOG: os << "log"; break;
            case UnaryOperator<T>::Operator::NEG: os << "neg"; break;
        }
        os << "\n";
    }
    else { // feuille : Const ou Variable
        os << prefix << (isLeft ? "└-- " : "┌-- ");

        if (auto* c = dynamic_cast<const Const<Rationnel>*>(node)) {
            os << c->value().toString(); // getValue() renvoie le Rationnel
        } 
        else if (auto* c = dynamic_cast<const Const<T>*>(node)) {
            os << c->view(); // int, double, etc.
        } 
        else if (auto* v = dynamic_cast<const Variable<T>*>(node)) {
            os << v->view();
        }
        else {
            os << node->view();
        }

        os << "\n";
    }
}

int main() {
    Const<int> one("1", 1);
    Const<int> two("2", 2);
    Const<int> three("3", 3);
    Const<int> four("4", 4);

    // (1 + 2)
    BinaryOperator<int> somme(&one, &two, BinaryOperator<int>::Operator::ADD);
    // sin(1 + 2)
    UnaryOperator<int> sinus(&somme, UnaryOperator<int>::Operator::SIN);
    // (3 - 4)
    BinaryOperator<int> difference(&three, &four, BinaryOperator<int>::Operator::DIFF);
    // sin(1 + 2) * (3 - 4)
    BinaryOperator<int> produit(&sinus, &difference, BinaryOperator<int>::Operator::PROD);
    // Affichage de l'arbre
    //std::cout << produit;

    // CAS COMPLEXE
    // Feuilles
    Const<double> c1("1", 1.0);
    Const<double> c2("2", 2.0);
    Const<double> c3("3", 3.0);
    Const<double> c4("4", 4.0);
    Variable<double> x("x");
    Variable<double> y("y");

    // Sous-expressions complexes
    BinaryOperator<double> somme1(&x, &c1, BinaryOperator<double>::Operator::ADD);         // (x + 1)
    UnaryOperator<double> sin1(&somme1, UnaryOperator<double>::Operator::SIN);            // sin(x + 1)
    BinaryOperator<double> somme2(&y, &c2, BinaryOperator<double>::Operator::ADD);        // (y + 2)
    UnaryOperator<double> cos1(&somme2, UnaryOperator<double>::Operator::COS);            // cos(y + 2)
    BinaryOperator<double> produit1(&sin1, &cos1, BinaryOperator<double>::Operator::PROD); // sin(x+1) * cos(y+2)
    UnaryOperator<double> exp1(&produit1, UnaryOperator<double>::Operator::EXP);           // exp(sin(x+1) * cos(y+2))
    BinaryOperator<double> somme3(&c3, &c4, BinaryOperator<double>::Operator::ADD);       // (3 + 4)
    UnaryOperator<double> log1(&somme3, UnaryOperator<double>::Operator::LOG);             // log(3+4)
    BinaryOperator<double> diff1(&exp1, &log1, BinaryOperator<double>::Operator::DIFF);     // exp(...) - log(...)
    // Dénominateur complexe : (y + 3) * 2
    BinaryOperator<double> denom(&y, &c3, BinaryOperator<double>::Operator::ADD);    // (y + 3)
    BinaryOperator<double> denomComplex(&denom, &c2, BinaryOperator<double>::Operator::PROD); // (y+3)*2
    // Expression finale : (exp(...) - log(...)) / ((y+3)*2)
    BinaryOperator<double> finalExpr(&diff1, &denomComplex, BinaryOperator<double>::Operator::DIV);

    // Affichage de l'arbre
    std::cout << finalExpr << std::endl << std::endl;
    
    // EN UTILISANT LES RATIONNELS !!!
    Const<Rationnel> r1("1/2", Rationnel(1, 2));
    Const<Rationnel> r2("3/4", Rationnel(3, 4));
    Variable<Rationnel> a("a");
    Variable<Rationnel> b("b");

    BinaryOperator<Rationnel> sum_r1(&a, &r1, BinaryOperator<Rationnel>::Operator::ADD); // a + 1/2
    UnaryOperator<Rationnel> sin_r1(&sum_r1, UnaryOperator<Rationnel>::Operator::SIN);

    BinaryOperator<Rationnel> sum_r2(&b, &r2, BinaryOperator<Rationnel>::Operator::ADD); // b + 3/4
    UnaryOperator<Rationnel> cos_r1(&sum_r2, UnaryOperator<Rationnel>::Operator::COS);

    BinaryOperator<Rationnel> prod_r1(&sin_r1, &cos_r1, BinaryOperator<Rationnel>::Operator::PROD);
    UnaryOperator<Rationnel> exp_r1(&prod_r1, UnaryOperator<Rationnel>::Operator::EXP);

    BinaryOperator<Rationnel> finalExpr_r1(&exp_r1, &b, BinaryOperator<Rationnel>::Operator::DIV);

    std::cout << finalExpr_r1 << std::endl;

    // Une expression bien énorme et complexe
    // --- Feuilles ---
    Const<double> c1_("1", 1.0);
    Const<double> c2_("2", 2.0);
    Const<double> c3_("3", 3.0);
    Const<double> c4_("4", 4.0);
    Const<double> c5_("5", 5.0);
    Const<double> c6_("6", 6.0);
    Variable<double> x_("x");
    Variable<double> y_("y");
    Variable<double> z_("z");

    // --- Sous-expressions intermédiaires ---
    // (x + 1)
    BinaryOperator<double> add_x1(&x_, &c1_, BinaryOperator<double>::Operator::ADD);
    // sin(x + 1)
    UnaryOperator<double> sin_x1(&add_x1, UnaryOperator<double>::Operator::SIN);

    // (y - 2)
    BinaryOperator<double> diff_y2(&y_, &c2_, BinaryOperator<double>::Operator::DIFF);
    // cos(y - 2)
    UnaryOperator<double> cos_y2(&diff_y2, UnaryOperator<double>::Operator::COS);

    // (z + 3)
    BinaryOperator<double> add_z3(&z_, &c3_, BinaryOperator<double>::Operator::ADD);
    // exp(z + 3)
    UnaryOperator<double> exp_z3(&add_z3, UnaryOperator<double>::Operator::EXP);

    // Partie 1 : sin(x+1) * cos(y-2)
    BinaryOperator<double> prod_sin_cos(&sin_x1, &cos_y2, BinaryOperator<double>::Operator::PROD);

    // Partie 2 : exp(z+3) / 4
    BinaryOperator<double> div_exp4(&exp_z3, &c4_, BinaryOperator<double>::Operator::DIV);

    // Sous-expression combinée : (sin(x+1)*cos(y-2)) + (exp(z+3)/4)
    BinaryOperator<double> add_combined(&prod_sin_cos, &div_exp4, BinaryOperator<double>::Operator::ADD);

    // log((sin(x+1)*cos(y-2)) + (exp(z+3)/4))
    UnaryOperator<double> log_part1(&add_combined, UnaryOperator<double>::Operator::LOG);

    // (x*y)
    BinaryOperator<double> prod_xy(&x_, &y_, BinaryOperator<double>::Operator::PROD);
    // (x*y) + z
    BinaryOperator<double> add_xyz(&prod_xy, &z_, BinaryOperator<double>::Operator::ADD);
    // sin((x*y) + z)
    UnaryOperator<double> sin_xyz(&add_xyz, UnaryOperator<double>::Operator::SIN);

    // (sin((x*y)+z)) * exp(z+3)
    BinaryOperator<double> prod_sin_exp(&sin_xyz, &exp_z3, BinaryOperator<double>::Operator::PROD);

    // (log(...) - sin((x*y)+z)*exp(...))
    BinaryOperator<double> diff_num(&log_part1, &prod_sin_exp, BinaryOperator<double>::Operator::DIFF);

    // --- Partie mégacomplexe du dénominateur ---
    // ((x+2)*(y+3)) + (z*5)
    BinaryOperator<double> add_x2(&x_, &c2_, BinaryOperator<double>::Operator::ADD);
    BinaryOperator<double> add_y3(&y_, &c3_, BinaryOperator<double>::Operator::ADD);
    BinaryOperator<double> prod_xy_term(&add_x2, &add_y3, BinaryOperator<double>::Operator::PROD);
    BinaryOperator<double> prod_z5(&z_, &c5_, BinaryOperator<double>::Operator::PROD);
    BinaryOperator<double> add_inner_denom(&prod_xy_term, &prod_z5, BinaryOperator<double>::Operator::ADD);

    // log(((x+2)*(y+3)) + (z*5))
    UnaryOperator<double> log_denom(&add_inner_denom, UnaryOperator<double>::Operator::LOG);

    // exp(log(...) + 6)
    BinaryOperator<double> add_log6(&log_denom, &c6_, BinaryOperator<double>::Operator::ADD);
    UnaryOperator<double> exp_denom(&add_log6, UnaryOperator<double>::Operator::EXP);

    // --- Expression finale ---
    // ( (log(...) - sin((x*y)+z)*exp(...)) ) / exp(log(...) + 6)
    BinaryOperator<double> finalExprBig(&diff_num, &exp_denom, BinaryOperator<double>::Operator::DIV);

    // Affichage
    std::cout << finalExprBig << std::endl;

    std::cout << "==================== TESTS DES NOUVEAUX OPÉRATEURS (NEG PUISS) ====================" << std::endl;
    // Test sur l'opération inverse NEG
    Const<int> one_("1", 1);
    Const<int> two_("2", 2);
    Const<int> three_("7", 7);
    Const<int> four_("4", 4);
    
    BinaryOperator<int> firstExpress(&one_, &four_, BinaryOperator<int>::Operator::DIFF);
    BinaryOperator<int> firstExpress2(&one_, &three_, BinaryOperator<int>::Operator::PROD);
    BinaryOperator<int> secondExpress(&firstExpress, &firstExpress2, BinaryOperator<int>::Operator::PUISS);
    UnaryOperator<int> finalEE(&secondExpress, UnaryOperator<int>::Operator::NEG);

    std::cout << "\n\n" << finalEE << std::endl;
    std::cout << "Affichage de l'expression : " << finalEE.view() << std::endl;
    std::cout << "Evaluation de l'expression : " << finalEE.evaluation() << std::endl;

    return 0;
}