#include <iostream>
#include <string>
#include <sstream>
using namespace std;

// checksum logic starts at second position, goes by twos, and checks the position and the previous position to see if they match.
// a stringstream is used for speed.
string getchecksum(string a) {
    stringstream checksum;
    for (int i = 1; i < a.length(); i = i + 2) {
        if (a[i] == a[i - 1]) {
            checksum << '1';
        }
        else checksum << '0';       
    }
    a = "";
    checksum >> a;
    return a;
}

// builds the data using a stringstream for speed.  Logic should be easy to follow, i opted to go through a backwards to build b.
// screen output in this sub, i used only a portion of the produced string for the output since we ended up not needing it anyway.
void getdata(string a, int disk) {
    while (a.length() < disk) {
        string b = "";
        stringstream bstream;
        for (int i = 0; i < a.length(); i++)
            bstream << char(((a[a.length() - 1 - i] - '1') * -1) + '0');
        bstream >> b;
        a = a + '0' + b;
    }

    string checksum = a.substr(0, disk);
    cout << "Data (" << checksum.length() << "): " << checksum.substr(0, 100) << "..." << endl;
    while (checksum.length() % 2 == 0 and checksum.length() > 0)
        checksum = getchecksum(checksum);
    cout << "Checksum: " << checksum << endl;
}

int main() {
    string input = "10011111011011001";

    getdata(input, 272);
    getdata(input, 35651584);
}
