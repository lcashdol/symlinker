This creates an x number of symlinks using the pid in the filename in order to clobber system files by linking to them when programs use 
/tmp in an insecure manner. This isn't really a problem on modern day unixes.  I've developed and tested it on an SGI Indy R5000 running 
IRIX 6.5.22.  
