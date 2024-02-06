#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cmath>
#include <regex>
using namespace std;

/*

Advent of Code 2016
Day 1

*/


// The following function converts L or R into degrees, with 0 being North.
int getdirection (string step, int direction) {
	if (step.substr(0,1) == "L")
		direction = direction - 90;
	if (step.substr(0,1) == "R")
		direction = direction + 90;

	if (direction == -90)
		direction = 270;
	if (direction == 360)
		direction = 0;

	return direction;
}

// The following function checks to see if the current (x,y) has been visited before.  It is called for full integer of travel.  
// It returns the distance from (0,0) if we visit a coordinate that has already been visited, or 0 if it has not.
int checkposition(vector <pair <int, int>>& mytracker, int x, int y) {
	int returnvalue = 0;
	for (int i = 0; i < mytracker.size(); i++) {
		if (mytracker[i].first == x and mytracker[i].second == y and mytracker.size() > 1 and returnvalue == 0) {
			returnvalue =  abs(x) + abs(y);
		}
	}
	return returnvalue;

}

// The following function moves one step at a time for a given line of instruction, recording each integer of movement into our vector database.
// It calls the checkposition function at each step of movement to see if we have been there before.  If checkposition returns something other
// than zero, the first value (of this loop) is returned.  Otherwise return 0.  Needed two loops, one for E-W and one for N-S.
int move (vector <pair <int, int>>& mytracker, int direction, int distance, int& x, int& y) {
	int myreturn = 0;
	int move = 1;
	if (distance < 0)
		move = -1;
	if (direction % 180 == 0) {
		for (int i = 0; i < abs(distance); i++) {
			y = y + move;
			int myd = checkposition(mytracker, x, y);
			if (myreturn == 0 and myd > 0)
				myreturn = myd;
			mytracker.push_back({x, y});
		}
	} else {
		for (int i = 0; i < abs(distance); i++) {
			x = x + move;
			int myd = checkposition(mytracker, x, y);
			if (myreturn == 0 and myd > 0)
				myreturn = myd;
			mytracker.push_back({x, y});
		}
	}
	return myreturn;
}

// Build a vector of instructions, and a vector of pairs for (x,y) coordinates that have been visited.
int main() {
        ifstream myfile;
        string line;
	int x = 0;
	int y = 0;
	int direction = 0;
	int firstcross = 0;
	vector <string> steps;
        myfile.open("input.txt", ios::in);
        if (myfile.is_open()) {
                while ( getline (myfile,line) ) {
                        int n = line.length();
			string delimiter = ", ";
			int pos = 0;
			string token;
			while ((pos = line.find(delimiter)) != std::string::npos) {
				token = line.substr(0, line.find(delimiter));
				steps.push_back(token);
				line.erase(0, pos + delimiter.length());
			}
			steps.push_back(line);
			cout << endl << endl << "total steps to take:           " << steps.size() << endl;
		}
        myfile.close();
        }
        else cout << "Unable to open file";

	cout << "starting position (x,y):       (" << x << "," << y << ")" << endl;
	vector <pair <int, int>> mytracker;

// send each line of instruction to the move function.  The first time we get a result other than zero back, save it as variable firstcross.
	for (int i = 0; i < steps.size(); i++) {
		direction = getdirection(steps[i], direction);
		int distance = stoi(steps[i].substr(1,steps[i].length()-1));

		if (direction > 179)
			distance = distance * -1;

		int test = move(mytracker, direction, distance, x, y);
		if (firstcross == 0)
			firstcross = test;
	}

	cout << "finishing position (x,y):      (" << x << "," << y << ")" << endl;
	cout << "total traveled (part one):     " << abs(x) + abs(y) << endl;
	cout << "first double visit (part two): " << firstcross << endl << endl << endl;




}

