// Last Update:2017-12-19 16:27:56
/**
 * @file textquery.cpp
 * @brief 
 * @author luxueqian
 * @version 0.1.00
 * @date 2017-12-19
 */

#include <iostream>
#include <fstream>
#include <sstream>
#include "textquery.h"
using namespace std;


void TextQuery::store_file(ifstream &is)
{
    string textline;
    while(getline(is, textline))
        lines_of_text.push_back(textline);
}

void TextQuery::build_map()
{
    for(line_no line_num = 0; line_num != lines_of_text.size(); line_num++)
    {
        istringstream line(lines_of_text[line_num]);
        string word;
        while (line >> word)
            word_map[word].insert(line_num);
    }
}

set<TextQuery::line_no> TextQuery::run_query(const string &word) const
{
    map<string, set<line_no> >::const_iterator it = word_map.find(word);
    if(it == word_map.end())
        return set<line_no> ();
    else
        return it->second;
}

string TextQuery::text_line(line_no line) const
{
    if (line < lines_of_text.size())
        return lines_of_text[line];
    else
        return "";
}

void print_results(set<TextQuery::line_no> &locs, string &s, TextQuery &tq)
{
    typedef set<TextQuery::line_no> line_nums;
    line_nums::size_type size = locs.size();
    cout << "\n" << s << " occurs " << size << " times"<< endl;

    line_nums::iterator it = locs.begin();
    for(; it != locs.end(); it++)
    {
        cout << "\t(line " 
            << (*it) + 1 << ") "
            << tq.text_line(*it) << endl;
    }
}

int main(int argc, char *argv[])
{
    ifstream infile;
    if(argc < 2)
    {
        cerr << "No input file!"<<endl;
        return -1;
    }
    infile.open(argv[1], ios::in);

    TextQuery tq;
    tq.read_file(infile);

    while(true)
    {
        cout << "enter word to look for, or q to quit: ";
        string s;
        cin >> s;
        if(!cin || s=="q") break;
        set<TextQuery::line_no> locs = tq.run_query(s);
        print_results(locs, s, tq);
    }
    
    return 0;
}
