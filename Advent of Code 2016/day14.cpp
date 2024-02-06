#include <iostream>
#include <fstream>
#include <openssl/md5.h>
#include <openssl/evp.h>
#include <cstdio>
#include <string>
#include <vector>
#include <tuple>

using namespace std;


// uses crypto library to generate md5 hash.  -lcrypto
string md5(const string& content)
{
  EVP_MD_CTX*   context = EVP_MD_CTX_new();
  const EVP_MD* md = EVP_md5();
  unsigned char md_value[EVP_MAX_MD_SIZE];
  unsigned int  md_len;
  string        output;

  EVP_DigestInit_ex2(context, md, NULL);
  EVP_DigestUpdate(context, content.c_str(), content.length());
  EVP_DigestFinal_ex(context, md_value, &md_len);
  EVP_MD_CTX_free(context);

  output.resize(md_len * 2);
  for (unsigned int i = 0 ; i < md_len ; ++i)
    std::sprintf(&output[i * 2], "%02x", md_value[i]);
  return output;
}

// find any md5s with three matches
char triplematch(string mymd5) {

	for (int i = 0; i < mymd5.length()-2; i++)
		if (mymd5[i] == mymd5[i+1] and mymd5[i] == mymd5[i+2])
			return mymd5[i];

	return 0;

}

// check a provided md5 for a sequence of five identical characters (char provided)
int fivematch(string mymd5, char mychar) {

	for (int i = 0; i < mymd5.length()-4; i++)
		if (mymd5[i] == mychar and mymd5[i+1] == mychar and mymd5[i+2] == mychar and mymd5[i+3] == mychar and  mymd5[i+4] == mychar)
			return 1;

	return 0;

}

// get the md5 to insert in the vector.  Could be from the provided string, or stretched by recomputing an additional 2016 times.  
string getmd5(string input, int i, int times) {
	string mymd5 = md5(input + to_string(i));
	for (int j = 0; j < times - 1; j++)
		mymd5 = md5(mymd5);
	return mymd5;
}

// main logic.  Generate 1000 md5s to start.  each iteration, generation one more at the end, then check the current iterator for three in a row, if found, check the next 1000 for five in a row.
int findmatches(string input, int times) {
	vector <string> md5s;
	int matches = 0;

	int thismd5 = 0;

	for (int i = 0; i < 1000; i++)
		md5s.push_back(getmd5(input, i, times));

	while (matches < 64) {
		md5s.push_back(getmd5(input, thismd5+1000, times));
		char mychar = triplematch(md5s[thismd5]);
		if (mychar != 0)
			for (int j = thismd5 + 1; j < thismd5 + 1001; j++)
				if (fivematch(md5s[j], mychar) == 1) {
					matches++;
					j = thismd5 + 1001;
				}
		if (matches == 64)
			return thismd5;
		thismd5++;
	}
	return 0;
}

int main() {
	string input = "ihaygndm";
//	string input = "abc";
	int partone = findmatches(input, 1);
	cout << "Part One: " << partone << endl;
	int parttwo = findmatches(input, 2017);
	cout << "Part Two: " << parttwo << endl;


	return 0;
}
