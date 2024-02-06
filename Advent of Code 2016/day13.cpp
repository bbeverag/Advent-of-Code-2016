#include <iostream>
#include <fstream>
#include <string>
#include <bitset>
#include <vector>
using namespace std;

int iswall(pair <int, int> xy) {
	long long unsigned int dfn = 1352;
	int x = xy.first;
	int y = xy.second;
	bitset<16> mynum {x*x + 3*x + 2*x*y + y + y*y + dfn};
	return mynum.count() % 2;
}

int checkmost(vector <pair <int, int>> realrooms) {
	sort(realrooms.begin(), realrooms.end());
	for (int i = 0; i < realrooms.size(); i++) {
		if (realrooms[i].first == realrooms[i+1].first and realrooms[i].second == realrooms[i+1].second) {
			realrooms.erase(i+1);
			i--;
		}
	}
	for (int i = 0; i < realrooms.size(); i++) {
		if (iswall(realrooms[i]) == 1) {
			realrooms.erase(i);
			i--;
		}
	}
	return realrooms.size();
}

void checkmoves(pair <int, int> xy, int &shortest, int mymoves, vector <pair <int, int>> visited, vector <pair <int, int>> realrooms, int &mostroomssaw) {
	mymoves++;
	cout << "moves: " << mymoves << " (" << xy.first << "," << xy.second << ")" << endl;
	visited.push_back(xy);
	if (mymoves > shortest)
		return;
	if (mymoves > 100)
		return;
	if (xy.first == 31 and xy.second == 39) {
		if (mymoves < shortest)
			shortest = mymoves;
			mostroomssaw = checkmost(realrooms);
		return;
	}
	if (iswall(xy) == 1)
		return;


	int x = xy.first;
	int y = xy.second;

	pair <int, int> up (x, y - 1);
	pair <int, int> down (x, y + 1);
	pair <int, int> left (x - 1, y);
	pair <int, int> right (x + 1, y);

	if (mymoves < 51 and x > 0 and y > 0) {
		realrooms.push_back(xy);
		realrooms.push_back(up);
		realrooms.push_back(down);
		realrooms.push_back(left);
		realrooms.push_back(right);
	}

	int upok = 1;
	int downok = 1;
	int leftok = 1;
	int rightok = 1;

	for (int i = 0; i < visited.size(); i++) {
		if (visited[i] == up)
			upok = 0;
		if (visited[i] == down)
			downok = 0;
		if (visited[i] == left)
			leftok = 0;
		if (visited[i] == right)
			rightok = 0;
	}

	if (upok == 1 and y > 0)
		checkmoves(up, shortest, mymoves, visited, realrooms, mostroomssaw);
	if (downok == 1)
		checkmoves(down, shortest, mymoves, visited, realrooms, mostroomssaw);
	if (leftok == 1 and x > 0)
		checkmoves(left, shortest, mymoves, visited, realrooms, mostroomssaw);
	if (rightok == 1)
		checkmoves(right, shortest, mymoves, visited, realrooms, mostroomssaw);
}

int main() {
	vector <pair<int,int>> visited;
	vector <pair<int,int>> realrooms;
	int x = 1;
	int y = 1;
	pair <int, int> xy(1, 1);
	int shortest = 50000;
	int mostroomssaw = 0;
	int mymoves = -1;
	checkmoves(xy, shortest, mymoves, visited, realrooms, mostroomssaw);
	cout << "shortest route: " << shortest << endl;
	cout << "rooms in 50 steps: " << mostroomssaw << endl;
//	for (int i = 0; i < realrooms.size(); i++)
//		cout << realrooms[i].first << "," << realrooms[i].second << endl;
}


