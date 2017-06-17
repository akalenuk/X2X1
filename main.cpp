#include <iostream>
#include "the.h"

using namespace std;

string process_to_string(string in){
	return in;
}

int main(int argc, char *argv[]){
	string in;
	cin >> in;

	cout << process_to_string(in);
}
