#include "wordfrequency.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>
/**
* Assignment 3 for COSE213 Data Structures
*
* Won-Ki Jeong (wkjeong@korea.ac.kr)
*
* 2021. 5. 9
*
*/

WordFrequency::WordFrequency()
{
	// ToDo
	map = new WordFreqMap;
}

WordFrequency::~WordFrequency()
{
	// ToDo
	delete map;
}

void WordFrequency::ReadText(const char* filename)
{
	// ToDo
	delete map;
	map = new WordFreqMap;

	using namespace std;
	ifstream fi(filename);
	string s;
	if (fi.is_open()) {

		while (getline(fi, s)) {
			// s : input string
			istringstream iss(s);
			do
			{
				string sub, sub_2;
				iss >> sub;
				transform(sub.begin(), sub.end(), sub.begin(), ::tolower);
				for (unsigned int i = 0; i < sub.length(); i++) {
					if (sub[i] >= 'a' && sub[i] <= 'z') {
						sub_2 += sub[i];
					}
					else {
						if (sub_2 == "") continue;
						WordFreqElem* u = map->find(sub_2);
						if (u == NULL) map->insert(sub_2, 1);
						else map->insert(sub_2, (u->val) + 1);
						sub_2 = "";
					}
				}
				if (sub_2 == "") continue;
				WordFreqElem* k = map->find(sub_2);
				if (k == NULL) map->insert(sub_2, 1);
				else map->insert(sub_2, (k->val) + 1);

			} while (iss);
		}

		fi.close();
	}
	else return;
}

int WordFrequency::GetFrequency(const std::string word)
{
	// ToDo
	WordFreqElem* k = map->find(word);
	if (k != NULL) {
		return k->val;
	}
	else return 0;
}

void WordFrequency::IncreaseFrequency(const std::string word)
{
	// ToDo
	WordFreqElem* k = map->find(word);
	if (k == NULL) map->insert(word, 1);
	else map->insert(word, (k->val) + 1);
}