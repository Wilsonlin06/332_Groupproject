#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

int clearTerminal() {
	//clears the terminal screen
	int status, f;
	f = fork();
	if (f == 0) {
		//child
		execl("/bin/sh", "sh", "-c", "clear", (char *)0);
	}
	else if (f == -1) { printf("Error forking child\n"); perror("list.clearTerminal"); return -1; }
	else {
		//parent waits for execution
		status = waitpid(f, &status, 0);
	}
	if (status == -1) { printf("Error waiting for child\n"); perror("list.clearTerminal"); return -2; }
	return 0;
}

int printContents() {
	//prints detailed contents of cwd to terminal
	int status, f;
	f = fork();
	if (f == 0) {
		//child
		execl("/bin/ls", "ls", "-l", (char *)0);
	}
	else if (f == -1) { printf("Error forking child\n"); perror("list.printContents"); return -3; }
	else {
		//parent waits for execution
		status = waitpid(f, &status, 0);
	}
	if (status == -1) { printf("Error waiting for child\n"); perror("list.printContents"); return -4; }
	return 0;
}

int printToFile() {
	//prints detailed contents of cwd to t1.txt
	int status, f;
	f = fork();
	if (f == 0) {
		//child
		execl("/bin/sh", "sh", "-c", "ls -l >> t1.txt", (char *)0);
	}
	else if (f == -1) { printf("Error forking child\n"); perror("list.printToFile"); return -5; }
	else {
		//parent waits for execution
		status = waitpid(f, &status, 0);
	}
	if (status == -1) { printf("Error waiting for child\n"); perror("list.printToFile"); return -6; }
	return 0;
}

int renameFile() {
	//changes name of t1.txt to tree.txt
	int status, f;
	f = fork();
	if (f == 0) {
		//child
		execl("/bin/mv", "mv", "t1.txt", "tree.txt", (char *)0);
	}
	else if (f == -1) { printf("Error forking child\n"); perror("list.renameFile"); return -7; }
	else {
		//parent waits for execution
		status = waitpid(f, &status, 0);
	}
	if (status == -1) { printf("Error waiting for child\n"); perror("list.renameFile"); return -8; }
	return 0;
}

int main() {
	clearTerminal();
	printContents();
	printToFile();
	renameFile();
	return 0;
}
