#ifndef INIWRITER_H
#define INIWRITER_H
#include <iostream>
#include <fstream>


class INIWriter {
public:
    INIWriter();
    INIWriter(const std::string& filename);
    virtual ~INIWriter();
    void Open(const std::string& filename);

    void Close();

    void PutSection(const std::string& section);

    void PutValue(const std::string& key, const std::string& value);

    void PutComment(const std::string& comment);

    void PutBlankLine();
protected:
private:
    std::ofstream file;
};

#endif // INIWRITER_H
