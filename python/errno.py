f = open("errno.h", "rw") 
content = f.read()

lines = content.split("\n")

array = ""
for l in lines:
	errno = l.split("#define")[1].split("\t")[1]
	print "\"" + errno + "\","