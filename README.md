# philosopher42
Brief
The Dining Philosophers problem is a classic practice exercise in computer science for understanding and dealing with concurrency issues in multi-threading environments. 

The problem illustrates synchronization issues and techniques for resolving them. It involves a certain number of philosophers seated around a circular table, and the challenge is to design a protocol that allows them to eat and think without running into deadlocks (where they are stuck waiting indefinitely) or resource starvation (where one or more philosophers are unable to access the resources they need to continue).

Each philosopher alternates between thinking and eating. To eat, a philosopher must have two forks (or resources), one from their left and one from their right, but each fork is shared with a neighbor. The problem becomes how to devise a strategy where philosophers do not deadlock (waiting indefinitely for a fork) and do not starve (being forever denied access to a fork).

# Philos = Array, Forks = Array
![14](https://github.com/Xiru-Wang/philosopher42/assets/79924696/e87ed4f1-203f-48b6-acfd-5e5771e6e107)

# Deadlock Prevention
![15](https://github.com/Xiru-Wang/philosopher42/assets/79924696/c9a2b8c4-7855-4222-98ad-adbe8f82dcc2)
![16](https://github.com/Xiru-Wang/philosopher42/assets/79924696/6941f670-88cf-4325-a8e5-6a05ed55b033)

# Thread vs Process
![17](https://github.com/Xiru-Wang/philosopher42/assets/79924696/e0209629-c52d-4b9c-9747-9a9b8449294a)

# Concurrently vs Parallel
![image](https://github.com/Xiru-Wang/philosopher42/assets/79924696/04a4276a-a59f-429d-8e95-a22a4ab5cd44)

# Race Condition & Mutex

Since threads share the same memory space within a process, they can access and modify the same variables and data structures. Without proper synchronization mechanisms, multiple threads could attempt to read and write to the same data simultaneously. This situation is known as a “race condition”, and it can lead to inconsistencies and unpredictable behaviors.

Code demonstration:
````
#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <stdint.h>
#include <stdlib.h>

#define MAX 100

//share resource
u_int64_t ledger = 0;

void *update_ledger(void *data)
{
	ledger += 1;
	return (NULL);
}

int main()
{
	pthread_t thread[MAX];

	int i = 0;
	while (i < MAX)
	{
		if (pthread_create(&thread[i], NULL, update_ledger, NULL) != 0)
			exit(1);
		i++;
	}
	i = 0;
	while (i < MAX)
	{
		if (pthread_join(thread[i], NULL) != 0)
			exit(1);
		i++;
	}
	printf("%llu\n", ledger);
	return (0);
}
````
To prevent race conditions, we can use mutexes (mutual exclusions) to ensure that only one thread can access a piece of data at a time.
````
//share resource
u_int64_t ledger = 0;
pthread_mutex_t ledger_lock;//👈

void *update_ledger(void *data)
{
	pthread_mutex_lock(&ledger_lock);//lock👈
	ledger += 1;
	pthread_mutex_unlock(&ledger_lock);//unlock👈
	return (NULL);
}

int main()
{
	pthread_t thread[MAX];

	int i = 0;
	pthread_mutex_init(&ledger_lock, NULL);//create lock👈
	while (i < MAX)
	{
		if (pthread_create(&thread[i], NULL, update_ledger, NULL) != 0)
			exit(1);
		i++;
	}
	i = 0;
	while (i < MAX)
	{
		if (pthread_join(thread[i], NULL) != 0)
			exit(1);
		i++;
	}
	printf("%llu\n", ledger);
	pthread_mutex_destroy(&ledger_lock);//destroy lock👈
	return (0);
}
````
