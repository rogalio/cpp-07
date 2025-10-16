# EX00 : Templates de Fonctions - Les Bases

## 🎓 CONCEPT THÉORIQUE : Qu'est-ce qu'un template ?

### Le problème à résoudre
Imaginez : vous devez écrire une fonction `swap` qui échange deux valeurs.

```cpp
// Pour les int
void swap(int& a, int& b) {
    int tmp = a;
    a = b;
    b = tmp;
}

// Pour les float
void swap(float& a, float& b) {
    float tmp = a;
    a = b;
    b = tmp;
}

// Pour les string
void swap(string& a, string& b) {
    string tmp = a;
    a = b;
    b = tmp;
}
```

**LE PROBLÈME :** Le code est IDENTIQUE à chaque fois, seul le TYPE change !
- Répétition de code
- Maintenance difficile
- Une fonction par type = centaines de fonctions

### La solution : LES TEMPLATES

**Un template = un moule réutilisable**

```cpp
template <typename T>  // T = "n'importe quel type"
void swap(T& a, T& b) {
    T tmp = a;
    a = b;
    b = tmp;
}
```

✨ **Une seule fonction qui marche avec TOUS les types !**

---

## 🧠 COMMENT ça marche ?

### Étape 1 : Vous écrivez le template (le moule)
```cpp
template <typename T>
void swap(T& a, T& b) { /* ... */ }
```

### Étape 2 : Vous utilisez la fonction
```cpp
int x = 5, y = 10;
swap(x, y);  // Le compilateur voit "int"
```

### Étape 3 : Le compilateur génère automatiquement
```cpp
void swap(int& a, int& b) {  // Généré automatiquement !
    int tmp = a;
    a = b;
    b = tmp;
}
```

**C'est le compilateur qui fait le travail !**

---

## 💡 POURQUOI apprendre ça ?

### 1. Éviter la duplication de code
- **Avant :** 100 types = 100 fonctions
- **Après :** 1 template = ∞ types

### 2. Base de TOUTE la STL (Standard Template Library)
```cpp
std::vector<int>        // vector est un template !
std::map<string, int>   // map est un template !
std::sort(...)          // sort est un template !
```

### 3. Programmation générique
**Générique** = qui fonctionne pour un genre (type) général

---

## 📚 CE QUE CET EXERCICE ENSEIGNE

### 1️⃣ Syntaxe de base d'un template
```cpp
template <typename T>
//        ^^^^^^^^^ T = paramètre de type
T min(T a, T b) {
//^   ^  ^  ^
//|   |  |  └─ b est de type T
//|   |  └──── a est de type T
//|   └─────── la fonction prend des T
//└─────────── la fonction retourne un T
    return (a < b) ? a : b;
}
```

### 2️⃣ Le compilateur déduit automatiquement le type
```cpp
int x = min(5, 10);        // T = int (automatique)
float y = min(3.14, 2.71); // T = float (automatique)
```

### 3️⃣ Contraintes implicites
```cpp
template <typename T>
T min(T a, T b) {
    return (a < b) ? a : b;  // Utilise l'opérateur <
}
```

**IMPORTANT :** T DOIT avoir l'opérateur `<` défini !
- `int` ✅ a l'opérateur <
- `string` ✅ a l'opérateur <
- Une classe sans `<` ❌ ne marchera pas

---

## 🎯 LES 3 FONCTIONS DE L'EXERCICE

### swap : Comprendre les références
```cpp
template <typename T>
void swap(T& a, T& b)  // & = passage par RÉFÉRENCE
{
    T tmp = a;  // Copie temporaire
    a = b;      // a prend la valeur de b
    b = tmp;    // b prend l'ancienne valeur de a
}
```

**POURQUOI `&` ?** Pour modifier les VRAIES variables (pas des copies)

### min : Comprendre le retour par référence const
```cpp
template <typename T>
T const & min(T const & a, T const & b)
//^^^^^       ^^^^^^^^
//|           └─ const = on promet de ne pas modifier
//└─ retourne une référence (pas de copie)
{
    return (a < b) ? a : b;
}
```

**POURQUOI `const &` ?**
- Évite de copier (plus rapide pour les gros objets)
- `const` = garantit qu'on ne modifie pas

**⚠️ PIÈGE DU SUJET :** Si `a == b`, retourner `b` (le 2ème)
```cpp
return (a < b) ? a : b;  // Si a >= b, retourne b ✅
```

---

## 🔬 EXPÉRIENCE MENTALE

Imaginez que `T` est une boîte mystère :

```cpp
template <typename T>
void swap(T& a, T& b) {
    T tmp = a;  // "tmp" est une boîte du même type que "a"
    a = b;
    b = tmp;
}
```

Quand vous appelez `swap(x, y)` :
- Si x et y sont des `int` → T devient `int`
- Si x et y sont des `string` → T devient `string`
- Si x et y sont des `Vector3D` → T devient `Vector3D`

**Le template s'adapte automatiquement !**

---

## 📖 ANALOGIE DE LA VIE RÉELLE

**Template = Recette de cuisine universelle**

Recette : "Gâteau à la [SAVEUR]"
1. Prenez de la farine
2. Ajoutez de la [SAVEUR]
3. Mélangez
4. Cuisez

[SAVEUR] peut être :
- Chocolat → Gâteau au chocolat
- Vanille → Gâteau à la vanille
- Fraise → Gâteau à la fraise

**Une seule recette, plusieurs saveurs !**

De même :
- Un seul template `swap<T>`
- Plusieurs types : int, float, string...

---

## ⚡ CE QU'IL FAUT RETENIR

| Concept | Explication |
|---------|-------------|
| **Template** | Moule réutilisable pour différents types |
| **typename T** | T = variable de type (int, float, string...) |
| **Généricité** | Un code qui marche avec plusieurs types |
| **Compilation** | Le compilateur génère le code pour chaque type utilisé |
| **STL** | Toute la bibliothèque standard utilise des templates |

---

## 🎓 EXERCICE DE COMPRÉHENSION

**Question :** Combien de fonctions le compilateur génère-t-il ?

```cpp
template <typename T>
void print(T x) { std::cout << x; }

int main() {
    print(42);
    print(3.14);
    print("hello");
    print(42);  // Déjà utilisé !
}
```

**Réponse :** 3 fonctions
- `print<int>` pour 42
- `print<double>` pour 3.14
- `print<const char*>` pour "hello"

Le 4ème appel réutilise `print<int>` déjà générée !

---

## 🚀 POUR ALLER PLUS LOIN

Cet exercice est la **PORTE D'ENTRÉE** vers :
- Les templates de classes (ex02)
- La STL complète (vector, map, set...)
- La métaprogrammation template
- Les concepts C++20

**Maîtriser les templates = débloquer tout le C++ moderne !**
