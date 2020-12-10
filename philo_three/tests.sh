# --- PERFORMANCES ---
./philo_three 4 410 200 200
echo PAUSE, faites CTRL + D pour reprendre ; cat
./philo_three 5 800 200 200
echo PAUSE, faites CTRL + D pour reprendre ; cat

# --- MANGE LE BON NOMBRE DE FOIS ---
./philo_three 4 410 200 200 7 | grep '1 is eating'
echo PAUSE, faites CTRL + D pour reprendre ; cat
./philo_three 5 800 200 200 7 | grep '1 is eating'
echo PAUSE, faites CTRL + D pour reprendre ; cat
./philo_three 200 610 200 100 15 | grep '111 is eating'
echo PAUSE, faites CTRL + D pour reprendre ; cat

# --- MEURS CORRECTEMENT ---
./philo_three 4 310 200 100
echo PAUSE, faites CTRL + D pour reprendre ; cat
./philo_three 2 310 200 100
echo PAUSE, faites CTRL + D pour reprendre ; cat
./philo_three 200 310 200 100
echo PAUSE, faites CTRL + D pour reprendre ; cat

# --- GRAND NOMBRE DE PHILO ---
./philo_three 200 610 200 100
echo PAUSE, faites CTRL + D pour reprendre ; cat

# --- TIMINGS ---
./philo_three 2 410 200 200

# --- ERREURS ---
./philo_one 1 60 60 60
echo PAUSE, faites CTRL + D pour reprendre ; cat
./philo_one 0 60 60 60
echo PAUSE, faites CTRL + D pour reprendre ; cat
./philo_one -1 60 60 60
echo PAUSE, faites CTRL + D pour reprendre ; cat
./philo_one 2 -1 60 60
echo PAUSE, faites CTRL + D pour reprendre ; cat
./philo_one 2 0 60 60
echo PAUSE, faites CTRL + D pour reprendre ; cat
./philo_one 2 60 -1 60
echo PAUSE, faites CTRL + D pour reprendre ; cat
./philo_one 2 60 0 60
echo PAUSE, faites CTRL + D pour reprendre ; cat
./philo_one 2 60 60 -1
echo PAUSE, faites CTRL + D pour reprendre ; cat
./philo_one 2 60 60 0
