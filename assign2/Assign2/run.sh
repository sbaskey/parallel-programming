#!/bin/bash
#execution may takes hours.to execute partially comment some portion
#busy_wait will take very long time so reduce the thread size for quick run
iter_values=(100 100 100000)
num_thread=(2 4 6 8)


echo  "mutex.txt">report/mutex.txt
echo  "semaphore.txt">report/semaphore.txt
echo  "conditional_var.txt">report/conditional_var.txt
echo  "cond_barrier.txt">report/cond_barrier.txt
echo  "busy_wait.txt">report/busy_wait.txt

echo  "iters,nothrd,val,time">>report/semaphore.txt
echo  "iters,nothrd,val,time">>report/mutex.txt
echo  "iters,nothrd,val,time">>report/conditional_var.txt
echo  "iters,nothrd,val,time">>report/busy_wait.txt
echo  "iters,nothrd,val,time">>report/cond_barrier.txt

for i in ${iter_values[*]}
do
	for n in ${num_thread[*]}
	do
	a=0
	while [ $a -lt 5 ]
	do 
		./mutex ${i} ${n}>>report/mutex.txt
		./busy_wait ${i} ${n}>>report/busy_wait.txt
		./semaphore ${i} ${n}>>report/semaphore.txt
		./conditional_var ${i} ${n}>>report/conditional_var.txt
		./cond_barrier ${i} ${n}>>report/cond_barrier.txt
		a=`expr $a + 1`
	done
	done
done
cd report
python python_plot.py<mutex.txt
python python_plot.py<semaphore.txt
python python_plot.py<conditional_var.txt
python python_plot.py<cond_barrier.txt
python python_plot.py<busy_wait.txt




			
		
	
