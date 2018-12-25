#include <cstdio>
#include <iostream>
#include <memory>
#include <stdexcept>
#include <string>
#include <array>
#include <string>
#include <vector>
#include <algorithm>

#include <gtkmm/application.h>

#include <boost/filesystem.hpp>
#include <boost/filesystem/path.hpp>

#include "MainWindow.h"

#define MAX_FILES 100

namespace fs = boost::filesystem;

std::string exec(const char *cmd) {
    std::array<char, 128> buffer{};
    std::string result;
    std::unique_ptr<FILE, decltype(&pclose)> pipe(popen(cmd, "r"), pclose);
    if (!pipe) {
        throw std::runtime_error("popen() failed!");
    }
    while (fgets(buffer.data(), buffer.size(), pipe.get()) != nullptr) {
        result += buffer.data();
    }
    return result;
}

int main(int argc, char *argv[]) {

    fs::path p(fs::initial_path<fs::path>());
    unsigned int cnt{0};
    fs::directory_iterator end_iter;

    std::vector<std::pair<int, std::string>> v;

    // Count number of items in directory
    for (fs::directory_iterator dir_itr(p); dir_itr != end_iter; ++dir_itr) {
        std::stringstream tmp = std::stringstream(exec(("du -s '" + dir_itr->path().string() + "'").c_str()));

        int length;
        std::string path;
        tmp >> length;
        std::getline(tmp, path);
        fs::path tmp_path(path);

        ++cnt;
        v.emplace_back(std::make_pair(length, tmp_path.filename().string()));
    }

    // Descending order
    std::sort(v.rbegin(), v.rend());

    for (auto i:v) {
        std::cout << i.first << " " << i.second << std::endl;
    }


    if (cnt > MAX_FILES) {
        std::cout << "Limiting to biggest " << MAX_FILES << " files/dirs." << std::endl;
    }

    if (argc > 1 && !strcmp(argv[1], "--no-gui")) {
        std::cout << "No GUI, sorting " << std::endl;
        std::string ret = exec("du -sh -- *;");
        std::cout << ret << std::endl;
        return 0;
    }

    // Set up GUI
//    auto app = Gtk::Application::create(argc, argv);
//    MainWindow window;
//    window.set_default_size(200, 200);
//    app->run(window);
    return 0;
}