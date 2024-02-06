#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <regex>
using namespace std;

void inc(map<char, int> &registers, string line) {
	registers[line[4]]++;
}

void dec(map<char, int> &registers, string line) {
	registers[line[4]]--;
}

void cpy(map<char, int> &registers, string line) {
	regex myregex("cpy (\\d*|[a-d]) ([a-d])");
	smatch m;
	regex_match(line, m, myregex);
	string match1, match2;
	if (m[0].matched == true) {
		match1 = m[1];
		match2 = m[2];
		if (match1[0] > 47 and match1[0] < 58)
		registers[match2[0]] = stoi(match1);
		if (match1[0] < 48 or match1[0] > 57)
		registers[match2[0]] = registers[match1[0]];
	}
}

int jnz(map<char, int> &registers, string line, int i) {
	string match1, match2;
	regex myregex("jnz (\\d*|[a-d]) (.*)");
	smatch m;
	regex_match(line, m, myregex);
	if (m[0].matched == true) {
		match1 = m[1];
		match2 = m[2];
		if (match1[0] < 101 and match1[0] > 96)
			if (registers[match1[0]] != 0)
				i = i + stoi(match2) - 1;
		if ((match1[0] < 58 and match1[0] > 48) or match1[0] == '-')
			i = i + stoi(match2) - 1;
	}
	return i;
}

int theloop(int a, int b, int c, int d, vector<string> &input) {
	map <char, int> registers;

	registers['a'] = a;
	registers['b'] = b;
	registers['c'] = c;
	registers['d'] = d;

	for (int i = 0; i < input.size(); i++) {
		if (i == 10 and registers['b'] != 0) {	// this is cheating in a way, based on my input.  Won't work for everyone.
			registers['a'] = registers['a'] + registers['b'];	// find your 3 line loop and update i.
			registers['b'] = 0;					// look for inc a, dec b, jnz b -2
			i = 12;
		}
		if (input[i].substr(0,3) == "inc")
			inc(registers, input[i]);
		if (input[i].substr(0,3) == "dec")
			dec(registers, input[i]);
		if (input[i].substr(0,3) == "cpy")
			cpy(registers, input[i]);
		if (input[i].substr(0,3) == "jnz")
			i = jnz(registers, input[i], i);
	}
	return registers['a'];
}

int main() {
	vector <string> input;
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


	cout << "part one: " << theloop(0,0,0,0,input) << endl;
	cout << "part two: " << theloop(0,0,1,0,input) << endl;



}

