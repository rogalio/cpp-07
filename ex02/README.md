# EX02 : Array - Template de Classe

## 🎓 CONCEPT THÉORIQUE : Template de Classe

### Différence : Template de Fonction vs Template de Classe

#### Template de fonction (ex00, ex01)
```cpp
template <typename T>
void swap(T& a, T& b) { }  // UNE fonction générique
```

#### Template de classe (ex02)
```cpp
template <typename T>
class Array {  // TOUTE une classe générique
    T* _array;
    unsigned int _size;
};
```

**Classe template = un type de données générique complet !**

---

## 💡 POURQUOI DES CLASSES TEMPLATES ?

### Le problème : Tableaux C natifs

```cpp
int arr[5];  // Taille fixe, aucune sécurité
arr[10];     // ❌ Pas d'erreur, comportement indéfini !
```

**Problèmes :**
- Pas de vérification de bounds
- Taille fixe à la compilation
- Pas de copie profonde automatique
- Gestion mémoire manuelle

### La solution : Classe Array générique

```cpp
Array<int> arr(5);  // Taille dynamique
arr[10];            // ✅ Lance une exception !
```

**Avantages :**
- Type-safe (sécurisé)
- Vérification des limites
- Gestion mémoire automatique (RAII)
- Fonctionne avec n'importe quel type

---

## 📚 CE QUE CET EXERCICE ENSEIGNE

### 1️⃣ Templates de Classes

```cpp
template <typename T>
class Array {
    T* _array;           // Tableau de T
    unsigned int _size;  // Taille

public:
    Array(unsigned int n);
    T& operator[](unsigned int index);
};
```

**T = n'importe quel type**
- `Array<int>` → tableau d'int
- `Array<string>` → tableau de strings
- `Array<Vector3D>` → tableau de Vector3D

**Une classe, infinité de types !**

### 2️⃣ Orthodox Canonical Form (OCF)

**Les 4 piliers obligatoires :**

```cpp
template <typename T>
class Array {
public:
    Array();                           // 1. Constructeur par défaut
    Array(Array const & src);          // 2. Constructeur de copie
    Array& operator=(Array const &);   // 3. Opérateur d'affectation
    ~Array();                          // 4. Destructeur
};
```

**Pourquoi 4 ?** Règle du C++ :
> Si une classe gère des ressources (mémoire, fichiers...),
> elle DOIT implémenter ces 4 méthodes !

### 3️⃣ RAII (Resource Acquisition Is Initialization)

**Principe fondamental du C++ moderne**

```cpp
{
    Array<int> arr(100);  // Constructeur : alloue la mémoire
    arr[0] = 42;
    // Utilisation...
}  // ← Destructeur : libère AUTOMATIQUEMENT la mémoire !
```

**Pas de `delete` manuel !**

---

## 🧠 COMMENT ÇA MARCHE : Copie Profonde

### Le piège de la copie superficielle

```cpp
class ArrayNaif {
    int* _array;

public:
    ArrayNaif(int n) : _array(new int[n]) {}
    // Pas de constructeur de copie défini !
};

ArrayNaif a(5);
ArrayNaif b = a;  // Copie superficielle : même pointeur !
```

```
Mémoire :
┌────────┐
│   a    │──┐
└────────┘  │   ┌─────────────────┐
            └──→│ [1][2][3][4][5] │
┌────────┐  │   └─────────────────┘
│   b    │──┘
└────────┘

Problème : a et b pointent vers LA MÊME mémoire !
```

**Si on modifie `a[0]`, `b[0]` change aussi !**
**Si on détruit `a`, `b` pointe vers de la mémoire libérée !**

### La solution : Copie profonde

```cpp
template <typename T>
Array<T>::Array(Array const & src) {
    _size = src._size;
    _array = new T[_size];  // Nouvelle allocation

    for (unsigned int i = 0; i < _size; i++)
        _array[i] = src._array[i];  // Copie élément par élément
}
```

