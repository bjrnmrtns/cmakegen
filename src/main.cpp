#include <experimental/filesystem>
#include <algorithm>
#include <string>
#include <sstream>
#include <iostream>

namespace fs = std::experimental::filesystem;

namespace {
    constexpr auto directories_of(const auto path, const std::vector<std::string>& matchto) {
        std::vector<fs::path> paths;
        const auto it = fs::directory_iterator(path);
        std::for_each(fs::begin(it), fs::end(it), [&paths, &matchto](const fs::path& p) {
                if(fs::is_directory(p)) {
                    if(std::any_of(std::cbegin(matchto), std::cend(matchto),
                            [&p](const auto& m) { return p.filename() == m; })) {
                        paths.push_back(p);
                    }
                }
        });
        return paths;
    }
    
    constexpr auto paths_with_extensions(const auto path, const std::vector<std::string>& extensions) {
        std::vector<fs::path> paths;
        const auto it = fs::directory_iterator(path);
        std::for_each(fs::begin(it), fs::end(it), [&paths, &extensions](const fs::path& p) {
                if(std::any_of(std::cbegin(extensions), std::cend(extensions),
                        [&p](const auto& e) { return p.extension() == e; })) {
                    paths.push_back(p);
                }
        });
        return paths;
    }
namespace cmake_literals {
    static const char* project_s = R"cmake(project()cmake";
    static const char* closing = R"cmake())cmake";
    static const char* add_library_s = R"cmake(add_library(${PROJECT_NAME})cmake";
}

    std::string create_cmake(const std::vector<fs::path>& files) {
        namespace cl = cmake_literals;
        std::ostringstream os;
        os << cl::project_s;
        os << "hoi";
        os << cl::closing << "\n";

        os << cl::add_library_s << "\n";
        for(const auto& file: files) {
            os << file << "\n";
        }
        os << cl::closing << "\n";
        return os.str();
    }
}

int main() {
    const auto root = fs::current_path();
    const auto paths = directories_of(root, {"cgame"});
    std::for_each(std::begin(paths), std::end(paths), [](const auto& path) {
        const auto paths = paths_with_extensions(path, {".c", ".h"});
        std::cout << create_cmake(paths) << "\n";
    });
}
