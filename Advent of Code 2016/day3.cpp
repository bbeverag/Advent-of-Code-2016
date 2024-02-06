#include <iostream>
#include <fstream>
#include <string>
#include <regex>
using namespace std;

int main() {
	int possible = 0;
	vector <tuple<int, int, int>> triangles;
	regex myregex("\\s*(\\d*)\\s*(\\d*)\\s*(\\d*)\\s*");
        ifstream myfile;
        string line;
        myfile.open("input.txt", ios::in);
        if (myfile.is_open()) {
                while ( getline (myfile,line) ) {
                        int n = line.length();
			smatch mymatch;
			regex_match(line, mymatch, myregex);
			if (mymatch[0].matched == true)
				triangles.push_back({stoi(mymatch[1]), stoi(mymatch[2]), stoi(mymatch[3])});
		}
        myfile.close();
        }
        else cout << "Unable to open file";

	for (int i = 0; i < triangles.size(); i++) {
		int t0 = get<0>(triangles[i]);
		int t1 = get<1>(triangles[i]);
		int t2 = get<2>(triangles[i]);

		if (t0 + t1 > t2 and t1 + t2 > t0 and t2 + t0 > t1)
			possible++;

	}

	cout << "Triangles possible by row: " << possible << endl;


	possible = 0;
	for (int i = 0; i < triangles.size(); i = i + 3) {
		int t0 = get<0>(triangles[i+0]);
		int t1 = get<0>(triangles[i+1]);
		int t2 = get<0>(triangles[i+2]);

		if (t0 + t1 > t2 and t1 + t2 > t0 and t2 + t0 > t1)
			possible++;

		t0 = get<1>(triangles[i+0]);
		t1 = get<1>(triangles[i+1]);
		t2 = get<1>(triangles[i+2]);

		if (t0 + t1 > t2 and t1 + t2 > t0 and t2 + t0 > t1)
			possible++;

		t0 = get<2>(triangles[i+0]);
		t1 = get<2>(triangles[i+1]);
		t2 = get<2>(triangles[i+2]);

		if (t0 + t1 > t2 and t1 + t2 > t0 and t2 + t0 > t1)
			possible++;

	}

	cout << "Triangles possible by column: " << possible << endl;
	

}

