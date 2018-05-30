execfile("prototypes.py")
execfile("syscall.py")

import subprocess


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

def get_type(type_arg):
	for t in TYPES:
		if t in type_arg:
			return TYPES[t]
	return "%p"

def get_return_value(syscall):

    result = subprocess.check_output(['man', syscall])
    split = result.split("SYNOPSIS")
    synopsis = split[1].split("DESCRIPTION")[0]

    func = synopsis.split(syscall)[0].split("\n")
    ret = func[len(func) -1].strip()
    return ret

def parse_array(syscall, rets):
    for r in rets:
        if r[0] == syscall:
            return r
    return None

rets = []

for s in SYSCALL_NAMES:
    try:
        ret = get_return_value(SYSCALL_NAMES[s])
        if len(ret) > 0 and "include" not in ret:
            rets.append([SYSCALL_NAMES[s], get_type(ret)])
    except subprocess.CalledProcessError:
        nothing_here = ""

results = ""
for s in SYSCALL_NAMES:
    res = parse_array(SYSCALL_NAMES[s], rets)
    if res != None:
        results = results + "\n" + "\"" + res[1] + "\","
    else:
        results = results + "\n" + "\"\","
        
results = results + "\nNULL"
print results
