#include <iostream>
#include <fstream>
#include <string>
#include <regex>
#include <array>
using namespace std;

// in part one, i simply use a regex to match the parenthesis expression.  I then use members of the return from that to shorten my 
// create a new string, trim the left of the original string, and loop through until i get no more matches.
int partone(string mystring) {
	string newstring;
	regex myregex("\\((\\d*)x(\\d*)\\)");
	smatch m;

	while (regex_search(mystring, m, myregex) == true) {
		string prefix = m.prefix();
		string suffix = m.suffix();

		int m1 = stoi(m[1]);
		int m2 = stoi(m[2]);

		newstring = newstring + prefix;
		int newstrlength = suffix.length() - m1;
		mystring = suffix.substr(m1, newstrlength);
		string copystring = suffix.substr(0,m1);
		for (int i = 0; i < m2; i++)
			newstring = newstring + copystring;
	}
	newstring = newstring + mystring;
	return newstring.length();
}

// helper function to improve readability of parttwo()
int getlength(string mystring) {
	for (int i = 0; i < mystring.length(); i++) 
		if (mystring[i] == 'x')
			return stoi(mystring.substr(0,i));
	return 0;
}

// helper function to improve readability of parttwo()
int getcount(string mystring) {
	for (int i = 0; i < mystring.length(); i++) 
		if (mystring[i] == ')')
			return stoi(mystring.substr(0,i));
	return 0;
}

// in part two i use an array to track the number of times each character will appear.  as I loop through, i set the special characters value
// to zero, and multiply the A-Z positions according to the parenthetical data.  At the end, i loop through and sum them.  I couldn't get 
// accumulate to work so i just for looped it.  
unsigned long parttwo(string mystring) {
	int n = mystring.length();
	//int arr[n] = {1};
	vector <int> v(mystring.length());
	for (int i = 0; i < mystring.length(); i++)
		v[i] = 1;
		//arr[i] = 1;
	for (int i = 0; i < mystring.length(); i++) {
		if (mystring[i] < 65 or mystring[i] > 90) //ascii values
			v[i] = 0;
			//			arr[i] = 0;
		if (mystring[i] == '(') {
			int mylength = getlength(mystring.substr(i+1,mystring.length()-i-1));
			int mycount = getcount(mystring.substr(i+to_string(mylength).length()+2,mystring.length()-i-to_string(mylength).length()-2));
			int mystart = i+to_string(mylength).length()+to_string(mycount).length()+3;
			for (int j = 0; j < mylength; j++)
				v[mystart + j] = v[mystart + j] * mycount;
				//arr[mystart+j] = arr[mystart+j] * mycount;
		}
	}
	unsigned long sum = 0;
	for (int i = 0; i < mystring.length(); i++)
		sum = sum + v[i];
		//sum = sum + arr[i];
	return sum;
}

int main() {
	string mystring;
        ifstream myfile;
        string line;
        myfile.open("input9.txt", ios::in);
        if (myfile.is_open()) {
                while ( getline (myfile,line) ) {
                        int n = line.length();
			mystring = line;
		}
        myfile.close();
        }
        else cout << "Unable to open file";

	int origlength = mystring.length();


	cout << endl;

	cout << "original length: " << origlength << endl;
	cout << "decompressed length: " << partone(mystring) << endl;
	cout << "part two decompression: " << parttwo(mystring) << endl;

}

