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

#include "du_comp.h"
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

    unsigned int cnt{0};
    std::vector<std::string> du{};

    if (argc > 1 && !strcmp(argv[1], "--use-du")) {
        std::cout << "No GUI, sorting with du:" << std::endl;

        std::stringstream ret = std::stringstream(exec("du -sh -- *;"));
        std::string line;
        while (std::getline(ret, line)) {
            du.push_back(line);
            ++cnt;
        }

        std::sort(du.rbegin(), du.rend(), du_comp());

        for (auto i:du) {
            std::cout << i << std::endl;
        }

        return 0;
    }


    fs::path p(fs::initial_path<fs::path>());
    fs::directory_iterator end_iter;

    // Trying out boost to count items in directory
    for (fs::directory_iterator dir_itr(p); dir_itr != end_iter; ++dir_itr) {
        ++cnt;
    }

    if (cnt > MAX_FILES) {
        std::cout << "Limiting to biggest " << MAX_FILES << " files/dirs." << std::endl;
    }

    // Set up GUI
//    auto app = Gtk::Application::create(argc, argv);
//    MainWindow window;
//    window.set_default_size(200, 200);
//    app->run(window);
    return 0;
}