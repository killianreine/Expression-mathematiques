# Expression mathématiques

## Introduction au sujet

> On appelle **expression mathématiques** une combinaison de nombres, de variables, de symboles et d'opérateurs mathématiques qui représente une relation ou une valeur.

*Exemples :*

- $E_1= 3+2-sin(2x)$
- $E_2= 6x+2y-7z^2$
- $E_3= \dfrac{4x+ln(7)}{2x-7}$

L'objectif de ce projet est d'utiliser la notion d'héritage en C++ pour permettre de représenter et d'évaluer des expressions mathématiques.

## Quelques précisions

On représentera une expression mathématiques par un objet de type `Objet`, ce dernier peut représenter : 

- Une **constante** *comme PI*
- Une **variable** *Comme* $x, y, z$
- Un **opérateur** mathématiques
    - Opérateur binaire $+, -, \times, /, puiss\ldots$
    - Opérateur unaire $sin, cos, tan, inv, \ldots$

La classe `Objet` représentera en fait une interface globale qui sera implémentée par les classes `Constante`, `unaryOperator`, ...

## Arborescence du répertoire

```css
Projet/
├── Includes/
│   ├── BinaryOperator.hpp
│   ├── Const.hpp
│   ├── Objet.hpp
│   ├── Rationnel.hpp
│   ├── UnaryOperator.hpp
│   └── Variable.hpp
│
└── Modules/
    ├── main.cpp
    ├── mainArbre.cpp
    └── rationnel.cpp
```

## Expressions mathématiques typées

L'objectif est aussi de gérer et évaluer des expressions de différents types. Dans un premier temps nous nous sommes consacré à évaluer et représenter des expressions sur des types simples comme `int` et `double`. Puis ensuite, l'utilisation de la classe `Rationnel` pour représenter des nombres décimaux.

### Rationnels

#### Précisions

Un nombre rationnel est définit par son numérateur et son dénominateur et il sera représenté par : `[ NUMERATOR DIV DENOMINATOR ]` afin de différencer les rationnels et l'opérations `/`.

#### Exemple

On souhaite représenter le rationnel $\dfrac{4}{7}$

```c++
Rationnel r(4, 7);
std::cout << r << std::endl; // Affiche [ 4 DIV 7 ]
```

#### Approximation d'un réel

La classe `Rationnel` fournit aussi de nombreuses fonctionnalités comme celle de créer une approximation d'un réel. Prenons l'exemple de PI.

```c++
Rationnel r_pi;
Rationnel::approx_naive(M_PI, 100000, r_pi);
std::cout << "Approximation de PI : " << r_pi << std::endl;
// Approximation de PI : [ 312689 DIV 99532 ]
```

## Évaluation d'une expression

Le système doit aussi être capable d'évaluer **une expression à une variable**. Il doit pouvoir la représenter et l'évaluer. \
*Les expressions à plusieurs variables doivent pouvoir être représentées sans pour autant devoir être évaluer pour le moment.*

## Représentation d'une expression

Le principal but de ce projet est de pouvoir visualiser une expression sous la forme d'un arbre binaire. 

- Dans un premier temps affiché dans le terminal
- Dans un second temps (si possible) générer un code Tikz pour avoir une belle représentation.

### Quelques exemples de représentations

#### Première expression

$$
\mathcal{E}_1 = \dfrac{e^{sin(x+1.0) \times cos(y+2.0)}-log(3.0+4.0)}{(y+3.0)\times 2}
$$

```
│       ┌-- 2.000000
│   ┌-- *
│   │   │   ┌-- 3.000000
│   │   └-- +
│   │       └-- y
└-- /
    │           ┌-- 4.000000
    │       ┌-- +
    │       │   └-- 3.000000
    │   ┌-- log
    └-- -
        │               ┌-- 2.000000
        │           ┌-- + 
        │           │   └-- y
        │       ┌-- cos
        │   ┌-- *
        │   │   │       ┌-- 1.000000
        │   │   │   ┌-- +
        │   │   │   │   └-- x
        │   │   └-- sin
        └-- exp
```

#### Seconde expression

$$
\mathcal{E}_2=\dfrac{e^{sin(a+\frac{1}{2})\times cos(b+\frac{3}{4})}}{b}
$$

```
│   ┌-- b
└-- /
    │               ┌-- [ 3 DIV 4 ]
    │           ┌-- +
    │           │   └-- b
    │       ┌-- cos
    │   ┌-- *
    │   │   │       ┌-- [ 1 DIV 2 ]
    │   │   │   ┌-- +
    │   │   │   │   └-- a
    │   │   └-- sin
    └-- exp
```

#### Troisième expression

$$
\mathcal{E}_3=\dfrac{log\left(sin(x+1.0)\times cos(y-2.0)+\frac{e^{z+3.0}}{4}\right)-sin(xy+z)) \times e^{z+3.0}}{e^{log((x+2.0)\times(y+3.0)+5.0z)+6}}
$$

```
│           ┌-- 6.000000
│       ┌-- +
│       │   │           ┌-- 5.000000
│       │   │       ┌-- *
│       │   │       │   └-- z
│       │   │   ┌-- +
│       │   │   │   │       ┌-- 3.000000
│       │   │   │   │   ┌-- +
│       │   │   │   │   │   └-- y
│       │   │   │   └-- *
│       │   │   │       │   ┌-- 2.000000
│       │   │   │       └-- +
│       │   │   │           └-- x
│       │   └-- log
│   ┌-- exp
└-- /
    │               ┌-- 3.000000
    │           ┌-- +
    │           │   └-- z
    │       ┌-- exp
    │   ┌-- *
    │   │   │       ┌-- z
    │   │   │   ┌-- +
    │   │   │   │   │   ┌-- y
    │   │   │   │   └-- *
    │   │   │   │       └-- x
    │   │   └-- sin
    └-- -
        │           ┌-- 4.000000
        │       ┌-- /
        │       │   │       ┌-- 3.000000
        │       │   │   ┌-- +
        │       │   │   │   └-- z
        │       │   └-- exp
        │   ┌-- +
        │   │   │           ┌-- 2.000000
        │   │   │       ┌-- -
        │   │   │       │   └-- y
        │   │   │   ┌-- cos
        │   │   └-- *
        │   │       │       ┌-- 1.000000
        │   │       │   ┌-- +
        │   │       │   │   └-- x
        │   │       └-- sin
        └-- log
```
