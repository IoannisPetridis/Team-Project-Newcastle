#include <fstream>
#include <vector>
#include <string>

std::vector<int> ConfigFileLoader(std::string filename) {
	std::vector<int> SettingList;
	std::ifstream f(filename.c_str(), std::ios::in);
	if (f) {
		while (!f.eof()) {
			int key_value;
			std::string dump;
			f >> dump;	//no name matching, just dump the first column
			f >> dump;	//dump the = 
			f >> key_value; //retrive the setting value
			SettingList.push_back(key_value);
		}
	}
	f.close();
}

