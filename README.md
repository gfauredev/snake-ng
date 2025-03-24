# Projet Snake New Generation

Jeu type Snake en C avec la bibliothèque SDL3.

Projet tutoré de développement en C à Polytech Tours.

## Conventions de code

### Nommage des symboles

| Symbole               | Convention                   |
| --------------------- | ---------------------------- |
| Variable (int…)       | `snake_case`                 |
| Constante (#DEFINE…)  | `UPPER_CASE`                 |
| Fonction (void fn()…) | `snake_case`                 |
| Types (struct, enum…) | `snake_case` suivi de `_t`   |
| Tableaux ([])         | `snake_case` suivi de `_tab` |

### Formatage du code (sauts de ligne, indentation…)

Formatage automatique avec le LSP de Clang, défini dans `.clang-format`.

### Documentation du code

Documentation de toutes les fonctions suivant la syntaxe
[Doxygen](https://www.doxygen.nl/manual), avec au moins les mentions `@brief` et
`@param`.

```c
/**
 * @brief Example function
 * @param arg An example argument
 */
void my_function(int arg);
```
