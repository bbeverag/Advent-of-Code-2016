#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <regex>
using namespace std;

// Disc #(\d*) has (\d*) positions; at time=0, it is at position (\d*).

// (time + disc# + startpos) % discpositions == 0

// basic for loop, checks each disc using formula above, once all of them are modulus 0 it means the object can fall through.
// the number of discs is specified when called, to differentiate between part one and part two.
int runit (map <int,int> positions, map <int,int> starting, int discs) {
	int time = -1;

	while (0 == 0) {
		time++;
		int test = 0;
		for (int i = 1; i < discs; i++)
			test = test + ((time + i + starting[i]) % positions[i]);
		if (test == 0)
			return time;
	}
	return 0;
}


// import from input.txt into two maps -- one for number of positions and one for starting position.
int main() {
	map <int,int> positions;
	map <int,int> starting;
        ifstream myfile;
        string line;
        myfile.open("input.txt", ios::in);
        if (myfile.is_open()) {
                while ( getline (myfile,line) ) {
                        int n = line.length();
			regex myregex("Disc #(\\d*) has (\\d*) positions; at time=0, it is at position (\\d*).");
			smatch m;
			regex_match(line, m, myregex);
			if (m[0].matched == true) {
				positions[stoi(m[1])] = stoi(m[2]);
				starting[stoi(m[1])] = stoi(m[3]);
			}
		}
        myfile.close();
        }
        else cout << "Unable to open file";

	int partone = runit(positions, starting, positions.size());
	cout << "Part One: " << partone << endl;
	int parttwo = runit(positions, starting, positions.size() + 1);
	cout << "Part Two: " << parttwo << endl;

}

