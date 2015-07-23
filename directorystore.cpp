#include "directorystore.h"

void maindirectory::start_application(std::vector<std::string>& input) {
    if (input.size() != 2) {
    } else {
        dirpath = input.at(1);
    }
    //Check whether user input is valid directory.
    valid_directory = boost::filesystem::is_directory(dirpath);
}


void scaninputdirectory::scan_the_inputdirectory(maindirectory& input) {

    cur_dir = input.current_working_direct();
    // do some sanity check before doing final processing
    bool output = cur_dir.empty();
    if (output == true)
        return;
    recursive_directory_information();
}


bool scaninputdirectory::validate_each_node(fspath node) {
    std::string name = node.extension().generic_string();
    const size_t arrsize =5;
    boost::array <std::string, arrsize> arrextension = {".h",".c",".cpp",".hpp",".cxx"};
    std::string::size_type sz = 0;
    bool output;

    for(boost::array <std::string, arrsize>::iterator itr = arrextension.begin();
        itr != arrextension.end();
        ++itr) {

        sz = name.find(*itr);
        output = (sz != std::string::npos) && (name.size() == (*itr).size());
        if (output == true)
            break;
    }
    return output;
}



void scaninputdirectory::recursive_directory_information(void) {
    rdir_iterator rbgnitr(cur_dir);
    rdir_iterator renditr;
    for (rdir_iterator itr = rbgnitr; itr != renditr; ++itr) {
        if (validate_each_node(*itr)) {
            input_files.push_back(*itr);
        }
    }
}
