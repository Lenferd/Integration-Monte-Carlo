import random 
size = 4
outfile = open("Input.txt", 'w')

list = []
for i in range(size):
   list2 = []
   for j in range(size):
      list2.append(random.randint(1,200))
   list.append(list2)

outfile.write("size="+ str(size) + "\n")
lines = []
for line in list:
   for num in line:
      outfile.write(str(num) + "\t")
   outfile.write("\n")
