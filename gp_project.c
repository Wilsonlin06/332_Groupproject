/* 
The program assumes that the custom commands [tree, path, list, exit]
that  you want to execute are called tree.exe, path.exe, list.exe, 
and they all reside in the same directory as this program.
*/

#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <dirent.h>


// Custom project commands
char* custom_commands[] = {"tree", "path", "list", "exit"}; 
char* cmds[4];		// To save commands
char** new_argv;
int cmd_cnt = 0;		// Command counter
int len = sizeof(custom_commands)/sizeof(char *);
int agc;

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

void tree(){
	printf("%s\n", "Test output: Tree command.");
    struct stat st = {0};
    char path[50];
    if(stat("Dir0/", &st) == -1){
		mkdir("Dir0", 0777) ;  // Check if directory doesn't exist, then create directory
		printf("Folder Dir0 created successfully!\n");
	}else printf("The folder Dir0 exists.\n");
	sprintf(path,"%s/","Dir0");
    chdir(path);		// Change the working directory
    if(stat("Dir1/", &st) == -1){
		mkdir("Dir1", 0777);   // Check if directory doesn't exist, then create directory
		printf("Folder Dir1 created successfully!\n");
	}else printf("The folder Dir1 exists.\n");
    if(access("t1.txt", F_OK) == -1) {	// Check if file doesn't exist, then create file
		sprintf(path, "%st1.txt", "");
		int file1 = open(path, O_WRONLY | O_CREAT, 0777);
		printf("File t1.txt created successfully!\n");
	}else printf("The file t1.txt exists.\n");
	if(access("t2.txt", F_OK) == -1) {  // Check if file doesn't exist, then create file
		sprintf(path, "%st2.txt", "");
		int file2 = open(path, O_WRONLY | O_CREAT, 0777);
		printf("File t2.txt created successfully!\n");
	}else printf("The file t2.txt exists.\n");
	if(access("t3.txt", F_OK) == -1) {  // Check if file doesn't exist, then create file
		sprintf(path, "%st3.txt", "");
		int file3 = open(path, O_WRONLY | O_CREAT, 0777);
		printf("File t3.txt created successfully!\n");
	}else printf("The file t3.txt exists.\n");
}
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
void list(){
	clearTerminal();
	printContents();
	printToFile();
	renameFile();
}
void path(){
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
       perror("getcwd() error\n");
   }
   //write path into t2.txt
   write(text2, cwd, sizeof(cwd));
   close(text2);
   //rename the t2.txt to path-into.txt
   ret = rename("t2.txt","path-info.txt");
   if(ret == 0) {
      printf("File renamed successfully\n");
   } else {
      printf("Error: unable to rename the file.\n");
   }
   //concentenate two files into one
   file1 = fopen("tree.txt", "r"); 
   if (file1 == NULL) 
   { 
       printf("Cannot open file tree.txt\n"); 
       exit(0); 
   } 
  
  
   file2 = fopen("path-info.txt", "r"); 
   if (file2 == NULL) 
   { 
       printf("Cannot open file path-info.txt \n"); 
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
  
   printf("\nContents copied to t3.txt\n"); 
  
   fclose(file1); 
   fclose(file2);
   fclose(file3);
   // rename the t3.txt
   rename("t3.txt","log.txt");	
   // remove tree.txt and path.txt
   if (remove("tree.txt") == 0){ 
      printf("Deleted successfully\n"); }
   else{
      printf("Unable to delete the file\n"); }
   if (remove("path-info.txt") == 0){ 
      printf("Deleted successfully\n"); }
   else{
      printf("Unable to delete the file\n");} 
}
int exit_(){
    struct dirent *de; // Pointer for directory entry
    char fileName[255];
    DIR *dr = opendir(".");

    printf("Commands history:\n");
	for(int i = 0;i < 4;i++){
        printf("%d.%s\n",i+1,cmds[i]);
    }

	printf("Files list in current directory:\n");
    while ((de = readdir(dr)) != NULL){
        printf("%s\n", de->d_name);
    }
    closedir(dr);
    printf("%s\n","Press 'enter' to exit.");
    if(getchar() != '\n') return 1;
    else {
        printf("%s\n", "Bye");
        return 0;
    }
}

int execute_custom_commands(char** args) {
	int pid;
	// allocate memory and copy strings
    new_argv = malloc((agc+1) * sizeof *new_argv);
    for(int i = 0; i < agc; ++i)
    {
        size_t length = strlen(args[i])+1;
        new_argv[i] = malloc(length);
        memcpy(new_argv[i], args[i], length);
    }
    // new_argv[agc] = NULL;																																																																																																																																			
	if(cmds[3] != NULL){
		for(int i = 0; i<3; i++) cmds[i] = cmds[i+1];
		for(int i = 0; i < agc; ++i)
		{
			if(new_argv[i]!=NULL){
				cmds[3] = new_argv[i];
				cmd_cnt++;
			}
		}
	}else{
		// copy commands from new_argv to cmds
		for(int i = 0; i < agc; ++i)
		{
			if(new_argv[i]!=NULL){
				cmds[cmd_cnt] = new_argv[i];
				cmd_cnt++;
			}
			printf("%s\n", new_argv[i]);
		}
	}
	pid = fork();
	if(pid == 0) {
		if(!strcmp("tree", args[0])){
			printf("Command tree\n");
			tree();
		}
		if(!strcmp("exit", args[0])){
			return exit_();
		}
		if(!strcmp("path", args[0])){
			printf("Command path\n");
			path();
		}
		if(!strcmp("list", args[0])){
			printf("Command list\n");
			list();
		}
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
void loop() {
	char* line;
	char** args;
	int status;

	do {
		printf("Command >>> ");
		line = read_commands();
		args = parse_commands(line);
		status = execute_commands(args);
		free(line);
		free(args);
		if(status == 0){
			// free memory
			for(int i = 0; i < agc; ++i)
			{
				free(new_argv[i]);
			}
			free(new_argv);
			exit(status);
		}
	} while(status == 1); //if satus is 0, the loop will exit
}

int main(int argc, char const** argv)
{
	agc = argc;
	loop();

	return 0;
}