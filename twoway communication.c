#include<stdio.h>
#include<unistd.h>

int main() {
   int pipefds1[2], pipefds2[2];
   int returnstatus1, returnstatus2;
   int pid;
   char pipe1writemessage[20] = "Hi";
   char pipe2writemessage[20] = "Hello";
   char readmessage[20];

   returnstatus1 = pipe(pipefds1);
   if (returnstatus1 == -1) {
      printf("Unable to create pipe 1 \n");
      return 1;
   }

   returnstatus2 = pipe(pipefds2);
   if (returnstatus2 == -1) {
      printf("Unable to create pipe 2 \n");
      return 1;
   }

   pid = fork();

   if (pid != 0) { // Parent process
      close(pipefds1[0]); // Close the unwanted pipe1 read side
      close(pipefds2[1]); // Close the unwanted pipe2 write side

      if(write(pipefds1[1], pipe1writemessage, sizeof(pipe1writemessage)) == -1){
         printf("Error writing to pipe 1\n");
         return 1;
      }

      if(read(pipefds2[0], readmessage, sizeof(readmessage)) == -1){
         printf("Error reading from pipe 2\n");
         return 1;
      }

      printf("In Parent: Reading from pipe 2 – Message is %s\n", readmessage);
   } else { // Child process
      close(pipefds1[1]); // Close the unwanted pipe1 write side
      close(pipefds2[0]); // Close the unwanted pipe2 read side

      if(read(pipefds1[0], readmessage, sizeof(readmessage)) == -1){
         printf("Error reading from pipe 1\n");
         return 1;
      }

      printf("In Child: Reading from pipe 1 – Message is %s\n", readmessage);

      if(write(pipefds2[1], pipe2writemessage, sizeof(pipe2writemessage)) == -1){
         printf("Error writing to pipe 2\n");
         return 1;
      }
   }

   return 0;
}
