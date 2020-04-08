#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int main (int argc, char *argv[])
{
	int child1, child2, child3, pid1, pid2, pid3, status;
	struct stat st = {0};
	child1 = fork(); // Create 1st fork
	if(child1 < 0){  //  Error report
		printf("Fork1 creation error!");
		return 1;
	}else if(child1 == 0){  // Child1 process		
		child2 = fork();  // Create 2nd fork
		if(child2 < 0){  // Error report
			printf("Fork2 creation error!");
			return 1;
		}else if(child2 == 0){  // Child2 process
			child3 = fork(); // Create 3rd fork
			if(child3 < 0){  // Error report
				return 1;
			}else if(child3 == 0){  // Child3 process			
				if(stat("Dir0/Dir1/", &st) == -1) mkdir("Dir0/Dir1", 0777);   // Check if directory doesn't exist, then create directory
			}
			char path[50];
			if(access("Dir0/t1.txt", F_OK) == -1) {	// Check if file doesn't exist, then create file
				sprintf(path, "%s/t1.txt", "Dir0");
				int file1 = open(path, O_WRONLY | O_CREAT, 0777);
			}
			if(access("Dir0/t2.txt", F_OK) == -1) {  // Check if file doesn't exist, then create file
				sprintf(path, "%s/t2.txt", "Dir0");
				int file2 = open(path, O_WRONLY | O_CREAT, 0777);
			}
			if(access("Dir0/t3.txt", F_OK) == -1) {  // Check if file doesn't exist, then create file
				sprintf(path, "%s/t3.txt", "Dir0");
				int file3 = open(path, O_WRONLY | O_CREAT, 0777);
			}
		}
		if(stat("Dir0/", &st) == -1) mkdir("Dir0", 0777) ;  // Check if directory doesn't exist, then create directory
	}else{
		pid3 = waitpid(child3, &status, 0);  // Wait for child3
		pid2 = waitpid(child2, &status, 0);  // Wait for child2
		pid1 = waitpid(child1, &status, 0);  // Wait for child1
	}
	return 0;
}
