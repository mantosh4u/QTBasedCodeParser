#ifndef FILEINFORMATION_H
#define FILEINFORMATION_H

#include <string>
#include <iostream>
#include <fstream>
#include <boost/regex.hpp>
#include <boost/array.hpp>


class fileinformation {
public:
    fileinformation(std::string& input);
    long number_of_validlines();
private:
    bool validate_lines_information(std::string& line);
    std::ifstream filehandle;
    long nlines;
};



#endif // FILEINFORMATION_H
