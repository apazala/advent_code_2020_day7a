#include <cstdio>
#include <unordered_map>
#include <unordered_set>
#include <vector>

#include <iostream>
#include <string>
#include <regex>

using namespace std;

char line[1024];
int main() {
	FILE *fin = fopen("input.txt", "r");
	if (!fin) {
		fprintf(stderr, "Can't open input\n");
		return 1;
	}

	unordered_map<string, vector<string>> contained_map;

	std::regex container_splitter(" bags contain");
	std::regex contents_splitter(" bags?[\\.,]");
	std::regex bag_quant_name_re("\\s*(\\d+) (.*)");


	// default constructor = end-of-sequence:
	std::regex_token_iterator<std::string::iterator> rend;

	while (fgets(line, sizeof(line), fin)) {
		string s(line);
		std::regex_token_iterator<std::string::iterator> a(s.begin(), s.end(), container_splitter, -1);
		string container(a->str());
		//cout << "[" << a->str() << "]" << endl;
		a++;
		string s1(a->str());
		std::regex_token_iterator<std::string::iterator> b(s1.begin(), s1.end(), contents_splitter, -1);
		
		for (; b != rend; b++) {
			string s2(b->str());

			std::regex_token_iterator<std::string::iterator> c(s2.begin(), s2.end(), bag_quant_name_re, 2);
			if (c != rend) {
				string content(c->str());

				contained_map[content].push_back(container);

				//cout << "(" << c->str() << ")" << endl;
			}
				
		}
	}
	fclose(fin);

	unordered_set<string> visited;

	int count = 0;

	vector<string> remain;

	string last_str("shiny gold");
	remain.push_back(last_str);
	visited.insert(last_str);

	while (!remain.empty()) {
		last_str = remain.back();
		remain.pop_back();

		auto it = contained_map.find(last_str);
		if (it != contained_map.end()) {
			for (string &s : it->second) {
				if (visited.insert(s).second) {
					count++;
					remain.push_back(s);
				}
			}
		}
	}

	cout << count << endl;

	return 0;
}