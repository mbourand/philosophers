# --- PERFORMANCES ---
./philo_one 4 410 200 200
echo PAUSE, faites CTRL + D pour reprendre ; cat
./philo_one 5 800 200 200
echo PAUSE, faites CTRL + D pour reprendre ; cat

# --- MANGE LE BON NOMBRE DE FOIS ---
./philo_one 4 410 200 200 7 | grep '1 is eating'
echo PAUSE, faites CTRL + D pour reprendre ; cat
./philo_one 5 800 200 200 7 | grep '1 is eating'
echo PAUSE, faites CTRL + D pour reprendre ; cat
./philo_one 200 610 200 100 15 | grep '111 is eating'
echo PAUSE, faites CTRL + D pour reprendre ; cat

# --- MEURS CORRECTEMENT ---
./philo_one 4 310 200 100
echo PAUSE, faites CTRL + D pour reprendre ; cat
./philo_one 2 310 200 100
echo PAUSE, faites CTRL + D pour reprendre ; cat

# --- GRAND NOMBRE DE PHILO ---
./philo_one 200 610 200 100
echo PAUSE, faites CTRL + D pour reprendre ; cat

# --- TIMINGS ---
./philo_one 2 410 200 200
