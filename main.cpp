#include <iostream>
#include "files.h"
#include "the.h"

using namespace std;

string process_to_string(string in){
	return in;
}

int main(int argc, char *argv[]){
	auto path_and_program = the(argv[0]).split_with("/");
	string program = path_and_program[path_and_program.size()];
	vector<string> input;
	for (int i = 1; i < argc; ++i) 
		input.emplace_back(string(argv[i]));
	cout << process_to_string(program);
	cout << endl;
}

