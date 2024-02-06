#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <regex>
using namespace std;

class AScreen {
	private:
		int arr[50][6] = {0};

	public:
		void draw_rectangle(string line) {
			regex myregex("rect (\\d*)x(\\d*)");
			smatch m;
			regex_match(line, m, myregex);
			if (m[0].matched == true) {
				int x = stoi(m[1]);
				int y = stoi(m[2]);
				for (int i = 0; i < x; i++)
					for (int j = 0; j < y; j++)
						arr[i][j] = 1;
			}
		}

		void rotate_row(string line) {
			int row[50] = {0};
			regex myregex("rotate row y=(\\d*) by (\\d*)");
			smatch m;
			regex_match(line, m, myregex);
			if (m[0].matched == true) {
				for (int i = 0; i < 50; i++)
					row[i] = arr[i][stoi(m[1])];
				for (int i = 0; i < 50; i++) {
					int j = i + stoi(m[2]);
					if (j > 49)
						j = j - 50;
					arr[j][stoi(m[1])] = row[i];
				}
			}
		}

		void rotate_column(string line) {
			int column[6] = {0};
			regex myregex("rotate column x=(\\d*) by (\\d*)");
			smatch m;
			regex_match(line, m, myregex);
			if (m[0].matched == true) {
				for (int i = 0; i < 6; i++)
					column[i] = arr[stoi(m[1])][i];
				for (int i = 0; i < 6; i++) {
					int j = i + stoi(m[2]);
					if (j > 5)
						j = j - 6;
					arr[stoi(m[1])][j] = column[i];
				}
			}
		}

		int getpixel(int x, int y) {
			return arr[x][y];
		}
};

void draw_rectangle(string line, int *ptr[50][6]) {
//	ptr = 1;
}

int main() {
	vector <string> input;
	int litpixels = 0;
        ifstream myfile;
        string line;
        myfile.open("input8.txt", ios::in);
        if (myfile.is_open()) {
                while ( getline (myfile,line) ) {
                        int n = line.length();
			input.push_back(line);
		}
        myfile.close();
        }
        else cout << "Unable to open file";

	AScreen MyScreen;

	for (int i = 0; i < input.size(); i++) {
		if (input[i].substr(0,4) == "rect")
			MyScreen.draw_rectangle(input[i]);
		if (input[i].substr(0,10) == "rotate row")
			MyScreen.rotate_row(input[i]);
		if (input[i].substr(0,13) == "rotate column")
			MyScreen.rotate_column(input[i]);
	}

	cout << endl;

	for (int j = 0; j < 6; j++) {
		for (int i = 0; i < 50; i++) {
			if (MyScreen.getpixel(i, j) == 1) {
				litpixels++;
				cout << "X";
			} else cout << " ";
		}
		cout << endl;
	}
		cout << endl << "total lit pixels: " << litpixels << endl;

}

