#include <iostream>
#include <fstream>
#include <openssl/md5.h>
#include <openssl/evp.h>
#include <cstdio>
#include <string>

using namespace std;

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

int main() {
	string password = "";
	string input = "ojvtpuvg";
	int chars = 0;
	char arr[8] = {'-','-','-','-','-','-','-','-'};
	for (int i = 0; chars < 8; i++) { 
		string mymd5 = md5(input + to_string(i));
		char pass2char = mymd5[5];
		int pass2pos = pass2char - '0';
		int password2 = 0;
		if (pass2pos < 8 and pass2pos > -1)
			if (arr[pass2pos] == '-')
				password2 = 1;
		if (mymd5.substr(0,5) == "00000" and password.length() < 8)
			password = password + mymd5.substr(5,1);
		if (mymd5.substr(0,5) == "00000" and password2 == 1 ) {
			arr[pass2pos] = mymd5[6];
			chars++;
			for (int i = 0; i < 8; i++) {
				if (arr[i] == -1) {
					cout << "_";
				} else {
					cout << arr[i];
				}
			}
			cout << endl;
		}
	}
	cout << "First password: " << password << endl;
	cout << "Second password: ";
	for (int i = 0; i < 8; i++)
		cout << arr[i];
	cout << endl;
	return 0;
}
