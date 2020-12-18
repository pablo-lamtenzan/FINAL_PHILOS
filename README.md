# Dinning table philosophers

The classic deadlock managememnt problem: N philosopher are sit in a round table, there's N forks in the table and a spaguetties bowl in the middle. The philosophers (which are threads) will run a routine, this routine consist to take forks, (while having 2 forks) eat, then drop the forks, sleep, think and repeat the loop. If a philosopher die the "simulation" ends. While lanching the program the user can set: the time to die (if the philosopher doesnt eat durring more than this time it die), time to eat and time to sleep. An optional argument can be provided who defines the maximun times each philosopher can eat.

```
./philo < NB OF PHILOSOPHERS > < TIME TO DIE > < TIME TO EAT > < TIME TO SLEEP > (optinal) [MAX EATS ALLOWED]
```

42 schools made some modifications in the classic problems. This project consist to implement 3 versions fo the classical problem:
- 1) There's a fork between each philosopher and they are limited to take only "their side forks", each philosopher must be a thread and must use mutexes.
- 2) All the forks are in the midle of the table, each philosopher must be a thread and must use semaphores.
- 3) All the forks are in the midle of the table, each philosopher must be a process and must use semaphores.
