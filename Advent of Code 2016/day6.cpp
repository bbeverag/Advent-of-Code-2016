#include <iostream>
#include <fstream>
#include <string>
#include <vector>
using namespace std;

void partone(vector <string> input) {
	cout << "part one: ";
	int n = input[0].length();
	for (int i = 0; i < n; i++) {
		int arr[26] = {0};
		for (int j = 0; j < input.size(); j++) {
			int mypos = input[j][i] - 'a';
			arr[mypos]++;
		}
		int max = 0;
		int maxchar;
		for (int j = 0; j < 26; j++) {
			if (arr[j] > max) {
				maxchar = j;
				max = arr[j];
			}
		}
		char mychar = maxchar + 'a';
		cout << mychar;
	}
	cout << endl;
}

void parttwo(vector <string> input) {
	cout << "part two: ";
	int n = input[0].length();
	for (int i = 0; i < n; i++) {
		int arr[26] = {0};
		for (int j = 0; j < input.size(); j++) {
			int mypos = input[j][i] - 'a';
			arr[mypos]++;
		}
		int min = input.size();
		int minchar;
		for (int j = 0; j < 26; j++) {
			if (arr[j] < min) {
				minchar = j;
				min = arr[j];
			}
		}
		char mychar = minchar + 'a';
		cout << mychar;
	}
	cout << endl;
}


int main() {
	vector <string> input;
	string message = "";
        ifstream myfile;
        string line;
        myfile.open("input6.txt", ios::in);
        if (myfile.is_open()) {
                while ( getline (myfile,line) ) {
			input.push_back(line);
		}
        myfile.close();
        }
        else cout << "Unable to open file";
	partone(input);
	parttwo(input);
}

