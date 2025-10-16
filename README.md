# CPP Module 07 : C++ Templates

## 🎯 VISION GLOBALE

Ce module est votre **introduction aux templates en C++**, le mécanisme fondamental de la **programmation générique**.

### Progression pédagogique

```
EX00: Templates de Fonctions
  ↓
  Comprendre la syntaxe de base
  Écrire du code réutilisable

EX01: Templates + Callbacks
  ↓
  Combiner templates et pointeurs de fonction
  Introduction à la programmation fonctionnelle

EX02: Templates de Classes
  ↓
  Créer des types de données génériques
  Gestion mémoire avancée (RAII)
  Orthodox Canonical Form
```

---

## 📚 QU'EST-CE QU'UN TEMPLATE ?

### Définition simple
**Template = moule réutilisable qui s'adapte à différents types**

### Analogie
Imaginez une **machine à gaufres** :
- La machine (template) est toujours la même
- La pâte (type) peut changer : chocolat, vanille, salée...
- Résultat : des gaufres de saveurs différentes !

De même :
- Le template est toujours le même
- Le type peut changer : int, string, float...
- Résultat : du code qui fonctionne avec tous les types !

---

## 🎓 LES 3 CONCEPTS FONDAMENTAUX

### 1️⃣ Généricité (Ex00)
**Écrire du code qui fonctionne avec n'importe quel type**

Sans templates :
```cpp
void swap_int(int& a, int& b) { }
void swap_float(float& a, float& b) { }
void swap_string(string& a, string& b) { }
// ... 100 fonctions différentes
```

Avec templates :
```cpp
template <typename T>
void swap(T& a, T& b) { }  // Une fonction pour tous !
```

### 2️⃣ Callbacks et Abstraction (Ex01)
**Passer des fonctions en paramètres pour réutiliser des algorithmes**

```cpp
template <typename T, typename F>
void iter(T* array, size_t size, F func) {
    for (size_t i = 0; i < size; i++)
        func(array[i]);  // Action définie par l'appelant
}
```

**L'algorithme (boucle) est séparé de l'action (fonction) !**

### 3️⃣ Types de Données Génériques (Ex02)
**Créer des structures de données qui fonctionnent avec n'importe quel type**

```cpp
template <typename T>
class Array {
    T* _data;  // Tableau de n'importe quel type
};

Array<int> numbers;      // Tableau d'int
Array<string> words;     // Tableau de strings
Array<Vector3D> points;  // Tableau de Vector3D
```

---

## 💡 POURQUOI C'EST IMPORTANT ?

### 1. Base de toute la STL (Standard Template Library)

**Tout dans la STL est basé sur les templates :**

```cpp
std::vector<T>           // Container générique
std::map<K, V>           // Dictionnaire générique
std::sort(begin, end)    // Algorithme générique
std::find_if(...)        // Recherche générique
```

**Si vous ne comprenez pas les templates, vous ne comprenez pas la STL !**

### 2. Code réutilisable et maintenable

```
Sans templates :
- 1 type = 1 fonction
- 100 types = 100 fonctions
- Bug dans une fonction = corriger 100 fois

Avec templates :
- 1 template = ∞ types
- Bug = corriger 1 fois
```

### 3. Performance

**Les templates sont résolus à la compilation :**
- Pas de coût à l'exécution (zero-cost abstraction)
- Le compilateur génère du code optimisé pour chaque type
- Aussi rapide que du code écrit à la main

---

## 🗺️ CARTE CONCEPTUELLE DU MODULE

```
                    TEMPLATES C++
                         │
         ┌───────────────┼───────────────┐
         │               │               │
    FONCTIONS        FONCTIONS       CLASSES
    (Ex00)          + CALLBACKS      (Ex02)
                      (Ex01)
         │               │               │
         │               │               │
    ┌────▼────┐     ┌────▼────┐    ┌────▼────┐
    │  swap   │     │  iter   │    │  Array  │
    │  min    │     │         │    │         │
    │  max    │     │         │    │         │
    └────┬────┘     └────┬────┘    └────┬────┘
         │               │               │
         │               │               │
    Réutiliser      Algorithmes     Structures
      code         + callbacks      de données
                                   génériques
                         │
                         ▼

                   STL COMPLÈTE

         vector, map, set, algorithm...
```

---

## 📊 COMPARAISON : Avant / Après Templates

| Aspect | Sans Templates | Avec Templates |
|--------|----------------|----------------|
| **Réutilisabilité** | Faible (1 fonction/type) | Élevée (1 template/∞ types) |
| **Maintenance** | Difficile (code dupliqué) | Facile (un seul endroit) |
| **Performance** | Bonne | Excellente (compile-time) |
| **Complexité code** | Simple mais répétitif | Plus abstrait mais élégant |
| **Typage** | Fort (type fixe) | Fort + Générique |