```
Mémoire :
┌────────┐       ┌─────────────────┐
│   a    │──────→│ [1][2][3][4][5] │
└────────┘       └─────────────────┘

┌────────┐       ┌─────────────────┐
│   b    │──────→│ [1][2][3][4][5] │ (COPIE indépendante)
└────────┘       └─────────────────┘
```

**Maintenant a et b sont INDÉPENDANTS !**

---

## 🔬 POURQUOI L'ORTHODOX CANONICAL FORM ?

### 1. Constructeur par défaut
```cpp
Array();
```

**Permet de créer un objet vide**
```cpp
Array<int> arr;  // Tableau vide (size = 0)
```

### 2. Constructeur de copie
```cpp
Array(Array const & src);
```

**Appelé automatiquement dans ces cas :**
```cpp
Array<int> a(5);
Array<int> b = a;        // Constructeur de copie
Array<int> c(a);         // Constructeur de copie
func(a);                 // Passage par valeur → copie
```

### 3. Opérateur d'affectation
```cpp
Array& operator=(Array const & rhs);
```

**Différent du constructeur de copie !**
```cpp
Array<int> a(5);
Array<int> b(10);

b = a;  // Opérateur d'affectation (b existe déjà !)
```

**Doit gérer :**
- Auto-affectation (`a = a`)
- Libérer l'ancienne mémoire de `b`
- Allouer nouvelle mémoire
- Copier les données de `a`

### 4. Destructeur
```cpp
~Array();
```

**Libère la mémoire automatiquement**
```cpp
{
    Array<int> arr(100);
    // ...
}  // ← Destructeur appelé ici automatiquement
```

**Sans destructeur → fuite mémoire !**

---

## 📖 ANALOGIE : La photocopieuse

### Copie superficielle = Post-it pointant vers le document
```
Document A ←─┐
             ├─ Post-it "Document"
Document B ←─┘
```
Si vous modifiez A, B change aussi (même document !)

### Copie profonde = Vraie photocopie
```
Document A (original)
Document B (photocopie indépendante)
```
Modifier A n'affecte pas B !

---

## 🎯 POINTS TECHNIQUES CRUCIAUX

### 1. Initialisation par défaut avec `new T()`

**Le sujet dit :** *"Try to compile `int * a = new int();` then display `*a`"*

```cpp
int* a = new int();    // ← Parenthèses vides
std::cout << *a;       // Affiche : 0

int* b = new int;      // ← Sans parenthèses
std::cout << *b;       // Affiche : valeur aléatoire !
```

**Différence :**
- `new T()` → initialisation par défaut (0 pour int)
- `new T` → pas d'initialisation (valeur indéterminée)

**Pour notre Array :**
```cpp
_array = new T[n]();  // ← () important !
// Tous les éléments sont initialisés (0, "", etc.)
```

### 2. operator[] : deux versions

```cpp
// Version non-const : permet modification
T& operator[](unsigned int index) {
    return _array[index];
}

// Version const : lecture seule
T const & operator[](unsigned int index) const {
    return _array[index];
}
```

**Pourquoi deux ?**
```cpp
Array<int> arr(5);
arr[0] = 42;           // Utilise la version non-const

Array<int> const & ref = arr;
int x = ref[0];        // Utilise la version const
```

**Le compilateur choisit automatiquement !**

### 3. Exception pour bounds checking

```cpp
T& operator[](unsigned int index) {
    if (index >= _size)
        throw OutOfBoundsException();  // Lance exception
    return _array[index];
}
```

**Pourquoi ?**
- Tableaux C natifs : pas de vérification → crash
- Notre Array : vérification → exception claire

```cpp
try {
    arr[100];  // Hors limites
} catch (std::exception const & e) {
    std::cout << e.what();  // "Error: Index out of bounds"
}
```

---

## ⚡ SCHÉMA RÉCAPITULATIF : Vie d'un Array

