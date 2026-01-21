#pragma once
#include "Objet.hpp"
#include "const.hpp"
#include "UnaryOperator.hpp"
#include <string>
#include <iostream>
#include <cmath>

template <typename T>
class BinaryOperator : public Objet<T> {
    public:
        using string = std::string;

        enum class Operator { ADD, DIFF, PROD, DIV, PUISS };

    private:
        Objet<T>* left_;
        Objet<T>* right_;
        Operator op_;

    public:
        BinaryOperator(Objet<T>* left, Objet<T>* right, Operator op){
            left_ = left;
            right_ = right;
            op_ = op;
        }

        Objet<T>* getLeft() const {
            return left_;
        }

        Objet<T>* getRight() const {
            return right_;
        }

        Operator getOperator() const {
            return op_;
        }

        string view() const  {
            string op_str;
            switch (op_) {
                case Operator::ADD:  op_str = " + "; break;
                case Operator::DIFF: op_str = " - "; break;
                case Operator::PROD: op_str = " * "; break;
                case Operator::DIV:  op_str = " / "; break;
                case Operator::PUISS: op_str = " ^ "; break;
            }
            return "(" + left_->view() + op_str + right_->view() + ")";
        }

        T evaluation() const  {
            switch (op_) {
                case Operator::ADD:
                    return left_->evaluation() + right_->evaluation();
                case Operator::DIFF:
                    return left_->evaluation() - right_->evaluation();
                case Operator::PROD:
                    return left_->evaluation() * right_->evaluation();
                case Operator::DIV:
                    return left_->evaluation() / right_->evaluation();
                case Operator::PUISS:
                    return std::pow(left_->evaluation(), right_->evaluation());
            }
            return 0.0f;
        }

        Objet<T>* derivative(const string& var) const  {
            switch (op_) {
                case Operator::ADD:
                    return new BinaryOperator<T>(
                        left_->derivative(var),
                        right_->derivative(var),
                        Operator::ADD
                    );
                case Operator::DIFF:
                    return new BinaryOperator<T>(
                        left_->derivative(var),
                        right_->derivative(var),
                        Operator::DIFF
                    );
                case Operator::PROD:
                    return new BinaryOperator<T>(
                        new BinaryOperator<T>(left_->derivative(var), right_, Operator::PROD),
                        new BinaryOperator<T>(left_, right_->derivative(var), Operator::PROD),
                        Operator::ADD
                    );
                case Operator::DIV:
                    return new BinaryOperator<T>(
                        new BinaryOperator<T>(
                            new BinaryOperator<T>(left_->derivative(var), right_, Operator::PROD),
                            new BinaryOperator<T>(left_, right_->derivative(var), Operator::PROD),
                            Operator::DIFF
                        ),
                        new BinaryOperator<T>(right_, new Const<T>("2", 2.0), Operator::PROD),
                        Operator::DIV
                    );
                case Operator::PUISS: {
                    // f(x) = u(x) ^ v(x)
                    // f'(x) = (u^v) * [v'(ln(u)) + v * (u'/u)]

                    Objet<T>* u = left_;
                    Objet<T>* v = right_;

                    // terme1 = v' * ln(u)
                    Objet<T>* term1 = new BinaryOperator<T>(
                        v->derivative(var),
                        new UnaryOperator<T>(u, UnaryOperator<T>::Operator::LOG),
                        Operator::PROD
                    );

                    // terme2 = v * (u'/u)
                    Objet<T>* term2 = new BinaryOperator<T>(
                        v,
                        new BinaryOperator<T>(
                            u->derivative(var),
                            u,
                            Operator::DIV
                        ),
                        Operator::PROD
                    );

                    // somme = terme1 + terme2
                    Objet<T>* somme = new BinaryOperator<T>(
                        term1,
                        term2,
                        Operator::ADD
                    );

                    // résultat final : (u^v) * (terme1 + terme2)
                    return new BinaryOperator<T>(
                        new BinaryOperator<T>(u, v, Operator::PUISS),
                        somme,
                        Operator::PROD
                    );
                }
            }
            return nullptr;
        }

        void printTree(std::ostream& os, std::string path = "", int spacing = 4) const override {
            printTreeHelper(this, os);
        }
};