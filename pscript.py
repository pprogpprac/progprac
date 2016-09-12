from difflib import Differ

with open('lol.txt') as f1, open('lol1.txt') as f2:
    differ = Differ()

    for line in differ.compare(f1.readlines(), f2.readlines()):
        if line.startswith(""):
            print(line[2:])
	

txt1 = open('/home/naveen/lol.txt')
txt2 = open('/home/naveen/lol1.txt')

t1 = txt1.read()
t2 = txt2.read()

print "Following are the differences between the content of the files:"
print "file1 = ",txt1, "and","file2 = ",txt2
print "************** diff statistics (START) ***************"
print "Content length of file1 = ",len(t1)
print "Content length of file2 = ",len(t2)

if len(t1) != len(t2):
    print "file1 content length != file2 content length."
else:
    print "file1 content length == file2 content length."

if len(t1) > len(t2):
    length = len(t1)
else:
    length = len(t2)

pos = ""
for i in range(0, length-1):
    if t1[i] != t2[i]:
        pos = pos+","+str(i)

mystr = ""
for j in range(0, len(pos)-1):
    if pos[j] == ",":
        k = j+1
	while pos[k] != ",":
	    print "k=", k
	    if k == len(pos)-1:
		break
	    print "mystr = ",mystr
	    mystr = mystr+pos[k:]
	    k += 1

print mystr
print "************** diff statistics (END) ***************"
