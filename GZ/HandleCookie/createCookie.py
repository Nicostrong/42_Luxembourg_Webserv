import sys
from http.cookies import SimpleCookie

def makeCookie():
    if len(sys.argv) < 2 or len(sys.argv) % 2 == 0:
        print(f"Error: Lacks args or lacks key or value")
        return
    C = SimpleCookie()
    for i in range(1, len(sys.argv), 2):
        C[sys.argv[i]] = sys.argv[i + 1]
    print(f"{C.output()}")
    
makeCookie()

#Create cookie using python
""" Flavian tells me to create a trivial cookie using python (with args)
Lets google that - DONE

then he wants me to generate 1 HTML /css/js page and 1 Php Page
easy
 """