import urllib2
import re

url = "https://raw.githubusercontent.com/torvalds/linux/master/include/linux/syscalls.h"
source = urllib2.urlopen(url).read()

p1 = re.compile(r"^asmlinkage long sys(?:32)?_(.*?)\((.*?)\)",
                re.MULTILINE | re.DOTALL)
p2 = re.compile(r"^(.*?)([^ *]+)$")

SYSCALL_PROTOTYPES = {}

for m1 in p1.finditer(source):
    print m1.group(0)
    call_name = m1.group(1)
    args = m1.group(2)
    args = args.replace("__user", "")
    args = " ".join(args.split())
    args_tuple = ()
    if args != "void":
        for arg in args.split(","):
            if arg.endswith(("*", "long", "int", "size_t")):
                arg_type = arg.strip()
                arg_name = ""
            else:
                m2 = p2.match(arg)
                arg_type = m2.group(1).strip()
                arg_name = m2.group(2).strip()
            args_tuple += ((arg_type, arg_name),)
    SYSCALL_PROTOTYPES[call_name] = ("LE RETOUR C'EST PAS LONG SALOPE", args_tuple)

for call_name in sorted(SYSCALL_PROTOTYPES):
    signature = SYSCALL_PROTOTYPES[call_name]
    args_tuple = signature[1]
    #print('"%s": ("%s", (' % (call_name, signature[0]))
    for arg in args_tuple:
        print(('    ("%s", "%s"),' % (arg[0], arg[1])))
    #print(')),')
