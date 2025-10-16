# EX01 : Iter - Templates + Callbacks

## 🎓 CONCEPT THÉORIQUE : Callback et Programmation Fonctionnelle

### Qu'est-ce qu'un callback ?
**Callback** = une fonction passée en paramètre à une autre fonction

**Analogie :** Vous appelez un livreur et vous lui dites :
- "Livre ce colis à cette adresse"
- "Quand tu as fini, **appelle-moi** (callback)"

### En programmation
```cpp
void faireTravail(void (*callback)()) {
    // Faire le travail...
    callback();  // Appeler la fonction passée en paramètre
}
```

---

## 🧠 LE PROBLÈME QUE ITER RÉSOUT

### Sans iter (répétitif)
```cpp
int numbers[] = {1, 2, 3, 4, 5};

// Afficher tous les nombres
for (int i = 0; i < 5; i++)
    std::cout << numbers[i];

// Incrémenter tous les nombres
for (int i = 0; i < 5; i++)
    numbers[i]++;

// Doubler tous les nombres
for (int i = 0; i < 5; i++)
    numbers[i] *= 2;
```

**PROBLÈME :** La boucle `for` est répétée à chaque fois !

### Avec iter (abstraction)
```cpp
iter(numbers, 5, print);      // Afficher
iter(numbers, 5, increment);  // Incrémenter
iter(numbers, 5, doubler);    // Doubler
```

**La boucle est cachée dans `iter` !**

---

## 💡 POURQUOI ITER ?

### 1. Séparation des responsabilités
- **iter** : s'occupe de parcourir le tableau
- **fonction callback** : s'occupe de l'action sur chaque élément

### 2. Réutilisabilité
```cpp
void print(int x) { std::cout << x; }

iter(tableau1, 5, print);  // Affiche tableau1
iter(tableau2, 10, print); // Affiche tableau2
// Même fonction print, différents tableaux !
```

### 3. Abstraction de la boucle
**Vous ne voyez plus la boucle `for`, juste l'intention !**

```cpp
// Intention claire
iter(array, size, capitalize);  // "Capitalise tous les éléments"

// vs boucle explicite (moins claire)
for (size_t i = 0; i < size; i++)
    capitalize(array[i]);
```

---

## 📚 CE QUE CET EXERCICE ENSEIGNE

### 1️⃣ Template avec 2 paramètres de type

```cpp
template <typename T, typename F>
void iter(T* array, size_t length, F func)
```

**Deux types différents :**
- **T** : type des éléments du tableau (int, string, float...)
- **F** : type de la fonction (fonction normale, template, functor...)

### 2️⃣ Callbacks génériques

**F peut être :**
1. Un pointeur de fonction normale
   ```cpp
   void print(int x) { std::cout << x; }
   iter(arr, 5, print);
   ```

2. Une fonction template
   ```cpp
   template <typename T>
   void print(T x) { std::cout << x; }
   iter(arr, 5, print<int>);
   ```

3. Un functor (objet-fonction)
   ```cpp
   struct Printer {
       void operator()(int x) { std::cout << x; }
   };
   iter(arr, 5, Printer());
   ```

**Le template F s'adapte automatiquement !**

### 3️⃣ const vs non-const

Le sujet dit : *"The function may take its argument by const reference or non-const reference"*

**Pourquoi ?** Deux cas d'usage différents :

#### Cas 1 : Lecture seule (const)
```cpp
template <typename T>
void display(T const & element) {  // const = lecture seule
    std::cout << element;
}
```

#### Cas 2 : Modification (non-const)
```cpp
template <typename T>
void increment(T & element) {  // non-const = modification
    element++;
}
```

**Solution :** Template générique qui accepte les deux
```cpp
template <typename T, typename F>
void iter(T* array, size_t length, F func) {
    for (size_t i = 0; i < length; i++)
        func(array[i]);  // F détermine si c'est const ou pas !
}
```

---

## 🔬 COMMENT ÇA MARCHE VRAIMENT

### Exemple concret

```cpp
int numbers[] = {1, 2, 3};

template <typename T>
void print(T const & x) {
    std::cout << x << " ";
}

iter(numbers, 3, print<int>);
```

### Décomposition étape par étape

**Étape 1 :** Le compilateur voit `iter(numbers, 3, print<int>)`
- `T*` devient `int*` (type du tableau)
- `F` devient `void (*)(int const &)` (type de print)

**Étape 2 :** Le compilateur génère
```cpp
void iter(int* array, size_t length, void (*func)(int const &)) {
    for (size_t i = 0; i < length; i++)
        func(array[i]);  // Appelle print(array[i])
}
```

