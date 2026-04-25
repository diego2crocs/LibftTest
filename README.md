# testlibft

> **[English](#english) | [Français](#français)**

---

## English

### What is this?

**testlibft** is a personal test suite for the 42 school **libft** project.  
It runs automated tests on all 43 functions and prints a clear `✅ OK` / `❌ KO` result for each one, with an error message explaining what went wrong on failure.

It is designed to be used **alongside** your libft project — not submitted with it.

### Prerequisites

- `cc` (or `gcc`) and `make`
- Your **libft** folder must sit **next to** this repository (see structure below)

### Setup & Clone

Clone both repositories as siblings into the same parent folder:

```bash
git clone <your-libft-repo-url> libft
git clone https://github.com/diego2crocs/LibftTest testlibft
```

Expected directory layout:

```
some-folder/
├── libft/        ← your libft project (to submit)
└── testlibft/    ← this repository (do NOT submit)
    ├── main_test.c
    ├── Makefile
    └── README.md
```

> The Makefile uses `../libft` as the path to your libft — this layout is required.

### Usage

```bash
cd testlibft
make        # compiles libft, then compiles and runs the tests
make re     # full recompile + runs the tests
make clean  # removes compiled binaries
```

### Output

```
========================================
               LIBFT TEST
========================================

--- ft_isalpha ---
  ✅ OK  'a'
  ✅ OK  'Z'
  ✅ OK  '0'
  ...

--- ft_split ---
  ✅ OK  3 words
  ❌ KO  leading/trailing sep : expected ["hello", NULL]
  ...

========================================
  PASSED: 112 | FAILED: 1 | TOTAL: 113
========================================
```

Exits with code `1` if any test fails, `0` if all pass — compatible with shell scripting.

### Functions tested

| Category | Function | Tests |
|---|---|---|
| **Char checks** | `ft_isalpha` | `'a'`, `'Z'`, `'0'`, `' '`, `'\0'` |
| | `ft_isdigit` | `'5'`, `'0'`, `'9'`, `'a'`, `' '` |
| | `ft_isalnum` | `'a'`, `'5'`, `'!'` |
| | `ft_isascii` | `0`, `127`, `128`, `-1` |
| | `ft_isprint` | `' '`, `'~'`, `'\t'`, `127` |
| | `ft_toupper` | `'a'→'A'`, `'z'→'Z'`, `'A'` unchanged, `'1'` unchanged |
| | `ft_tolower` | `'A'→'a'`, `'Z'→'z'`, `'a'` unchanged, `'1'` unchanged |
| **Memory** | `ft_memset` | fills 5 bytes, zero fill, `n=0` no-op |
| | `ft_bzero` | zeros 5 bytes, leaves remainder |
| | `ft_memcpy` | basic copy, returns `dst` |
| | `ft_memmove` | forward overlap, backward overlap |
| | `ft_memchr` | found, not found, found at start, beyond `n` |
| | `ft_memcmp` | equal, less, greater, `n=0` |
| **Strings** | `ft_strlen` | `"hello"`, empty, one char |
| | `ft_strlcpy` | basic, truncated, `size=0` |
| | `ft_strlcat` | basic concat, truncated |
| | `ft_strchr` | found, not found, `'\0'` at end |
| | `ft_strrchr` | last occurrence, not found |
| | `ft_strncmp` | equal, less, greater, `n=0`, common prefix |
| | `ft_strnstr` | found, not in range, empty needle, empty haystack |
| | `ft_strdup` | content match, different pointer, empty string |
| **Conversion** | `ft_atoi` | `"42"`, `"-42"`, `"  +10"`, `"0"`, leading spaces, `INT_MAX`, `INT_MIN` |
| | `ft_itoa` | `42`, `-42`, `0`, `INT_MIN`, `INT_MAX` |
| **Allocation** | `ft_calloc` | zeroed memory, `size=0` |
| **String manip** | `ft_substr` | basic, `start > len`, truncated len |
| | `ft_strjoin` | basic, empty s1, empty s2 |
| | `ft_strtrim` | spaces, custom set, no trim, all trimmed |
| | `ft_split` | 3 words, leading/trailing sep, empty string |
| | `ft_strmapi` | `toupper` on full string, empty string |
| | `ft_striteri` | in-place `toupper` |
| **Output** | `ft_putchar_fd` | visual check on stdout |
| | `ft_putstr_fd` | visual check on stdout |
| | `ft_putendl_fd` | visual check on stdout |
| | `ft_putnbr_fd` | `-42`, `INT_MIN` — visual check on stdout |
| **Linked list** | `ft_lstnew` | content, `next=NULL` |
| | `ft_lstadd_front` | new head value |
| | `ft_lstadd_back` | last node value |
| | `ft_lstsize` | size = 3 |
| | `ft_lstlast` | last node content |
| | `ft_lstiter` | in-place increment on all nodes |
| | `ft_lstmap` | not NULL, correct size |
| | `ft_lstclear` | pointer set to NULL |
| | `ft_lstdelone` | no crash on isolated node |

---

## Français

### C'est quoi ?

**testlibft** est une suite de tests personnelle pour le projet **libft** de l'école 42.  
Elle lance des tests automatisés sur les 43 fonctions et affiche un résultat clair `✅ OK` / `❌ KO` pour chacune, avec un message d'erreur expliquant ce qui a échoué.

Conçu pour être utilisé **à côté** de ton projet libft — à ne pas rendre.

### Prérequis

- `cc` (ou `gcc`) et `make`
- Ton dossier **libft** doit être **voisin** de ce dépôt (voir la structure ci-dessous)

### Installation & Clone

Clone les deux dépôts côte à côte dans le même dossier parent :

```bash
git clone <url-de-ton-repo-libft> libft
git clone https://github.com/diego2crocs/LibftTest testlibft
```

Structure attendue :

```
dossier-parent/
├── libft/        ← ton projet libft (à rendre)
└── testlibft/    ← ce dépôt (ne pas rendre)
    ├── main_test.c
    ├── Makefile
    └── README.md
```

> Le Makefile utilise `../libft` comme chemin vers ta libft — cette structure est obligatoire.

### Utilisation

```bash
cd testlibft
make        # compile libft, puis compile et lance les tests
make re     # recompilation complète + lance les tests
make clean  # supprime les binaires compilés
```

### Résultat

```
========================================
               LIBFT TEST
========================================

--- ft_isalpha ---
  ✅ OK  'a'
  ✅ OK  'Z'
  ...

--- ft_split ---
  ✅ OK  3 words
  ❌ KO  leading/trailing sep : expected ["hello", NULL]
  ...

========================================
  PASSED: 112 | FAILED: 1 | TOTAL: 113
========================================
```

Retourne le code de sortie `1` si un test échoue, `0` si tout passe.

### Fonctions testées

| Catégorie | Fonction | Tests |
|---|---|---|
| **Vérification char** | `ft_isalpha` | `'a'`, `'Z'`, `'0'`, `' '`, `'\0'` |
| | `ft_isdigit` | `'5'`, `'0'`, `'9'`, `'a'`, `' '` |
| | `ft_isalnum` | `'a'`, `'5'`, `'!'` |
| | `ft_isascii` | `0`, `127`, `128`, `-1` |
| | `ft_isprint` | `' '`, `'~'`, `'\t'`, `127` |
| | `ft_toupper` | `'a'→'A'`, `'z'→'Z'`, `'A'` inchangé, `'1'` inchangé |
| | `ft_tolower` | `'A'→'a'`, `'Z'→'z'`, `'a'` inchangé, `'1'` inchangé |
| **Mémoire** | `ft_memset` | remplit 5 octets, remplissage zéro, `n=0` |
| | `ft_bzero` | met à zéro 5 octets, laisse le reste |
| | `ft_memcpy` | copie basique, retourne `dst` |
| | `ft_memmove` | chevauchement avant, chevauchement arrière |
| | `ft_memchr` | trouvé, non trouvé, trouvé au début, au-delà de `n` |
| | `ft_memcmp` | égal, inférieur, supérieur, `n=0` |
| **Chaînes** | `ft_strlen` | `"hello"`, vide, un caractère |
| | `ft_strlcpy` | basique, tronqué, `size=0` |
| | `ft_strlcat` | concat basique, tronquée |
| | `ft_strchr` | trouvé, non trouvé, `'\0'` en fin |
| | `ft_strrchr` | dernière occurrence, non trouvé |
| | `ft_strncmp` | égal, inférieur, supérieur, `n=0`, préfixe commun |
| | `ft_strnstr` | trouvé, hors portée, needle vide, haystack vide |
| | `ft_strdup` | contenu identique, pointeur différent, chaîne vide |
| **Conversion** | `ft_atoi` | `"42"`, `"-42"`, `"  +10"`, `"0"`, espaces, `INT_MAX`, `INT_MIN` |
| | `ft_itoa` | `42`, `-42`, `0`, `INT_MIN`, `INT_MAX` |
| **Allocation** | `ft_calloc` | mémoire mise à zéro, `size=0` |
| **Manip. chaînes** | `ft_substr` | basique, `start > len`, longueur tronquée |
| | `ft_strjoin` | basique, s1 vide, s2 vide |
| | `ft_strtrim` | espaces, set custom, rien à trimmer, tout trimmé |
| | `ft_split` | 3 mots, séparateurs en début/fin, chaîne vide |
| | `ft_strmapi` | `toupper` sur toute la chaîne, chaîne vide |
| | `ft_striteri` | `toupper` en place |
| **Sortie** | `ft_putchar_fd` | vérification visuelle sur stdout |
| | `ft_putstr_fd` | vérification visuelle sur stdout |
| | `ft_putendl_fd` | vérification visuelle sur stdout |
| | `ft_putnbr_fd` | `-42`, `INT_MIN` — vérification visuelle sur stdout |
| **Liste chaînée** | `ft_lstnew` | contenu, `next=NULL` |
| | `ft_lstadd_front` | valeur du nouveau head |
| | `ft_lstadd_back` | valeur du dernier nœud |
| | `ft_lstsize` | taille = 3 |
| | `ft_lstlast` | contenu du dernier nœud |
| | `ft_lstiter` | incrément en place sur tous les nœuds |
| | `ft_lstmap` | non NULL, taille correcte |
| | `ft_lstclear` | pointeur mis à NULL |
| | `ft_lstdelone` | pas de crash sur nœud isolé |
