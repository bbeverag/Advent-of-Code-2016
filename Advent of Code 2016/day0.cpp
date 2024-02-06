#include <iostream>
#include <fstream>
#include <string>
using namespace std;

int main() {
        ifstream myfile;
        string line;
        myfile.open("input.txt", ios::in);
        if (myfile.is_open()) {
                while ( getline (myfile,line) ) {
                        int n = line.length();
		}
        myfile.close();
        }
        else cout << "Unable to open file";
}

