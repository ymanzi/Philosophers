# Philosophers 42Project
----------------------------------
![MyImage](https://media.giphy.com/media/eLudircQfgGEU/giphy.gif)

## Subject :warning:

[Philosopher](https://cdn.intra.42.fr/pdf/pdf/13835/en.subject.pdf)


## Introduction :ticket: 
In computer science, the dining philosophers problem is an example problem often used in concurrent algorithm design to illustrate synchronization issues and techniques for resolving them.
[More Informations](https://en.wikipedia.org/wiki/Dining_philosophers_problem)
* Philo_one: philosopher with threads and mutex
* Philo_two: philosopher with threads and semaphore
* Philo_three: philosopher with processes and semaphore


## Usage :musical_keyboard:
> **./philo_one number_philosopher time_to_die time_to_eat time_to_sleep [number_of_time_each_philosophers_must_eat]**

arguments in square brackets are not required (number_of_time_each_philosophers_must_eat)**

### Example :
> **./philo_one 4 500 200 200**

## Resources :calendar:

* [Parallel Computing](https://computing.llnl.gov/tutorials/parallel_comp/)
* [POSIX Threads](https://computing.llnl.gov/tutorials/pthreads/)
* [Working example](https://timmurphy.org/2010/05/04/pthreads-in-c-a-minimal-working-example/)
* [Semaphores in C](http://greenteapress.com/thinkos/html/thinkos012.html)
* [fork() example](https://timmurphy.org/2014/04/26/using-fork-in-cc-a-minimum-working-example/)
* [fork() multiple childs](https://stackoverflow.com/questions/876605/multiple-child-process)
* [Semaphore when programs end](https://stackoverflow.com/questions/9537068/sem-close-vs-sem-unlink-when-process-terminates)



