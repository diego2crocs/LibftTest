# testlibft

Suite de tests personnelle pour libft. Teste les 43 fonctions avec un affichage [OK]/[KO].

## Structure

```
HomeAfter42/
  libft/       ← projet à rendre
  testlibft/   ← ce dossier, ne pas rendre
    main_test.c
    Makefile
```

## Utilisation

```bash
cd testlibft
make      # compile libft + lance les tests
make re   # recompilation complète + lance les tests
make clean
```

Le Makefile compile automatiquement `../libft` avant de compiler les tests.

## Résultat

```
  [OK] nom du test
  [KO] nom du test

  PASSED: 112 | FAILED: 0 | TOTAL: 112
```

Retourne le code de sortie `1` si un test échoue, `0` si tout passe.