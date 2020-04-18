#include <iostream>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <string>
#include <sstream>
using namespace std;


// NAME: An Vo
// DATE: March 8th, 2020
// CLASS: Operating Systems
// LAB 2


int main(){

	cout << "*************" << endl;
	cout << "SHELL STARTED" << endl;
	cout << "*************" << endl;
	pid_t pid;
	string input;
	do{
		string command,  arguments;
		stringstream cmd, args;

		// display myshell and getline for command
		cout << "MYSHELL>> ";
		getline(cin, input);

		// parse input and get arguments and command
		istringstream iss(input);
		iss >> command >> arguments;

		// Combine comands using sstream
		cmd << "/usr/bin/" << command;
		args << "-" << arguments;

		// convert sstream to string
		command = cmd.str();
		arguments = args.str();
		// place command and args into array
		const char * executes[] = {&command[0], &arguments[1], 0};

		// fork for child process
		pid = fork();

		if(pid == 0){ // Child Process
			// execv with vect as agruments and command
			if(input == "exit"){
				exit(0);
			}
			if(execve(executes[0], (char* const*)executes, NULL) < 0){
				cout << "Command could not be found" << endl;
			}
			exit(0);
		}

		else{
			wait(NULL);
		}
	}while(input != "exit");

	return 0;
}
