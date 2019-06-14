import random
import string

#make array of file names
fileNames = ['file1', 'file2', 'file3']

#returns a string of 10 random, lowercase letters
def randomString():
	#start with a random lower case letter
   	r = random.choice(string.ascii_lowercase)

	#loop to add 9 more letters to string
    	for i in range(10):
        	r += (random.choice(string.ascii_lowercase))
    	return r

#loop 3 times to write each file
for i in range(3):
	#open file to write into
    	w = open(fileNames[i],'w+')
	#write the 10 random lowercase letters into the file
    	w.write(randomString())
	#close file
    	w.close()

#loop 3 times to print each file
for i in range(3):
	#open file to read
    	r = open(fileNames[i],'r+')
	#print the whole file
    	print r.read()
    	#close file
	r.close()

#get two random numbers between 1 and 42 inclusive
m = random.randint(1,42)
n = random.randint(1,42)

#print m and n
print(m)
print(n)

#print the product of m and n
print(m * n)
