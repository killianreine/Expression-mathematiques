#pragma once
#include "Objet.hpp"
#include "const.hpp"
#include <cmath>
#include <string>

template <typename T>
class BinaryOperator;

template <typename T>
class UnaryOperator : public Objet<T> {
    public:
        using string = std::string;

        enum class Operator { SIN, COS, EXP, LOG, NEG };

    private:
        Objet<T>* operand_;
        Operator op_;

    public:
        UnaryOperator(Objet<T>* operand, Operator op){
            operand_ = operand;
            op_ = op;
        }

        Objet<T>* getOperand() const { return operand_; }
        Operator getOperator() const { return op_; }

        string view() const  {
            switch (op_) {
                case Operator::SIN: return "sin(" + operand_->view() + ")";
                case Operator::COS: return "cos(" + operand_->view() + ")";
                case Operator::EXP: return "exp(" + operand_->view() + ")";
                case Operator::LOG: return "log(" + operand_->view() + ")";
                case Operator::NEG: return "-(" + operand_->view() + ")"; 
            }
            return "";
        }

        T evaluation() const  {
            T val = operand_->evaluation();
            switch (op_) {
                case Operator::SIN: return std::sin(val);
                case Operator::COS: return std::cos(val);
                case Operator::EXP: return std::exp(val);
                case Operator::LOG: return std::log(val);
                case Operator::NEG: return -val;
            }
            return 0.0f;
        }

        Objet<T>* derivative(const string& var) const  {
            switch (op_) {
                case Operator::SIN:
                    return new BinaryOperator<T>(
                        new UnaryOperator<T>(operand_, Operator::COS),
                        operand_->derivative(var),
                        BinaryOperator<T>::Operator::PROD
                    );
                case Operator::COS:
                    return new BinaryOperator<T>(
                        new Const<T>("-1", -1),
                        new BinaryOperator<T>(
                            new UnaryOperator<T>(operand_, Operator::SIN),
                            operand_->derivative(var),
                            BinaryOperator<T>::Operator::PROD
                        ),
                        BinaryOperator<T>::Operator::PROD
                    );
                case Operator::EXP:
                    return new BinaryOperator<T>(
                        new UnaryOperator<T>(operand_, Operator::EXP),
                        operand_->derivative(var),
                        BinaryOperator<T>::Operator::PROD
                    );
                case Operator::LOG:
                    return new BinaryOperator<T>(
                        new BinaryOperator<T>(
                            new Const<T>("1", 1.0),
                            operand_,
                            BinaryOperator<T>::Operator::DIV
                        ),
                        operand_->derivative(var),
                        BinaryOperator<T>::Operator::PROD
                    );
                case Operator::NEG:
                    return new UnaryOperator<T>(
                        operand_->derivative(var), Operator::NEG
                    );
            }
            return nullptr;
        }

        void printTree(std::ostream& os, std::string path = "", int spacing = 4) const override {
            printTreeHelper(this, os);
        }

};
