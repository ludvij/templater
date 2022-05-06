#include <regex>
#include <fstream>
#include <iostream>





int main() {
	std::string file_path = "templates/uniovi/eii/latex/sections/title.tex.templ";

	std::ifstream file(file_path);

	std::string line;
	while (std::getline(file, line))
	{
		std::regex pattern(
			"(?<=\\[% )(.*)(?= %\\])"
		);
		std::smatch m;
		if (std::regex_search(line, m, pattern, std::regex_constants::match_prev_avail)) {
			for (auto x:m) {
				std::cout << x << std::endl;
			}
		}
	}
}