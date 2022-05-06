#include <fstream>
#include <filesystem>
#include <iostream>

namespace fs = std::filesystem;

constexpr char dir[] = "resolved/";

void iterate_files(std::string pathStr);
void _iterate_files(fs::path path);
void copy_file(fs::path origin);

void iterate_files(std::string pathStr) {
	// TODO: create parent dirs when creating files
	if (!fs::exists(dir)) {
		fs::create_directory(dir);
	} else {
		// bug in gcc, workaround
		// TODO: move to vs2019 to check if it works there idk
		fs::remove_all(dir);
		fs::create_directory(dir);
	}
	fs::path path(pathStr);
	_iterate_files(path);
}

void copy_file(std::filesystem::path origin) {
	// std::cout << origin.extension().string() << "\n";       
	fs::path dest("resolved/" + origin.string());

	fs::copy_file(origin, dest, fs::copy_options::update_existing);
}

void _iterate_files(fs::path path) {
	if (!fs::exists(dir + path.string())) {
		fs::create_directory(dir + path.string());
	}
	for (const auto& entry : fs::directory_iterator(path)) {
		std::cout << entry.path().string() << "\n";
		if (entry.is_directory()) {
			_iterate_files(entry.path());
		} else {
			copy_file(entry.path());
		}
	}
}

int main(int argc, char** argv)
{
	if (argc < 2) {
		std::cout << "usage: .\\" << argv[0] << " template" << std::endl;
		return 0;
	}
	iterate_files(argv[1]);
	return 0;
}