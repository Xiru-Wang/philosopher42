#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <stdint.h>
#include <stdlib.h>

#define MAX 100

//share resource
u_int64_t ledger = 0;
pthread_mutex_t ledger_lock;

void *update_ledger(void *data)
{
	pthread_mutex_lock(&ledger_lock);
	ledger += 1;
	pthread_mutex_unlock(&ledger_lock);
	return (NULL);
}

int main()
{
	pthread_t thread[MAX];

	int i = 0;
	pthread_mutex_init(&ledger_lock, NULL);
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
	pthread_mutex_destroy(&ledger_lock);
	return (0);
}

// void	*making_coffee(void *data)
// {
// 	printf("making coffee now...\n");
// 	sleep(2);
// 	printf("coffee is ready\n");
// 	return (NULL);
// }

// int main(void)
// {
// 	pthread_t id1;//pthread_create后会保存这个thread的ID
// 	pthread_t id2;

// 	pthread_create(&id1, NULL, making_coffee, NULL);//注意这里是pointer
// 	pthread_create(&id2, NULL, making_coffee, NULL);
// 	//到这里，两个进程are running
// 	//我们需要等，所以这时候需要join等待thread结束
// 	//main thread will wait termination of the "child" process
// 	pthread_join(id1, NULL);//like wait()
// 	pthread_join(id2, NULL);//注意这里是pthread_t
// 	printf("%lu\n", sizeof(id1));//usigned long类型打印pthread_t//结果：8
// 	return (0);
// }
