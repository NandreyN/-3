#include <iostream>
#include <fstream>
#include <string>
#include <Windows.h>
#include <stdio.h>
#include <assert.h>
#include <vector>
#include <sstream>
#include <string>
using namespace std;

void split(const string& data, vector<string>& target)
{
	istringstream iss(data);
	while(iss)
	{
		string a; iss >> a;
		target.push_back(a);
	}
}

int main()
{
	ifstream in("in.txt");
	assert(in.is_open());

	vector<string> additional;

	while(in)
	{
		string str;

	}
	in.close();
	return 0;
}