#ifndef CODEPARSER_H
#define CODEPARSER_H

#include "directorystore.h"
#include "filescan.h"
#include <map>
#include <vector>
#include <string>

class codeparser {
public:
    codeparser(std::vector<std::string>& input);
    ~codeparser() {}
    void start_execution(void);
    long long total_valid_line() const;
    void display_files_info();
    std::map<std::string ,long long> filesinfo;
private:
    long long total_lines;
    std::vector<fspath> files;
};

#endif
// CODEPARSER_H
