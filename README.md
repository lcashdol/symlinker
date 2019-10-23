I've been looking around on my SGI Indy running IRIX 6.5.22 checking system utitlities for the use of /tmp.  I've noticed some scripts
using $$ to generate a unique file name in /tmp. I wrote this simple tool to generate links in /tmp in an attempt to clobber
files if the root user were to run any of the vulnerable utitliies.


This code creates an x number of symlinks using the pid in the filename in order to clobber system files by linking to them when programs 
use /tmp in an insecure manner. This isn't really a problem on modern day unixes.  I've developed and tested it on an SGI Indy R5000 running 
IRIX 6.5.22.  After running it monitors the target file's modification time to determine if the exploitation succeeded. 
