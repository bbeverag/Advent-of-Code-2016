#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <regex>
using namespace std;

// built a class to hold the info about the various robots zipping around.  Used a lot of negatives to denote untouched.
// in an attempt to do it "the right way" the variables are private and the methods are public.  So some of these jsut
// return a variable, and that's it.  I probably should have done some validation for setting variables, but I didn't.
class robot {

	private:
		int mybotid = -1;
		int myitem1 = -1;
		int myitem2 = -1;
		int mygivelow = -100;
		int mygivehigh = -100;

	public:
		void set_botid (int botid){
			mybotid = botid;
		}

		int get_botid () {
			return mybotid;
		}

		int get_itemcount () {
			int itemcount = 0;
			if (myitem1 != -1)
				itemcount++;
			if (myitem2 != -1)
				itemcount++;
			return itemcount;
		}

		int get_lowitem () {
			int lowitem = -1;
			if (myitem1 < myitem2) {
				lowitem = myitem1;
				myitem1 = -1;
			} else {
				lowitem = myitem2;
				myitem2 = -1;
			}
			return lowitem;
		}

		int get_highitem () {
			int highitem = -1;
			if (myitem1 > myitem2) {
				highitem = myitem1;
				myitem1 = -1;
			} else {
				highitem = myitem2;
				myitem2 = -1;
			}
			return highitem;
		}

		int get_givelow () {
			return mygivelow;
		}

		int get_givehigh () {
			return mygivehigh;
		}

		int add_item (int value) {
			if (get_itemcount() > 1) 
				return 0;
			if (myitem1 == -1) {
				myitem1 = value;
			} else {
				myitem2 = value;
			}
			return 1;
		}

		int check_compare (int item1, int item2) {
			if (myitem1 == item1 and myitem2 == item2)
				return -1;
			if (myitem1 == item2 and myitem2 == item1)
				return -1;
			return mybotid;
		}

		void givelow (int botid) {
			mygivelow = botid;
		}

		void givehigh (int botid) {
			mygivehigh = botid;
		}

		bool operator < (const robot& str) const {
			return (mybotid < str.mybotid);
		}
};

// returns the vector position of a given botid.
int get_botinfo(vector <robot> robots, int botid) {
	for (int i = 0; i < robots.size(); i++) {
		if (robots[i].get_botid() == botid)
			return i;
	}
	return -1;
}

// adds a new bot to the back of the given vector.
int newbot(vector <robot> &robots, int botid) {
	robot myrobot;
	myrobot.set_botid(botid);
	robots.push_back(myrobot);
	return robots.size() - 1;
}

// gives a bot an item with a provided value
void linev(vector <robot> &robots, string line) {
	regex myregex("value (\\d*) goes to bot (\\d*)");
	smatch m;
	regex_match(line, m, myregex);
	if (m[0].matched == true) {
		int mybot = get_botinfo(robots, stoi(m[2]));
		if (mybot == -1) 
			mybot = newbot(robots, stoi(m[2]));
		if (robots[mybot].add_item(stoi(m[1])) == 0)
			cout << "could not add to bot" << endl;
	} else cout << "line did not match the regex" << line << endl;
}

// gives a bot instruction on what to do with low/high
void lineb(vector <robot> &robots, string line) {
	regex myregex("bot (\\d*) gives low to (bot|output) (\\d*) and high to (bot|output) (\\d*)");
	smatch m;
	regex_match(line, m, myregex);
	if (m[0].matched == true) {
		int mybot = get_botinfo(robots, stoi(m[1]));
		if (mybot == -1)
			mybot = newbot(robots, stoi(m[1])); 
		int givelow = stoi(m[3]);
		int givehigh = stoi(m[5]);
		if (m[2] == "output")
			givelow = givelow -1000;
		if (m[4] == "output")
			givehigh = givehigh -1000;
		robots[mybot].givelow(givelow); 
		robots[mybot].givehigh(givehigh);
	} else cout << "line did not match the regex" << line << endl;
}

// runtime loop, cycles through until the output boxes 0, 1, and 2 and filled.  Can change the test in the while loop.
// populates the outbox array via reference, and returns the robot that compares 61 and 17.
int runtime(int (&output)[30], vector <robot> &robots) {
	int partone = -1;
	int r = 0;
	while (output[0] == -1 or output[1] == -1 or output[2] == -1) {
		if (robots[r].check_compare(61, 17) == -1)
			partone = r;
		if (robots[r].get_itemcount() == 2) {
			int givelow = robots[r].get_givelow();
			int lowitem = robots[r].get_lowitem();
			int givehigh = robots[r].get_givehigh();
			int highitem = robots[r].get_highitem();

			if (givelow < -900) {
				int bin = givelow + 1000;
				output[bin] = lowitem;
			} else	if (robots[givelow].add_item(lowitem) == 0)
				cout << "could not give item " << lowitem << " to " << givelow << endl;


			if (givehigh < -900) {
				int bin = givehigh + 1000;
				output[bin] = highitem;
			} else if (robots[givehigh].add_item(highitem) == 0)
				cout << "could not give item " << highitem << " to " << givehigh << endl;

		}
		r++;
		if (r >= robots.size())
			r = r - robots.size();

	}
	return partone;
}

// reads the file and displays the answers, minimal logic here.
int main() {
	vector <robot> robots;
	int output[30] = {-1, -1, -1};
        ifstream myfile;
        string line;
        myfile.open("input.txt", ios::in);
        if (myfile.is_open()) {
                while ( getline (myfile,line) ) {
                        int n = line.length();
			if (line[0] == 'v')
				linev(robots, line);
			if (line[0] == 'b')
				lineb(robots, line);
		}
        myfile.close();
        }
        else cout << "Unable to open file";

	sort(robots.begin(), robots.end());
	cout << runtime(output, robots) << " is comparing 61 and 17." << endl;
	cout << output[0]*output[1]*output[2] << " is the product of bins 0, 1, and 2" << endl;
}


