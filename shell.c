/* 
The program assumes that the custom commands [tree, path, list, exit]
that  you want to execute are called tree.exe, path.exe, list.exe, 
and they all reside in the same directory as this program.
*/
#define _POSIX_SOURCE
#include <dirent.h>
#include <errno.h>
#include <sys/types.h>
#undef _POSIX_SOURCE
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <sys/stat.h>
#include <fcntl.h>


// Custom project commands
char* custom_commands[] = {"tree", "path", "list", "exit"}; 

int len = sizeof(custom_commands)/sizeof(char *);
char* cmds[4];

int execute_system_commands(char** args) {
	pid_t pid;
	int status;

	pid = fork();
	if (pid == 0) {
	    execvp(args[0], args);
	    perror("System command execution failed!");
	} else if (pid < 0) {
	    perror("Error forking");
	} else {
	    waitpid(pid, NULL, 0);
	}

	return 1;
}

int execute_custom_commands(char** args) {
	int pid;
	pid = fork();
    
    // Uncomment when the commands are implemented!
	if(pid == 0) {
		// if(!strcmp("tree", args[0])){
		// 	printf("Command tree\n");
		// 	tree();
		// }
  //       if(!strcmp("exit", args[0])){
		// 	printf("Command exit\n");
		// 	exit_();
		// }
		// if(!strcmp("path", args[0])){
		// 	printf("Command path\n");
		// 	path();
		// }
		// if(!strcmp("list", args[0])){
		// 	printf("Command list\n");
		// 	list();
		// }
	} else if (pid < 0) {
	    perror("Error forking");
	} else {
		waitpid(pid, NULL, 0); // wait for the child
	}
	return 1;
}

int execute_commands(char** args) {
	if (args[0] == NULL) {
	    return 1;
	}

	// if one of the custom commands
	for(int i = 0; i < len; i++) { 
		if(!strcmp(custom_commands[i], args[0])) { 
			return execute_custom_commands(args);
		}
	}

	return execute_system_commands(args);
}

int const BUFFSIZE_READ_LINE = 1024;

char* read_commands(void) {
	int index = 0;
	char *buffer = malloc(sizeof(char) * BUFFSIZE_READ_LINE);
	int character; 

	if (!buffer) {
	    fprintf(stderr, "Allocation error\n");
	    exit(0);
  	}

  	while(1) {
  		character = getchar();
  		if(character == EOF || character == '\n') {
  			buffer[index] = '\0';
  			return buffer;
  		} else {
  			buffer[index] = character;
  		}
  		index++;
  	}
}

int const BUFFSIZE_PARSE_LINE = 1024;
char* const DELIMETERS = " \t\r\n\a";

char** parse_commands(char* line) {
	char** commands = malloc(BUFFSIZE_PARSE_LINE * sizeof(char*));
	int index = 0;
	char* command;

	command = strtok(line, DELIMETERS);

	while(command != NULL) {
		commands[index] = command;
		index++;

		command = strtok(NULL, DELIMETERS);
	}

	commands[index] = NULL;

	return commands;
}

// loop reads the command entered by the user 
// parses the command 
// exectues the command
void loop(void) {
	char* line;
	char** args;
	int status;

	do {
		printf("%s", "Command >>> ");
		line = read_commands();
		args = parse_commands(line);
		status = execute_commands(args);
		free(line);
		free(args);
	} while(status); //if satus is 0, the loop will exit
}

int main(int argc, char const** argv)
{
	loop();

	return 0;
}