# Expressions Mathématiques

> Un système élégant de représentation et d'évaluation d'expressions mathématiques en C++ utilisant l'héritage et les arbres binaires

<div align="center">

[![C++](https://img.shields.io/badge/C++-17-00599C?style=for-the-badge&logo=c%2B%2B&logoColor=white)](https://isocpp.org/)
[![License](https://img.shields.io/badge/License-MIT-green.svg?style=for-the-badge)](LICENSE)
[![Build](https://img.shields.io/badge/Build-Passing-success?style=for-the-badge)](.)

</div>

---

## Vue d'ensemble

Ce projet implémente un **système de manipulation d'expressions mathématiques** permettant de représenter, évaluer et visualiser des formules complexes sous forme d'arbres binaires. Il exploite la puissance de la programmation orientée objet en C++ pour créer une architecture extensible et élégante.

### Fonctionnalités clés

- **Support multi-types** : `int`, `double`, et nombres rationnels
- **Visualisation d'arbres** : Représentation graphique ASCII des expressions
- **Évaluation dynamique** : Calcul d'expressions à une variable
- **Architecture OOP** : Héritage et polymorphisme pour une extensibilité maximale
- **Opérateurs riches** : Binaires (`+`, `-`, `×`, `/`, `^`) et unaires (`sin`, `cos`, `log`, `exp`)

---

## Exemples d'expressions

### Expression simple
```cpp
E₁ = 3 + 2 - sin(2x)
```

### Expression rationnelle
```cpp
E₂ = 6x + 2y - 7z²
```

### Expression complexe
```cpp
E₃ = (4x + ln(7)) / (2x - 7)
```

---

## Architecture

Le projet utilise une hiérarchie de classes basée sur une interface `Objet` :

```
Objet (interface)
├── Constante
├── Variable
├── UnaryOperator
│   ├── Sin
│   ├── Cos
│   ├── Log
│   └── Exp
└── BinaryOperator
    ├── Addition
    ├── Soustraction
    ├── Multiplication
    └── Division
```

### Structure du projet

```
Projet/
├── Includes/
│   ├── Objet.hpp           # Interface de base
│   ├── Const.hpp           # Constantes mathématiques
│   ├── Variable.hpp        # Variables symboliques
│   ├── UnaryOperator.hpp   # Opérateurs unaires
│   ├── BinaryOperator.hpp  # Opérateurs binaires
│   └── Rationnel.hpp       # Nombres rationnels
│
└── Modules/
    ├── main.cpp            # Point d'entrée principal
    ├── mainArbre.cpp       # Tests de visualisation
    └── rationnel.cpp       # Implémentation des rationnels
```

---

## Les Nombres Rationnels

Le projet inclut une classe `Rationnel` puissante pour manipuler des fractions exactes.

### Notation
Un rationnel est affiché comme : `[ NUMERATEUR DIV DENOMINATEUR ]`

### Utilisation

```cpp
// Création d'un rationnel 4/7
Rationnel r(4, 7);
std::cout << r << std::endl;
// Affiche: [ 4 DIV 7 ]
```

### Approximation de nombres réels

```cpp
// Approximation de π
Rationnel r_pi;
Rationnel::approx_naive(M_PI, 100000, r_pi);
std::cout << "π ≈ " << r_pi << std::endl;
// Affiche: π ≈ [ 312689 DIV 99532 ]
```

---

## Visualisation en arbre

Le cœur du projet : transformer des expressions mathématiques en arbres binaires magnifiques !

### Exemple 1 : Expression avec exponentielles

**Expression mathématique :**
```
        e^(sin(x+1)·cos(y+2)) - log(3+4)
E₁ = ──────────────────────────────────────
                (y+3)·2
```

**Arbre binaire :**
```
│       ┌── 2.000000
│   ┌── *
│   │   │   ┌── 3.000000
│   │   └── +
│   │       └── y
└── /
    │           ┌── 4.000000
    │       ┌── +
    │       │   └── 3.000000
    │   ┌── log
    └── -
        │               ┌── 2.000000
        │           ┌── + 
        │           │   └── y
        │       ┌── cos
        │   ┌── *
        │   │   │       ┌── 1.000000
        │   │   │   ┌── +
        │   │   │   │   └── x
        │   │   └── sin
        └── exp
```

### Exemple 2 : Expression avec rationnels

**Expression mathématique :**
```
        e^(sin(a+1/2)·cos(b+3/4))
E₂ = ─────────────────────────────
                  b
```

**Arbre binaire :**
```
│   ┌── b
└── /
    │               ┌── [ 3 DIV 4 ]
    │           ┌── +
    │           │   └── b
    │       ┌── cos
    │   ┌── *
    │   │   │       ┌── [ 1 DIV 2 ]
    │   │   │   ┌── +
    │   │   │   │   └── a
    │   │   └── sin
    └── exp
```

### Exemple 3 : Expression ultra-complexe

**Expression mathématique :**
```
        [log(sin(x+1)·cos(y-2) + e^(z+3)/4) - sin(xy+z)]·e^(z+3)
E₃ = ────────────────────────────────────────────────────────────────
                    e^(log((x+2)·(y+3)+5z)+6)
```

**Arbre binaire :**
```
│           ┌── 6.000000
│       ┌── +
│       │   │           ┌── 5.000000
│       │   │       ┌── *
│       │   │       │   └── z
│       │   │   ┌── +
│       │   │   │   │       ┌── 3.000000
│       │   │   │   │   ┌── +
│       │   │   │   │   │   └── y
│       │   │   │   └── *
│       │   │   │       │   ┌── 2.000000
│       │   │   │       └── +
│       │   │   │           └── x
│       │   └── log
│   ┌── exp
└── /
    │               ┌── 3.000000
    │           ┌── +
    │           │   └── z
    │       ┌── exp
    │   ┌── *
    │   │   │       ┌── z
    │   │   │   ┌── +
    │   │   │   │   │   ┌── y
    │   │   │   │   └── *
    │   │   │   │       └── x
    │   │   └── sin
    └── -
        │           ┌── 4.000000
        │       ┌── /
        │       │   │       ┌── 3.000000
        │       │   │   ┌── +
        │       │   │   │   └── z
        │       │   └── exp
        │   ┌── +
        │   │   │           ┌── 2.000000
        │   │   │       ┌── -
        │   │   │       │   └── y
        │   │   │   ┌── cos
        │   │   └── *
        │   │       │       ┌── 1.000000
        │   │       │   ┌── +
        │   │       │   │   └── x
        │   │       └── sin
        └── log
```

---

## Concepts mis en œuvre

### Programmation Orientée Objet
- **Héritage** : Hiérarchie de classes avec interface commune
- **Polymorphisme** : Évaluation et affichage via méthodes virtuelles
- **Encapsulation** : Gestion interne des opérandes et opérateurs

### Structures de données
- **Arbres binaires** : Représentation naturelle des expressions
- **Récursivité** : Parcours et évaluation des arbres

### Types avancés
- **Génériques (Templates)** : Support de types numériques variés
- **Nombres rationnels** : Arithmétique exacte sans perte de précision

---

## Objectifs pédagogiques

Ce projet illustre :

✅ L'utilisation de l'**héritage** pour créer des abstractions puissantes  
✅ La manipulation d'**arbres binaires** en programmation  
✅ L'implémentation d'un **système d'évaluation symbolique**  
✅ La conception d'**API orientées objet** élégantes  
✅ La **visualisation de structures de données** complexes  

---

## Évolutions futures

- [ ] Support des expressions à plusieurs variables
- [ ] Export TikZ pour LaTeX
- [ ] Simplification algébrique automatique
- [ ] Dérivation symbolique
- [ ] Interface graphique interactive

---

## Licence

Ce projet est sous licence MIT. Voir le fichier `LICENSE` pour plus de détails.

---

<div align="center">

**Fait avec beaucoup de ☕**

*Un projet académique explorant des mathématiques et de la programmation*

</div>
