#include "DicMap.h"

using namespace std;

DicMap::DicMap(string path)
{
	string dataFile = path + "/data/wordlist.txt";
	ifstream ifs(dataFile);
	if (!ifs) {
		cout << "Failed to open file wordlist.txt" << endl;
		cout << "Please check: " << dataFile << endl;
		return;
	}
	string str;

	while(ifs && getline(ifs,str)) {
		dmap_.insert(pair<string, int> ( str , 1));
	}

	return;
}

DicMap::~DicMap()
{
	dmap_.clear();
	return;
}

bool DicMap::isWord(const string str)
{
	map<string, int>::iterator pos = dmap_.find(str);
	return (pos != dmap_.end());
}
