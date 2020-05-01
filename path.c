#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
int main() {
   FILE *file1,*file2,*file3;
   char cwd[100];
   char meg[100]; 
   int ret;
   char c;
   int text2 = open("t2.txt",O_RDWR);
   //print out dirctory
   if (getcwd(cwd, sizeof(cwd)) != NULL) {
       printf("Current working dir: %s\n", cwd);
		
   } else {
       perror("getcwd() error");
       return 1;
   }
   //write path into t2.txt
   write(text2, cwd, sizeof(cwd));
   close(text2);
   //rename the t2.txt to path-into.txt
   ret = rename("t2.txt","path-info.txt");
   if(ret == 0) {
      printf("File renamed successfully");
   } else {
      printf("Error: unable to rename the file");
   }
   //concentenate two files into one
   file1 = fopen("tree.txt", "r"); 
   if (file1 == NULL) 
   { 
       printf("Cannot open file tree.txt\n"); 
       exit(0); 
   } 
  
  
   file2 = fopen("path.txt", "r"); 
   if (file2 == NULL) 
   { 
       printf("Cannot open file path.txt \n"); 
       exit(0); 
   } 
   file3 = fopen("t3.txt","w");
   if (file3 == NULL) 
   { 
       printf("Cannot open file t3.txt \n"); 
       exit(0); 
   } 
   // Read contents from file 
   c = fgetc(file1); 
   while (c != EOF) 
   { 
       fputc(c, file3); 
       c = fgetc(file1); 
   }
   c = fgetc(file2);
   while (c != EOF) 
   { 
        putc(c, file3); 
        c = fgetc(file2); 
   }
  
   printf("\nContents copied to t3.txt"); 
  
   fclose(file1); 
   fclose(file2);
   fclose(file3);
   // rename the t3.txt
   rename("t3.txt","log.txt");	
   // remove tree.txt and path.txt
   if (remove("tree.txt") == 0){ 
      printf("Deleted successfully"); }
   else{
      printf("Unable to delete the file"); }
   if (remove("path.txt") == 0){ 
      printf("Deleted successfully"); }
   else{
      printf("Unable to delete the file");} 
  
   return 0;
}
