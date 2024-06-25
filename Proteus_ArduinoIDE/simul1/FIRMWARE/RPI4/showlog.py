# Program to show incomming contents of the server log on the console:

import os, time, sys, select
pipe_name = '/tmp/server.log'


def readlog () :
    pipein = open(pipe_name, 'r')
    while not heardEnter():
        line = pipein.readline()
        if line != "" : 
           print (line[:-1])
        if line.startswith("***ENDS"):
           break
    pipein.close()
            
def heardEnter():
    i,o,e = select.select([sys.stdin],[],[],0)
    for s in i:
        if s == sys.stdin:
            input = sys.stdin.readline()
            return True
    return False            

if os.path.exists(pipe_name):
   os.remove(pipe_name)
os.mkfifo(pipe_name)  
readlog()
os.remove(pipe_name)

    
    

