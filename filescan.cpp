#include "filescan.h"

const int count= 4;
std::array<std::pair<boost::regex, bool>, count> regularexpression = {
    std::make_pair(boost::regex("^\\s*$"), false),
    std::make_pair(boost::regex("^\\s*//"), false),
    std::make_pair(boost::regex("([\\s{0,}]?[/][*])"), false),
    std::make_pair(boost::regex("([\\s{0,}]?[*][/][\\s{0,}]?[\\W{0,}]?$)"), false)
};


fileinformation::fileinformation(std::string& input) {
    filehandle.open(input);
    if (!filehandle) {
        std::cerr << "Unable To Open The File:" << input << std::endl;
    }
    nlines = 0;
}

bool fileinformation::validate_lines_information(std::string& line) {
    boost::smatch matches;
    std::size_t index;

    bool output = false;
    bool slashstarcomment = false;
    static bool recursivecomment = false;

    static const int blankline = 0;
    static const int doublecomment = 1;
    static const int recursivestart = 2;
    static const int recursiveend = 3;

    for (index = 0; index < regularexpression.size(); ++index) {

        regularexpression[index].second = boost::regex_search(line, matches, regularexpression[index].first);

        if( ((index == blankline)&&(regularexpression[index].second == true))
                ||((index == doublecomment)&&(regularexpression[index].second == true)) )
        {
            output = true;
            goto reset;
        }

    }

    bool startflag = regularexpression.at(recursivestart).second;
    bool endflag  = regularexpression.at(recursiveend).second;

    slashstarcomment = startflag&&endflag;
    if(slashstarcomment == true)
    {
        output = true;
        goto reset;
    }


    if(recursivecomment == false)
    {
        recursivecomment = (startflag)&&(!endflag);
        if(recursivecomment == true)
        {
            output = true;
        }
    }
    else
    {
        output = true;
        if(endflag == true)
        {
            recursivecomment = false;
        }
    }



reset:
    for (index = 0; index < regularexpression.size(); ++index) {
        regularexpression[index].second = false;
    }

    return output;
}


long fileinformation::number_of_validlines() {
    std::string line;
    while (std::getline(filehandle, line)) {
        if (!validate_lines_information(line)) {
            nlines++;
        }
    }
    return nlines;
}

