/*
This program is free software: you can redistribute it and/or modify it under the terms of the GNU General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.
This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. 
See the GNU General Public License for more details.
You should have received a copy of the GNU General Public License along with this program. If not, see <https://www.gnu.org/licenses/>.
*/
    
    
#include <stdio.h>
#include <fcntl.h>
#include <errno.h>
#include <string.h>
#include <unistd.h>
 #include <stdlib.h>

extern int errno;

#define DATA_MAX 4


int main(int argc, char * argv[])
{
  int i;
  int fd;
  FILE * fd2;
  int arg;
  unsigned char data[4];
  unsigned int data2[4];
  unsigned char command[255];
  ssize_t datasize;

  fprintf(stdout, "bindkeys v0.1\n");
  
  if (argc < 3)
  {
     fprintf(stdout, "usage : bindkeys /dev/hidraw? file.conf\n");
     return 1;
  }
 
 // open hidraw device
 if ( (fd = open(argv[1], O_RDONLY)) == -1)
 {
   fprintf(stdout, "open error %s : %s\n", argv[1], strerror(errno));   
   return 1;
 }

 // open conf file
 if ( (fd2 = fopen(argv[2], "r")) == NULL)
 {
   fprintf(stdout, "open error %s : %s\n", argv[2], strerror(errno));
   close(fd);   
   return 1;
 }


 while(1)
 {
   for (i=0; i < DATA_MAX; i++)
   {
     data[i] = 0;
     data2[i] = 0;
   }
 
   if ( (datasize = read(fd, data, sizeof data)) == -1)
   {
     fprintf(stdout, "read error %s : %s\n", argv[1], strerror(errno));
     close(fd);
     return 1;
   }
     
   fprintf(stdout, "Key : ");   
      
  for(i=0; i< DATA_MAX; i++)
  {
    fprintf(stdout, "%02X ", data[i]);
  }
   
    fseek(fd2, 0, SEEK_SET);
   
   // search for the command for the key pressed
   while(1)
   {
      if ( ( arg = fscanf(fd2, "%02X %02X %02X %02X %254s", &data2[0], &data2[1], &data2[2], &data2[3], command)) == EOF)
       {
        break;
       }
       
       if (arg != 5) break; 
       
       if ((unsigned int)data[0] == data2[0] && (unsigned int)data[1] == data2[1] && (unsigned int)data[2] == data2[2] && (unsigned int)data[3] == data2[3] )
       {
          fprintf(stdout, "Command -> %s", command);
          system(command);
          break;
       }
       
   }

   fprintf(stdout, "\n");
 }


 fclose(fd2);
 close(fd);
 
 return 0;
}
