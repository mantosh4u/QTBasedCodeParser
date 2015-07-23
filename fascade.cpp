#include "fascade.h"

codeparser::codeparser(std::vector<std::string>& input) {
    maindirectory dirobject;
    dirobject.start_application(input);
    scaninputdirectory inputdir;
    inputdir.scan_the_inputdirectory(dirobject);
    files = std::move(inputdir.get_files_list());

    total_lines = 0;
}

void codeparser::start_execution(void) {
    for(std::vector<fspath>::iterator itr = files.begin(); itr != files.end(); ++itr) {
        std::string node = (*itr).generic_string();
        fileinformation file(node);
        long long output = file.number_of_validlines();
        filesinfo[node] = output;
    }
}


struct AccumlateLines {
    AccumlateLines():sum(0) { }
    void operator() (std::map<std::string ,long long>::value_type val)  {
        sum += (val).second;
    }
    long long sum;
};


long long codeparser::total_valid_line() const {
    AccumlateLines out = std::for_each(filesinfo.begin(), filesinfo.end(), AccumlateLines());
    return out.sum;
}


void codeparser::display_files_info()  {
    for(std::map<std::string ,long long>::iterator itr = filesinfo.begin();
        itr != filesinfo.end();
        ++itr) {
        std::cout<<(*itr).first<<"\t"<<(*itr).second<<"\n";
    }
}