```
1. CRÉATION
   Array<int> arr(5);
   ↓
   Constructeur appelé
   ↓
   new int[5]() → [0][0][0][0][0]

2. UTILISATION
   arr[0] = 42;
   ↓
   operator[] vérifie bounds
   ↓
   Si OK : retourne référence
   Si KO : lance exception

3. COPIE
   Array<int> copy = arr;
   ↓
   Constructeur de copie
   ↓
   Nouvelle allocation + copie profonde

4. AFFECTATION
   Array<int> other(3);
   other = arr;
   ↓
   Opérateur =
   ↓
   1. Vérifie auto-affectation
   2. Libère ancienne mémoire
   3. Alloue nouvelle mémoire
   4. Copie données

5. DESTRUCTION
   } ← Fin de scope
   ↓
   Destructeur appelé
   ↓
   delete[] _array
   ↓
   Mémoire libérée ✓
```

---

## 💎 CONCEPTS AVANCÉS

### RAII en détail

**RAII = Resource Acquisition Is Initialization**

**Principe :** La ressource est liée à la durée de vie de l'objet

```cpp
{
    Array<int> arr(100);  // Acquisition : new[]

    // Utilisation...

}  // Libération automatique : delete[]
```

**Avantages :**
- Pas d'oubli de `delete`
- Exception-safe (même si exception, destructeur appelé)
- Code plus propre

**C'est LA philosophie du C++ moderne !**

### Pourquoi unsigned int pour size ?

```cpp
unsigned int size() const { return _size; }
```

**unsigned** = jamais négatif
- Taille de tableau ne peut pas être négative
- Évite les bugs avec -1
- Convention standard en C++

### Auto-affectation

```cpp
Array& operator=(Array const & rhs) {
    if (this == &rhs)  // Protection auto-affectation
        return *this;

    // ...
}
```

**Sans protection :**
```cpp
arr = arr;
```
1. Libère `_array` (qui est `arr._array`)
2. Essaie de copier depuis `arr._array` (déjà libéré !)
3. **CRASH ou corruption mémoire !**

---

## 🚀 COMPARAISON AVEC std::vector

Votre `Array<T>` est une version simplifiée de `std::vector<T>` !

| Feature | Array<T> | std::vector<T> |
|---------|----------|----------------|
| Taille dynamique | ✅ | ✅ |
| Bounds checking | ✅ (avec []) | ✅ (avec .at()) |
| Copie profonde | ✅ | ✅ |
| RAII | ✅ | ✅ |
| Resize dynamique | ❌ | ✅ |
| push_back | ❌ | ✅ |

**Vous venez de comprendre comment vector fonctionne !**

---

## 🎓 EXERCICE DE COMPRÉHENSION

**Question 1 :** Que se passe-t-il ?
```cpp
Array<int> arr(5);
arr[0] = 1;
Array<int> copy = arr;
copy[0] = 999;

std::cout << arr[0];  // ???
```

**Réponse :** Affiche `1`
- Copie profonde = deux tableaux indépendants
- Modifier `copy` n'affecte pas `arr`

**Question 2 :** Combien d'allocations mémoire ?
```cpp
Array<int> a(5);
Array<int> b = a;
Array<int> c(10);
c = a;
```

**Réponse :** 4 allocations
1. `a(5)` : new
2. `b = a` : new (copie)
3. `c(10)` : new
4. `c = a` : new (réallocation)

Plus 4 libérations (delete) dans les destructeurs !

---

## 🌟 CE QU'IL FAUT RETENIR

| Concept | Signification |
|---------|---------------|
| **Template de classe** | Type de données générique complet |
| **OCF** | 4 méthodes obligatoires pour gérer ressources |
| **Copie profonde** | Duplication complète, pas de partage |
| **RAII** | Ressource liée à la durée de vie de l'objet |
| **Exception** | Gestion d'erreur propre et sécurisée |
| **const correctness** | Distinction lecture/écriture au niveau type |

---

## 🔥 POUR ALLER PLUS LOIN

Cet exercice est la **base pour comprendre** :
- `std::vector`
- `std::array`
- `std::unique_ptr`
- Smart pointers en général
- Tous les containers STL

**Maîtriser Array<T> = comprendre 80% de la STL !**

Next level :
- Move semantics (C++11)
- Perfect forwarding
- Custom allocators
