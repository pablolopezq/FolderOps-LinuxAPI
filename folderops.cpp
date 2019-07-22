#include <unistd.h>
#include <dirent.h>
#include <sys/types.h>
#include <sys/stat.h>

#include <iostream>
#include <string.h>
#include <stdio.h>
#include <bits/stdc++.h>
#include <errno.h>

using namespace std;

int check_command(string command){
	if(command == "create_folder")
		return 1;
	if(command == "delete_folder")
		return 2;	
	if(command == "list_folder")
		return 3;
	return -1;
}

void tokenize(string command, vector<string> &tokens){
	stringstream stream(command);
	string intermediate;
	while(getline(stream, intermediate, ' ')) 
    { 
        tokens.push_back(intermediate); 
    } 
}

void create_folder(string full_path, int mode){
	if (mkdir(full_path.c_str(), mode) == -1) 
        cerr << "Error :  " << strerror(errno) << endl; 
    else
        cout << "Directory created" << endl; 
}

void delete_folder(string full_path){
	if (rmdir(full_path.c_str()) == -1) 
        cerr << "Error :  " << strerror(errno) << endl; 
  
    else
        cout << "Directory deleted" << endl; 
}

int list_folder(string full_path){
	DIR *dp;
    struct dirent *dirp;
    if((dp = opendir(full_path.c_str())) == NULL) {
        cout << "Error(" << errno << ") opening " << full_path << endl;
        return errno;
    }

    while ((dirp = readdir(dp)) != NULL) {
        cout << dirp->d_name << endl;
    }
    closedir(dp);
    return 0;
}

int main(){

	string command;
	string full_path;
	bool active = true;
	vector<string> *tokens;
	int command_code = -1;

	while(active){

		tokens = new vector<string>(0);

		cout << "P> ";
		getline(cin, command);

		//cout << command << endl;

		tokenize(command, *tokens);
		command_code = check_command(tokens->at(0));

		switch(command_code){

			case 0:
				active = false;
				break;

			case 1:
				cout << "Create Folder" << endl;
				full_path = tokens->at(1) + tokens->at(2);
				cout << full_path << endl;
				create_folder(full_path, 0777);
				break;

			case 2:
				cout << "Delete Folder" << endl;
				cout << tokens->at(1) << endl;
				delete_folder(tokens->at(1));
				break;

			case 3:
				cout << "List Folder" << endl;
				//cout << tokens->at(1) << endl;
				list_folder(tokens->at(1));
				break;

			default:
				cout << "Invalid Command" << endl;
				break;

		}

	}

	return 0;
}