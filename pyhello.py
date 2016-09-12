print "Hello Kuttiyana"
bashCommand = "ls"
#import os
#os.system(bashCommand)
import subprocess
subprocess.Popen("ls")
#process = subprocess.Popen(bashCommand.split(), stdout=subprocess.PIPE)
#output = process.communicate()[0]