**Étape 3 :** Exécution
```
Itération 0: print(1) → affiche "1 "
Itération 1: print(2) → affiche "2 "
Itération 2: print(3) → affiche "3 "
```

---

## 📖 ANALOGIE : Le distributeur automatique

Imaginez `iter` comme un **distributeur qui traite chaque pièce** :

```
┌─────────────────────┐
│  ITER (distributeur)│
│                     │
│  Pour chaque pièce: │
│  func(pièce)        │
└─────────────────────┘
         ▲
         │
    [1][2][3][4][5]  ← Tableau (pièces)
         │
         ▼
    ┌─────────┐
    │  func   │ ← Callback (action sur chaque pièce)
    └─────────┘
```

**func** peut être :
- `laver(pièce)` → lave chaque pièce
- `compter(pièce)` → compte chaque pièce
- `doubler(pièce)` → double la valeur de chaque pièce

**iter ne change pas, seule l'action change !**

---

## 🎯 COMPARAISON AVEC D'AUTRES CONCEPTS

### iter = forEach de JavaScript
```javascript
// JavaScript
array.forEach(function(element) {
    console.log(element);
});
```

```cpp
// C++ avec iter
iter(array, size, print);
```

### iter = map de Python
```python
# Python
map(lambda x: x * 2, array)
```

```cpp
// C++ avec iter
template <typename T>
void doubler(T& x) { x *= 2; }
iter(array, size, doubler<int>);
```

### iter = std::for_each de C++11
```cpp
// C++11 (interdit dans le sujet)
std::for_each(begin, end, [](int x) { std::cout << x; });
```

```cpp
// C++98 (notre iter)
iter(array, size, print);
```

**Vous réinventez `std::for_each` en C++98 !**

---

## ⚡ CE QU'IL FAUT COMPRENDRE

### Template F = polymorphisme au compile-time

```cpp
template <typename T, typename F>
void iter(T* array, size_t length, F func)
```

**F n'est PAS un type fixe !** C'est résolu à la compilation.

```cpp
iter(arr, 5, print);       // F = void (*)(int)
iter(arr, 5, increment);   // F = void (*)(int&)
iter(arr, 5, Print());     // F = Print (functor)
```

Chaque appel génère **une version différente** de `iter` !

### const et non-const : Pourquoi c'est important ?

**Sécurité du typage**

```cpp
void display(int const & x) {  // Promet de ne pas modifier
    x = 10;  // ❌ ERREUR DE COMPILATION !
}

void increment(int & x) {  // Peut modifier
    x++;  // ✅ OK
}
```

Le compilateur **garantit** qu'une fonction const ne modifie pas !

---

## 🧪 EXERCICE DE COMPRÉHENSION

**Question :** Que fait ce code ?

```cpp
template <typename T>
void triple(T & x) { x *= 3; }

int numbers[] = {1, 2, 3, 4, 5};
iter(numbers, 5, triple<int>);
```

**Réponse :**
1. `iter` parcourt le tableau
2. Pour chaque élément, appelle `triple(element)`
3. `triple` multiplie par 3
4. Résultat final : `[3, 6, 9, 12, 15]`

**Question 2 :** Peut-on faire ça ?
```cpp
template <typename T>
void print(T const & x) { std::cout << x; }

int const arr[] = {1, 2, 3};
iter(arr, 3, print<int>);
```

**Réponse :** ✅ OUI !
- `arr` est const (on ne peut pas le modifier)
- `print` prend const ref (ne modifie pas)
- Parfaitement compatible !

---

## 💎 CONCEPTS AVANCÉS

### Pourquoi size_t et pas int ?

```cpp
void iter(T* array, size_t length, F func)
//                  ^^^^^^
```

**size_t** :
- Type non-signé (toujours >= 0)
- Taille dépend de l'architecture (32/64 bits)
- Standard pour les tailles de tableaux
- Évite les bugs avec les nombres négatifs

```cpp
int length = -5;  // Bug potentiel !
size_t length = 5;  // Sécurisé
```

---

## 🚀 POUR ALLER PLUS LOIN

Ce que `iter` enseigne :
1. **Callbacks** : fondamental en programmation événementielle
2. **Templates de fonctions** : polymorphisme générique
3. **Abstraction** : cacher les détails d'implémentation
4. **Programmation fonctionnelle** : fonctions en paramètres

**Prochaine étape :** Les algorithmes STL
- `std::for_each`
- `std::transform`
- `std::find_if`

**Tous basés sur ce principe !**
