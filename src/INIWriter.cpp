#include "../include/INIWriter.h"

INIWriter::INIWriter() {
    //ctor
}

INIWriter::~INIWriter() {
    //dtor
}

void INIWriter::Open(const std::string& filename) {
    file.open(filename);
    file.clear();
}

void INIWriter::Close() {
    file.close();
}

void INIWriter::PutSection(const std::string& section) {
    file << "[" << section << "]" << std::endl;
}

void INIWriter::PutValue(const std::string& key, const std::string& value) {
    file << key << "=" << value << std::endl;
}

void INIWriter::PutComment(const std::string& comment) {
    file << "# " << comment << std::endl;
}

void INIWriter::PutBlankLine() {
    file << std::endl;
}
