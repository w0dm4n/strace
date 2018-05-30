execfile("prototypes.py")
execfile("syscall.py")

TYPES = {
	"unsigned int": "%d",
	"int": "%d",
	"size_t": "%ld",
	"char *": "%s",
	"loff_t": "%lld",
	"off_t": "%lld",
	"long": "%ld",
	"pid_t": "%ld",
	"id_t": "%ld",
	"umode_t": "%d"
}

def append_result(result, flag):
	if len(result) == 0:
		return flag
	return result + ", " + flag

def get_type(type_arg):
	for t in TYPES:
		if t in type_arg:
			return TYPES[t]
	return "%p"

def get_args(syscall, args):
	result = ""
	types = args[1]
	for t in types:
		try:
			type_arg = get_type(t[0])
			if type_arg != None:
				result = append_result(result, type_arg)
		except KeyError:
			print "Type not handled", t[0]
	return result

def append_syscalls_arguments(sys_args, to_add):
	return sys_args + "\n" + "\"" + to_add + "\","


syscalls_arguments = ""
i = 0
for s in SYSCALL_NAMES:
    if SYSCALL_NAMES[s] in SYSCALL_PROTOTYPES:
    	result = get_args(SYSCALL_NAMES[s], SYSCALL_PROTOTYPES[SYSCALL_NAMES[s]])
       	syscalls_arguments = append_syscalls_arguments(syscalls_arguments, result)
    else:
    	syscalls_arguments = append_syscalls_arguments(syscalls_arguments, "")
    i += 1


syscalls_arguments = syscalls_arguments + "\n NULL"
print syscalls_arguments
#print TYPE["int"]