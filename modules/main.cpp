#include <iostream>
#include "../includes/Objet.hpp"
#include "../includes/const.hpp"
#include "../includes/BinaryOperator.hpp"
#include "../includes/UnaryOperator.hpp"
#include <string>
#include <stdexcept>
#include "../includes/Variable.hpp"
#include "../includes/rationnel.hpp"

int main() {
    // Exemple d'utilisation des classes définies
    Variable<double> x("x");
    Const<double> c("c", 5.0);
    BinaryOperator<double> expr(&x, &c, BinaryOperator<double>::Operator::ADD);
    std::cout << "Expression: " << expr.view() << std::endl;
    try {
        std::cout << "Évaluation: " << expr.evaluation() << std::endl
                    << "Dérivée par rapport à x: " 
                    << expr.derivative("x")->view() << std::endl;  
    } catch (const std::runtime_error& e) {
        std::cerr << "Erreur lors de l'évaluation: " << e.what() << std::endl;
    } 

    // Exemple d'utilisation de la classe Rationnel
    Rationnel r1(3, 4); // 3/4
    Rationnel r2(2, 5); // 2/5
    Rationnel r3 = r1 + r2;
    std::cout << "Rationnel r1: " << r1 << std::endl;
    std::cout << "Rationnel r2: " << r2 << std::endl;
    std::cout << "r1 + r2 = " << r3 << std::endl;

    // Exemple d'expression rationnelle
    Variable<Rationnel> y("y");
    Const<Rationnel> d("d", Rationnel(1, 2));
    BinaryOperator<Rationnel> ratExpr(&y, &d, BinaryOperator<Rationnel>::Operator::PROD);
    std::cout << "Expression rationnelle: " << ratExpr.view() << std::endl;
    try {
        std::cout << "Évaluation rationnelle: " << ratExpr.evaluation().toString() << std::endl
                  << "Dérivée par rapport à y: " 
                  << ratExpr.derivative("y")->view() << std::endl;  
    } catch (const std::runtime_error& e) {
        std::cerr << "Erreur lors de l'évaluation rationnelle: " << e.what() << std::endl;
    }   

    // Exemple avec un double
    double c2 = 0.75;
    double c3 = 0.4;
    Const<double> cDouble1("cDouble1", c2);
    Const<double> cDouble2("cDouble2", c3);
    BinaryOperator<double> doubleExpr(&cDouble1, &cDouble2, BinaryOperator<double>::Operator::DIV);
    std::cout << "Expression double: " << doubleExpr.view() << std::endl;
    try {
        std::cout << "Évaluation double: " << doubleExpr.evaluation() << std::endl
                  << "Dérivée par rapport à cDouble1: " 
                  << doubleExpr.derivative("cDouble1")->view() << std::endl;  
    } catch (const std::runtime_error& e) {
        std::cerr << "Erreur lors de l'évaluation double: " << e.what() << std::endl;
    }   
    return 0;
}