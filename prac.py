print "Hello Kuttiyana"

# Method 1 of executing bash commands using python
#--------------------------------------------------------------------------------------------------
bashCommand = "ls"

import subprocess
#subprocess.Popen("ls")
subprocess.Popen(bashCommand) # U can't use commands with spaces by this method (Method 1) ! :(
subprocess.Popen("uname")
#--------------------------------------------------------------------------------------------------


# Method 2 of executing bash commands using python
#--------------------------------------------------------------------------------------------------
bashCommand = "whatis python"
#bashCommand = "uname -r"

import os
os.system(bashCommand) # U can use commands with spaces by this method (Method 1) ! :)
process = subprocess.Popen(bashCommand.split(), stdout=subprocess.PIPE)
output = process.communicate()[0]
#--------------------------------------------------------------------------------------------------