---

## 🎯 OBJECTIFS PÉDAGOGIQUES PAR EXERCICE

### Ex00 : Fondations
**Objectifs :**
- ✅ Comprendre la syntaxe `template <typename T>`
- ✅ Savoir que le compilateur génère du code automatiquement
- ✅ Utiliser les templates de fonctions
- ✅ Comprendre les contraintes implicites (opérateurs requis)

**Concepts clés :**
- Template de fonction
- Déduction automatique de type
- Références vs valeurs

### Ex01 : Abstraction
**Objectifs :**
- ✅ Combiner templates et callbacks
- ✅ Comprendre la programmation fonctionnelle
- ✅ Abstraire les algorithmes (séparer "comment" de "quoi")
- ✅ Gérer const et non-const

**Concepts clés :**
- Template avec plusieurs paramètres de type
- Pointeurs de fonction génériques
- const correctness

### Ex02 : Structures Complexes
**Objectifs :**
- ✅ Créer des classes templates
- ✅ Maîtriser l'Orthodox Canonical Form
- ✅ Comprendre RAII (Resource Acquisition Is Initialization)
- ✅ Implémenter copie profonde
- ✅ Gérer les exceptions

**Concepts clés :**
- Template de classe
- Gestion mémoire dynamique
- Rule of Three
- Exception handling

---

## 🧠 CONCEPTS TRANSVERSAUX

### 1. Compilation des Templates

**Important :** Les templates sont générés **à la compilation**, pas à l'exécution.

```cpp
template <typename T>
void print(T x) { std::cout << x; }

int main() {
    print(42);       // Génère print<int>
    print(3.14);     // Génère print<double>
    print("hello");  // Génère print<const char*>
}
```

Le compilateur crée **3 versions différentes** de la fonction !

### 2. Templates dans les Headers

**Règle absolue :** Les templates DOIVENT être dans les fichiers .hpp

**Pourquoi ?**
- Le compilateur a besoin du code source complet
- Pas de séparation .cpp possible (sauf export, peu utilisé)

### 3. Type Safety

Les templates sont **type-safe** (sûrs au niveau des types) :

```cpp
template <typename T>
T add(T a, T b) { return a + b; }

add(1, 2);       // ✅ OK : int + int
add(1.5, 2.5);   // ✅ OK : double + double
add(1, 2.5);     // ❌ ERREUR : types différents !
```

---

## 📖 RESSOURCES POUR APPROFONDIR

### Après CPP-07, vous serez prêt pour :

1. **CPP-08** : Conteneurs STL (vector, map, stack...)
2. **CPP-09** : Algorithmes STL (sort, find, transform...)
3. **C++11+** :
   - Variadic templates
   - Perfect forwarding
   - SFINAE
   - Concepts (C++20)

### Livres recommandés :
- "Effective C++" by Scott Meyers
- "C++ Templates: The Complete Guide" by Vandevoorde & Josuttis

---

## ⚡ RÉSUMÉ EN 30 SECONDES

**Templates = moules réutilisables pour différents types**

**3 exercices, 3 niveaux :**
1. **Ex00** : Templates de fonctions (swap, min, max)
2. **Ex01** : Templates + callbacks (iter)
3. **Ex02** : Templates de classes (Array)

**Pourquoi c'est crucial ?**
- Base de toute la STL
- Code réutilisable
- Zero-cost abstraction
- C++ moderne

**Le module 07 = Porte d'entrée du C++ générique !**

---

## 🚀 COMPILATION ET TESTS

```bash
# Ex00
cd ex00 && make && ./templates

# Ex01
cd ex01 && make && ./iter

# Ex02
cd ex02 && make && ./array
```

**Tous les exercices compilent avec :**
- `-Wall -Wextra -Werror`
- `-std=c++98`
- Tests complets avec couleurs ANSI

---

## ✅ CHECKLIST GÉNÉRALE

Avant de rendre le module :

- [ ] Les 3 exercices compilent sans warnings
- [ ] Tous les tests passent
- [ ] Pas de fuites mémoire (valgrind clean)
- [ ] Templates dans les headers (.hpp)
- [ ] Orthodox Canonical Form pour Array
- [ ] Include guards partout
- [ ] Makefiles propres (clean, fclean, re)
- [ ] Code lisible et commenté
- [ ] Comprendre TOUS les concepts !

**Bonne chance ! 🎉**
