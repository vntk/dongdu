/*
 * SylMap.cpp
 *
 *  Created on: 2012/09/19
 *      Author: anh
 */

#include "SylMap.h"

namespace std {

SylMap::SylMap(string path)
{
	_syl.clear();

	string dataFile = path + "/data/VNsyl.txt";
	ifstream ifs(dataFile);

	if (!ifs) {
		cout << "Failed to open file:" << dataFile << endl;
		return;
	}

	int N;
	ifs >> N;

	string str;
	for(int i = 0; i < N; ++i) {
		ifs >> str;
		_syl.insert(str);
	}

	return;
}

SylMap::~SylMap() {
	_syl.clear();
}

bool SylMap::isVNESE(string syllabel)
{
	set<string>::iterator it;
	it = _syl.find(syllabel);
	return (it != _syl.end());
}

} /* namespace std */
