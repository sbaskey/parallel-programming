
import matplotlib.pyplot as plt 
import numpy as np
file_name=raw_input()
#print(file_name)
f = open(file_name,"r")
#print(f)
f.readline()
f.readline()
num_lines = sum(1 for line in open(file_name))
print(num_lines)
time={}
time_sum=0.0
for i in range(3,num_lines):
	y=f.readline()
	a,b,c,d=y.split()
	time_sum+=float(d)
	if(i%5==0):
		time[(a,b)]=time_sum/5
		#print(t)
		time_sum=0.0

#print(time)	 
x=[]
y=[]
for key,val in time.items():
	f,g=key
	
	if(g=='2'):
		y.append(float(val))
		x.append(int(f))
		
x=sorted(x)
y=sorted(y)
#print(x)
#print(y)

plt.plot(x, y,label="thread=2")
x1=[]
y1=[]
for key,val in time.items():
	f,g=key
	if(g=='4'):
		y1.append(float(val))
		x1.append(int(f))		
x1=sorted(x1)
y1=sorted(y1)
plt.plot(x1, y1,label="thread=4")

x2=[]
y2=[]
for key,val in time.items():
	f,g=key
	if(g=='6'):
		y2.append(float(val))
		x2.append(int(f))	
x2=sorted(x2)
y2=sorted(y2)
plt.plot(x2, y2,label="thread=6")

x3=[]
y3=[]
for key,val in time.items():
	f,g=key
	if(g=='8'):
		y3.append(float(val))
		x3.append(int(f))	
x3=sorted(x3)
y3=sorted(y3)
plt.plot(x3, y3,label="thread=8")



plt.xlabel('iterator') 
plt.ylabel('time') 
plt.title(file_name) 
plt.legend() 
plt.savefig(file_name+'.png')
#plt.show() 
		
	


