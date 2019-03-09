all:
	make run
	make plot
	

	
run:
	gcc mutex.c -o mutex -lpthread
	gcc busy_wait.c -o busy_wait -lpthread
	gcc semaphore.c -o semaphore -lpthread
	gcc conditional_var.c -o conditional_var -lpthread
	gcc cond_barrier.c -o cond_barrier -lpthread
	./run.sh
plot:
	/report/python data_read.py<mutex.txt
	
