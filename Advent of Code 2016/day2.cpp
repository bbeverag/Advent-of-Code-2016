#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <set>
#include <algorithm>
using namespace std;

int press(int curnum, char dir) {

	if (dir == 'U' and curnum > 3)
		curnum = curnum - 3;

	if (dir == 'D' and curnum < 7)
		curnum = curnum + 3;

	if (dir == 'L' and curnum % 3 != 1)
		curnum = curnum - 1;

	if (dir == 'R' and curnum % 3 != 0)
		curnum = curnum + 1;

	return curnum;
}

int press2(int curnum, char dir) {

	std::set<int> top {1, 2, 4, 5, 9};
	std::set<int> bottom {5, 9, 10, 12, 13};
	std::set<int> left {1, 2, 5, 10, 13};
	std::set<int> right {1, 4, 9, 12, 13};

	if (dir == 'U' and find(top.begin(), top.end(), curnum) == top.end()) {
		if (curnum == 13 or curnum == 3)
			curnum = curnum + 2;
		curnum = curnum - 4;
	}

	if (dir == 'D' and find(bottom.begin(), bottom.end(), curnum) == bottom.end()) {
		if (curnum == 1 or curnum == 11)
			curnum = curnum - 2;
		curnum = curnum + 4;
	}

	if (dir == 'L' and find(left.begin(), left.end(), curnum) == left.end())
		curnum = curnum - 1;

	if (dir == 'R' and find(right.begin(), right.end(), curnum) == right.end())
		curnum = curnum + 1;

	return curnum;
}

int main() {
	vector <string> input;
	vector <int> code;
        ifstream myfile;
        string line;
        myfile.open("input2.txt", ios::in);
        if (myfile.is_open()) {
                while ( getline (myfile,line) ) {
                        int n = line.length();
			input.push_back(line);
		}
        myfile.close();
        }
        else cout << "Unable to open file";

	cout << "first code: ";
	int curnum = 5;
	for (int i = 0; i < input.size(); i++) {
		for (int j = 0; j < input[i].length(); j++)
			curnum = press(curnum, input[i][j]);
		code.push_back(curnum);
	}

	for (int i = 0; i < code.size(); i++)
		cout << code[i];
	cout << endl;

	cout << "second code: ";
	curnum = 5;
	code.clear();
	for (int i = 0; i < input.size(); i++) {
		for (int j = 0; j < input[i].length(); j++)
			curnum = press2(curnum, input[i][j]);
		code.push_back(curnum);
	}

	for (int i = 0; i < code.size(); i++) {
		if (code[i] < 10) {
			cout << code[i];
		} else {
			switch (code[i]) {
				case 10:
					cout << "A";
					break;
				case 11:
					cout << "B";
					break;
				case 12:
					cout << "C";
					break;
				case 13:
					cout << "D";
					break;
			}
		}
	}
	cout << endl;

}

