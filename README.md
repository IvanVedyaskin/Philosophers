# Philosophers

In this project, I learned the basics of multithreading the process.
I learned how to create threads, got acquainted with mutexes and semaphores.

# Instructions for launching Philosophers.

There are 2 directories in this repository. The "philo" directory contains implementations using mutexes. To prepare the program for launch, you need to do: 
cd philo && make. 
After that, you need to enter the arguments:
./philosopher number_philosophists time to eat time to eat time to sleep[number_of_times_each_philosopher_must_eat]
Where 
◦ number_of_philosophers: the number of philosophers, as well as the number
of forks.
◦ time to_di (in milliseconds): If the philosopher has not started eating the time to_di.
milliseconds from the start of their last meal or the start of the simulation, they die.
◦ time_to_eat (in milliseconds): the time it takes for a philosopher to eat.
During this time, they will need to hold two forks.
◦ time_to_sleep (in milliseconds): the time that the philosopher will spend in a dream.
◦ number_of_times_each_philosopher_must_eat (optional argument): If all
philosophers ate at least number_of_times_each_philosopher_must_eat
once, the simulation stops. Unless otherwise specified, the simulation stops when
the philosopher dies.

Example./philo 4 410 200 200

The program with semaphores runs the same way, only in a different directory:
cd ./philo_bonus && make

Example./philo_bonus 4 410 200 200
