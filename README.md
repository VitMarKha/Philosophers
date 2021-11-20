# Philosophers

## Description

Implementation of the problem about 5 philosophers, using multithreading and multiprocessing. At the expense of mutex and semaphore.

The compilation was performed as follows: ``gcc -Wall -Wextra -Werror``.

All files pass to ``Norminette``.

No memory leaks.

## Requirements

We will write 3 different programs, but they will have the same basic rules:

* A number of philosophers are sitting at a round table doing one of three things: eating, thinking or sleeping.
* While eating, they are not thinking or sleeping, while sleeping, they are not eating or thinking and of course, while thinking, they are not eating or sleeping.
* The philosophers sit at a circular table with a large bowl of spaghetti in the center.
* There are some forks on the table.
* As spaghetti is difficult to serve and eat with a single fork, it is assumed that a philosopher must eat with two forks, one for each hand.
* The philosophers must never be starving.
* Every philosopher needs to eat.
* Philosophers don’t speak with each other.
* Philosophers don’t know when another philosopher is about to die.
* Each time a philosopher has finished eating, he will drop his forks and start sleeping.
* When a philosopher is done sleeping, he will start thinking.
* The simulation stops when a philosopher dies.
* Each program should have the same options: ``count_philo`` ``time_to_die`` ``time_to_eat`` ``time_to_sleep`` ``[must_eat]``. 
  * ``count_philo``: is the number of philosophers and also the number of forks.
  * ``time_to_die``: is in milliseconds, if a philosopher doesn’t start eating ``time_to_die`` milliseconds after starting his last meal or the beginning of the simulation, it dies.
  * ``time_to_eat``: is in milliseconds and is the time it takes for a philosopher to eat. During that time he will need to keep the two forks.
  * ``time_to_sleep``: is in milliseconds and is the time the philosopher will spend sleeping.
  * ``must_eat``: argument is optional, if all philosophers eat at least ``must_eat`` the simulation will stop. If not specified, the simulation will stop only at the death of a philosopher.
* Each philosopher should be given a number from 1 to ``count_philo``.
* Philosopher number 1 is next to philosopher number ``count_philo``. Any other philosopher with number N is seated between philosopher N - 1 and philosopher N + 1. 
* Any change of status of a philosopher must be written as follows (with X replaced with the philosopher number and timestamp_in_ms the current timestamp in mil- liseconds). 
  * timestamp_in_ms X has taken a fork
  * timestamp_in_ms X is eating
  * timestamp_in_ms X is sleeping
  * timestamp_in_ms X is thinking
  * timestamp_in_ms X died
* The status printed should not be scrambled or intertwined with another philosopher’s status.
* The delay of death should not exceed 10 milliseconds. 
* Philosophers should avoid to die.

**The following conditions are added for philo_one:**

* One fork between each philosopher, therefore there will be a fork at the right and at the left of each philosopher.
* To prevent philosophers from duplicating forks, we must protect the state of the fork with a mutex for each of them.
* Each philosopher should be a thread.

**The following conditions are added for philo_two:**

* All the forks are in the middle of the table.
* They have no states in memory but the number of available forks is represented by a semaphore.
* Each philosopher should be a thread.

**The following conditions are added for philo_three:**

* All the forks are in the middle of the table.
* They have no states in memory but the number of available forks is represented by a semaphore.
* Each philosopher should be a process and the main process should not be a philoso- pher.

## Usage

We go to the folder of any of the tasks, write ``make``, we can run the program.
Commands for checking the operation:
  * ``./<program_name> 5 800 200 200`` - No philosopher should die, the program runs indefinitely.
  * ``./<program_name> 5 800 200 200 7`` - None of the philosophers should die, the program should stop when all the philosophers have eaten. 
  * ``./<program_name> 4 410 200 200`` - No philosopher should die, the program runs indefinitely. 
  * ``./<program_name> 4 310 200 100`` - The philosopher must die.
  * ``./<program_name> 1 800 200 200`` - The philosopher must die. 
