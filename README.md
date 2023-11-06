# philosopher42

Threads might run concurrently and not completely parallel
![image](https://github.com/Xiru-Wang/philosopher42/assets/79924696/04a4276a-a59f-429d-8e95-a22a4ab5cd44)

# Race Condition

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
pthread_mutex_t ledger_lock;

void *update_ledger(void *data)
{
	pthread_mutex_lock(&ledger_lock);//lock
	ledger += 1;
	pthread_mutex_unlock(&ledger_lock);//unlock
	return (NULL);
}

int main()
{
	pthread_t thread[MAX];

	int i = 0;
	pthread_mutex_init(&ledger_lock, NULL);//create lock
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
	pthread_mutex_destroy(&ledger_lock);//destroy lock
	return (0);
}
````
