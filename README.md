# testlibft

Suite de tests personnelle pour libft. Teste les 43 fonctions avec un affichage compact par fonction, vérifie les fichiers en trop, lance la norminette, et détecte les fuites mémoire avec valgrind.

## Structure

```
HomeAfter42/
  libft/       ← projet à rendre
  testlibft/   ← ce dossier, ne pas rendre
    main_test.c
    Makefile
```

Si ton dossier `libft/` est ailleurs, modifie `LIBFT_DIR` au début du Makefile.

## Utilisation

| Commande | Effet |
|---|---|
| `make` | Vérif fichiers + norminette + compilation + tests |
| `make valgrind` | Vérifie les fuites mémoire (`definitely lost`, `indirectly lost`) |
| `make clean` | Nettoie les binaires |
| `make re` | clean + all |

Le Makefile compile automatiquement `../libft` avant de compiler les tests.

## Ce que ça vérifie

- **Fichiers en trop** : signale tout fichier dans `libft/` qui n'est pas autorisé par le sujet (`a.out`, `*.o`, scripts orphelins, etc.). Les artefacts de build (`libft.a`, `.o`) sont automatiquement nettoyés avant la vérification via un `make fclean` côté libft.
- **Norminette** : lance `norminette` sur le dossier libft et n'affiche que les erreurs. Si la norminette n'est pas installée, l'étape est skippée avec un warning.
- **Compilation** : compile la libft puis le tester avec `-Wall -Wextra -Werror`. Les erreurs de compilation sont affichées proprement.
- **Tests fonctionnels** : 43 fonctions testées (partie obligatoire + bonus liste chaînée).
- **Valgrind** : optionnel via `make valgrind`. Filtre le `still reachable` (faux positifs) pour ne signaler que les vraies fuites.

## Résultat

Format compact : une ligne par fonction, détails uniquement en cas d'erreur.

```
ft_isalpha     : 1.✅ 2.✅ 3.✅ 4.✅ 5.✅
ft_isdigit     : 1.✅ 2.✅ 3.✅ 4.✅ 5.✅
ft_split       : 1.✅ 2.❌ 3.✅
     → test 2: expected ["hello", NULL]
...
PASSED: 112 | FAILED: 1 | TOTAL: 113
```

Retourne le code de sortie `1` si un test échoue, `0` si tout passe.

## Notes

- Si tu ne fais pas la partie bonus de la libft, retire les fichiers `ft_lst*_bonus.c` de la variable `ALLOWED_FILES` au début du Makefile, et commente l'appel à `test_list()` dans `main_test.c`.
- Valgrind doit être installé sur le système. Sur macOS, il faut utiliser `leaks` à la place (non géré par ce tester).