---
lang: fr
---

# Projet Snake New Generation

Jeu type Snake en C avec la bibliothèque SDL3.

Projet tutoré de développement en C à Polytech Tours.

## Outils

| Fonction                                | Outil                                     |
| --------------------------------------- | ----------------------------------------- |
| Compilateur C                           | [Clang](https://clang.llvm.org)           |
| Assistance langage C                    | [clangd](https://clangd.llvm.org) (LSP)   |
| Formateur de code                       | [clangd](https://clangd.llvm.org) (LSP)   |
| Débugueur C                             | [lldb](https://lldb.llvm.org)             |
| Système de build                        | [CMake](https://cmake.org) (utilise Make) |
| Versionnage et collaboration            | [Git](https://git-scm.com) avec GitHub    |
| Gestion de dépendances et environnement | [Nix](https://nixos.org)                  |

### Bibliothèques

- SDL3 pour la gestion des fenêtres, les graphismes, l’affichage

<!-- - SDL3-ttf pour supporter l’écriture dans les fenêtres SDL3 -->

## Conventions de code

### Organisation

| Fichier                 | Contenu                                              |
| ----------------------- | ---------------------------------------------------- |
| `main.c`                | Initialisation, boucle principale, fin et nettoyages |
| `param.h`               | Paramètres globaux (macros)                          |
| `state.h`               | Structure contenant l’état global du jeu             |
| `render.c` + `render.h` | Affichage des éléments et déroulement du jeu         |
| `snake.c` + `snake.h`   | Déplacements, évolution et gestion du serpent        |
| `fruit.c` + `fruit.h`   | Création et gestion des fruits                       |

### Nommage des symboles

| Symbole                                     | Convention                   |
| ------------------------------------------- | ---------------------------- |
| Variable (`uint32_t`)                       | `snake_case` (`my_var = …`)  |
| Tableau (`example_tab [] = …`)              | `snake_case` suivi de `_tab` |
| Pointeur (`* example_ptr = …`)              | `snake_case` suivi de `_ptr` |
| Macro (constante) (`#DEFINE`)               | `UPPER_CASE` (`MY_CONST …`)  |
| Fonction (`void my_func(uint32_t arg) {…}`) | `snake_case`                 |
| Types (`typedef` `struct`/`enum` `{…} …`)   | `snake_case` suivi de `_t`   |

### Formatage du code (sauts de ligne, indentation…)

Formatage automatique avec le « language server » inclus dans Clang. Style de
code défini dans le fichier `.clang-format`.

```yml
BasedOnStyle: Microsoft
IndentWidth: 4
UseTab: Never
ColumnLimit: 80
.
.
.
```

### Documentation du code

Documentation de toutes les fonctions en anglais, suivant la syntaxe
[Doxygen](https://www.doxygen.nl/manual), comportant au moins les mentions
`@brief` et `@param`.

```c
/**
 * @brief Do nothing but being an example function.
 * @param arg1 An example argument
 * @param arg2 A second example argument
 */
void my_func(uint32_t arg1, uint16_t arg2);
```

### Autre

Utilisation des entiers de taille définie `uint8_t`, `uint16_t`, `uint32_t` et
`uint64_t` de la bibliothèque `<stdint.h>` au lieu des `char`, `short`, `int` et
`long` dépendants de la plateforme.

Norme utilisée du langage C la plus récente,
[C23](https://en.wikipedia.org/wiki/C23_(C_standard_revision)).
