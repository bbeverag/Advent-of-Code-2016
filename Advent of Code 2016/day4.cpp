#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

/*
	for (int i = 0; i < 26; i++) {
		char mychar = i + 'a';
		cout << mychar << ": " << arr[i] << endl;
	}
*/

int returntop(int arr[26]) {
	int max = -1;
	int maxcount = 0;

	for (int i = 0; i < 26; i++) {
		if (arr[i] > maxcount) {
			maxcount = arr[i];
			max = i;
		}
	}

	return max;
}

int checkchecksum(string checksum, int arr[26]) {
	for (int i = 0; i < 5; i++) {
		int mychar = checksum[i] - 'a';
		int max = returntop(arr);
		if (max != mychar)
			return 0;
		arr[max] = 0;
	}

	return 1;

}

string unencryptroom(string room, int shift) {
	string unencrypted;
	for (int i = 0; i < room.length(); i++) {
		char charchar;
		if (room[i] == '-') {
			charchar = ' ';
		} else {
			int charint = room[i] + shift;
			if (charint > 122)
				charint = charint - 26;
			charchar = charint;
		}
		unencrypted = unencrypted + charchar;
	}

	return unencrypted;
}


int testline(string line) {
	int arr[26] = {0};
	int sector = stoi(line.substr(line.length()-10,3));
	string checksum = line.substr(line.length()-6,5);
	string room = line.substr(0,line.length()-11);

	for (int i = 0; i < room.length(); i++) {
		if (room[i] != '-') {
			int j = room[i] - 'a';
			arr[room[i] - 'a']++;
		}
	}

	if (checkchecksum(checksum, arr) == 1) {
		string myroom = unencryptroom(room, sector % 26);
		if (myroom == "northpole object storage")
			cout << sector << " " << myroom << endl;
		return sector;
	}

	return 0;
}


int main() {
	vector <string> rooms;
	int mysum = 0;
        ifstream myfile;
        string line;
        myfile.open("input4.txt", ios::in);
        if (myfile.is_open()) {
                while ( getline (myfile,line) ) {
                        int n = line.length();
			rooms.push_back(line);
		}
        myfile.close();
        }
        else cout << "Unable to open file";

	for (int i = 0; i < rooms.size(); i++)
		mysum = mysum + testline(rooms[i]);

	cout << "Sum of non-decoy room sectors: " << mysum << endl;

}

