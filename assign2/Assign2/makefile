all:
	make clean
	make run
	
	
clean:
	rm -f *.o
	
run:
	gcc mutex.c -o mutex -lpthread
	gcc busy_wait.c -o busy_wait -lpthread
	gcc semaphore.c -o semaphore -lpthread
	gcc conditional_var.c -o conditional_var -lpthread
	gcc cond_barrier.c -o cond_barrier -lpthread
	./run.sh

	
