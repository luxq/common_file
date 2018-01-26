// Last Update:2017-12-19 15:56:50
/**
 * @file textquery.h
 * @brief 
 * @author luxueqian
 * @version 0.1.00
 * @date 2017-12-19
 */

#ifndef TEXTQUERY_H
#define TEXTQUERY_H
#include <iostream>
#include <string>
#include <set>
#include <vector>
#include <map>

class TextQuery {
    public:
        typedef std::vector<std::string>::size_type line_no;

        void read_file(std::ifstream &is)
        {
            store_file(is);
            build_map();
        }

        std::set<line_no> run_query(const std::string& word) const;
        std::string text_line(line_no) const;
    private:
        void store_file(std::ifstream&);
        void build_map();

        std::vector<std::string> lines_of_text;
        std::map<std::string, std::set<line_no> > word_map;
};


#endif  /*TEXTQUERY_H*/
