#ifndef DIRECTORYSTORE_H
#define DIRECTORYSTORE_H

#include <vector>
#include <string>
#include <algorithm>
#include <iterator>

#include <boost/array.hpp>
#include <boost/filesystem.hpp>
typedef boost::filesystem::path							   fspath;
typedef boost::filesystem::recursive_directory_iterator    rdir_iterator;


class maindirectory {
public:
    maindirectory(): valid_directory(false) {}
    ~maindirectory() {}
    void start_application(std::vector<std::string>& input);
    inline fspath current_working_direct() const {return dirpath;}
private:
    fspath dirpath;
    bool valid_directory;
};


class scaninputdirectory {
public:
    scaninputdirectory() {}
    ~scaninputdirectory(){}
    void scan_the_inputdirectory(maindirectory& input);
    std::vector<fspath> get_files_list(void) { return input_files;}
private:
    void recursive_directory_information();
    bool validate_each_node(fspath node);
    std::vector<fspath> input_files;
    fspath cur_dir;
};

#endif
// DIRECTORYSTORE_H
