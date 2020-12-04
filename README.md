# Philosophers
**Ce programme est une simulation de philosophes multithreadée :**

## Règles

- Les philosophes doivent rester en vie le plus longtemps possible.
- Les philosophes sont assis autour d'une table et doivent utiliser **deux fourchettes** pour manger dans l'assiette située au centre de la table.
- Il y a **autant de fourchettes que de philosophes** sur la table.
- Si un philosophe ne mange pas après un certain temps, il meurt.
- Après avoir **mangé**, un philosophe **dort**.
- Après avoir dormi, un philosophe **pense**, c'est *uniquement dans cet état* qu'il peut prendre les fourchettes.
- Si un philosophe meurt, la simulation **s'arrête**.
- Si l'option *max_eat* est activée, et que tous les philosophes ont mangé au moins *max_eat* fois, la simulation s'arrête.

## Installation / Utilisation
1. Clonez le repo : ``git clone https://github.com/mbourand/philosophers``
2. Allez dans le philosopher qui vous intéresse : ``cd "philo_one" / "philo_two" / "philo_three"``
3. Compilez le programme : ``make``
4. Lancez le programme : ``./philo_(one/two/three) <nb philo> <temps avant mort> <temps manger> <temps dormir> [max de fois manger]``, les temps sont en ms

Exemple de lancement du programme ``./philo_one 4 410 200 200``

## Spécificités
### Philo One
- Les fourchettes sont situées à droite et à gauche de chaque philosophe, un philosophe n'a donc accès qu'à deux fourchettes.
- Chaque philosophe est représenté par un thread.

### Philo Two
- Les fourchettes sont situées au centre de la table, les philosophes ont donc accès à toutes les fourchettes.
- Chaque philosophe est représenté par un thread.

### Philo Three
- Les fourchettes sont situées au centre de la table, les philosophes ont donc accès à toutes les fourchettes.
- Chaque philosophe est représenté par un fork.
