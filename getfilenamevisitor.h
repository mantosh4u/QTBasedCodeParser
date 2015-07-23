#ifndef GETFILENAMEVISITOR
#define GETFILENAMEVISITOR

#include <boost/filesystem.hpp>
#include <string>

typedef boost::filesystem::path fspath;

std::string filename_from_path(std::string& completename){
  fspath tmp(completename);
  tmp = tmp.filename();
  return tmp.string();
}

#endif // GETFILENAMEVISITOR
