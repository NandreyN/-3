#include <iostream>
#include <fstream>
#include <string>
#include <Windows.h>
#include <assert.h>
#include <vector>
#include <sstream>
#include <iterator>
#include <algorithm>
#include <set>
using namespace std;

void getIntersection(const vector<set<string>>& coll, set<string>& target)
{
	set<string> backup;
	assert(coll.size() > 0);
	backup = coll[0];

	for (auto i = 1; i < coll.size(); i++)
	{
		target.clear();
		set_intersection(coll[i].begin(), coll[i].end(), backup.begin(), backup.end(), inserter(target, target.begin()));
		backup = target;
	}
	target = backup;
}

struct FlowerBed
{
	FlowerBed(const string& str)
	{
		istringstream iss(str);
		iss >> id;
		iss >> shape;
		copy(istream_iterator<string>(iss), istream_iterator<string>(), back_inserter(types));
	}
	FlowerBed() {};
	int id;
	string shape;
	vector<string> types;
};
ostream& operator<<(ostream& o, const FlowerBed& fb)
{
	o << fb.id << " " << fb.shape << " ";
	copy(fb.types.begin(), fb.types.end(), ostream_iterator<string>(o, " ")); o << endl;
	return o;
}

istream& operator>>(istream& o, FlowerBed& fb)
{
	string a;
	getline(o, a);
	fb = FlowerBed(a);
	return o;
}

int main()
{
	ifstream in("in.txt");
	assert(in.is_open());

	vector<FlowerBed> flbeds;
	// <task 1>
	istream_iterator<FlowerBed> iterBgn(in) , currIter;
	
	copy(iterBgn, currIter, back_inserter(flbeds));	
	in.close();

	// sort by shape
	cout << endl << "Sorted by shape : " << endl;
	sort(flbeds.begin(), flbeds.end(), [](auto s1, auto s2) {return s1.shape < s2.shape; });
	copy(flbeds.begin(), flbeds.end(), ostream_iterator<FlowerBed>(cout , "\n"));
	// 4 a,b
	//a)вывести список различных форм для клумб;
	//b)вывести список всех цветов указанной клум - бы;
	set<string> shapes;
	for_each(flbeds.begin(), flbeds.end(), [&shapes](auto s) {shapes.insert(s.shape); });
	cout << endl << "Shapes : "; copy(shapes.begin(), shapes.end(), ostream_iterator<string>(cout, " , "));

	int flwbdId;
	cout << endl << "Input req. flowerbed id : ";
	cin >> flwbdId;

	vector<FlowerBed>::iterator iter = find_if(flbeds.begin(), flbeds.end(), [flwbdId](auto s) {return s.id == flwbdId; });
	assert(iter != flbeds.end());
	cout << endl << "All flowers at " << flwbdId << " : ";
	copy((*iter).types.begin(), (*iter).types.end(), ostream_iterator<string>(cout, " ")); cout << endl;


	// 5ad
	// a)найти клумбу с указанным количеством цветов.
	int reqFlCount;
	cout << endl << "Input req. flowers count : ";
	cin >> reqFlCount; cout << endl;

	iter = find_if(flbeds.begin(), flbeds.end(), [reqFlCount](auto s) {return s.types.size() == reqFlCount; });
	assert(iter != flbeds.end());
	cout << "Id : " << (*iter).id << endl;

	//d)найти цветок, растущий на всех клумбах
	vector<set<string>> typesCollection;
	for_each(flbeds.begin(), flbeds.end(), [&typesCollection](const FlowerBed& flb)
	{
		set <string> st;
		copy(flb.types.begin(), flb.types.end(), inserter(st, st.begin()));
		typesCollection.push_back(st);
	});
	set<string> intersection;
	getIntersection(typesCollection, intersection);
	cout << endl << "Att all flowerbeds : ";
	copy(intersection.begin(), intersection.end(), ostream_iterator<string>(cout, " "));

	// a)	подсчет числа различных форм;
	cout << endl <<  "Shapes count : "; cout << shapes.size() << endl;
	// d)	поиск клумбы с наибольшим количеством цветков
	iter = max_element(flbeds.begin(), flbeds.end(), [](auto s1, auto s2) {return s1.types.size() < s2.types.size(); });
	cout << endl << "Largest , id = " << (*iter).id << endl;

	// b)	подсчет числа различных цветков;
	set<string> flowers;
	for_each(flbeds.begin(), flbeds.end(), [&flowers](FlowerBed& fb)
	{
		flowers.insert(fb.types.begin(), fb.types.end());
	});
	cout << endl << "Unique flowers : ";
	cout << flowers.size() << endl;
	return 0;
}