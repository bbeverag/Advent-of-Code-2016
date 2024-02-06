#include <iostream>
#include <fstream>
#include <string>
#include <vector>
using namespace std;

// return 0 if there is an abba inside brackets.  return 1 if we make it to the end of the string and found at least one abba
// outside of brackets.
int checktls(string line) {
	int inside = 0;
	int goodabba = 0;
	for (int i = 0; i < line.length() - 3; i++) {
		if (line[i] == '[')
			inside = 1;
		if (line[i] == ']')
			inside = 0;
		if (line[i] == line[i+3] and line[i+1] == line[i+2] and inside == 0 and line[i] != line[i+1])
			goodabba = 1;
		if (line[i] == line[i+3] and line[i+1] == line[i+2] and inside == 1 and line[i] != line[i+1])
			return 0;
	}
	if (goodabba == 1) {
		return 1;
	}
	return 0;
}

// return 1 if we find bab inside brackets, return 0 if we don't.  a and b are predefined.
int checkbab(string line, char a, char b) {
	int inside = 0;
	for (int i = 0; i < line.length() - 2; i++) {
		if (line[i] == '[')
			inside = 1;
		if (line[i] == ']')
			inside = 0;
		if (line[i] == b and line[i+1] == a and line[i+2] == b and inside == 1)
			return 1;
	}
	return 0;
}

// look for aba outside of brackets.  a and b are not predefined but must be different.  If we find it, call checkbab 
// to look for bab (predefined) in brackets.  if we find bab in brackets, and aba outside of brackets, return 1, otherwise
// return 0.
int checkssl(string line) {
	int inside = 0;
	for (int i = 0; i < line.length() - 2; i++) {
		if (line[i] == '[')
			inside = 1;
		if (line[i] == ']')
			inside = 0;
		if (line[i] == line[i+2] and line[i] != line[i+1] and inside == 0)
			if (checkbab(line, line[i], line[i+1]) == 1)
				return 1;
	}
	return 0;
}


int main() {
	vector <string> input;
	int tls = 0;
	int ssl = 0;
        ifstream myfile;
        string line;
        myfile.open("input.txt", ios::in);
        if (myfile.is_open()) {
                while ( getline (myfile,line) ) {
                        int n = line.length();
			input.push_back(line);
		}
        myfile.close();
        }
        else cout << "Unable to open file";

	for (int i = 0; i < input.size(); i++) {
		tls = tls + checktls(input[i]);
		ssl = ssl + checkssl(input[i]);
	}
	cout << "TLS: " << tls << endl;
	cout << "SSL: " << ssl << endl;
}

