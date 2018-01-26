// Last Update:2017-12-19 10:54:31
/**
 * @file word_count.cpp
 * @brief 
 * @author luxueqian
 * @version 0.1.00
 * @date 2017-12-19
 */
#include <vector>
#include <string>
#include <algorithm>
#include <iostream>
using namespace std;
bool isShorter(const string &s1, const string &s2)
{
    return s1.size() < s2.size();
}

bool GT6(const string &s)
{
    return s.size() >= 6;
}

void print_vec(vector<string>::iterator begin, vector<string>::iterator end)
{
    for(begin; begin != end; begin++)
    {
        cout<< *begin << " ";
    }
    cout<<endl;
}


int main(int argc, char *argv[])
{
    vector<string> words;
    const char *array[] = {"the",
                   "quick",
                   "red",
                   "fox",
                   "jumps",
                   "over",
                   "the",
                   "slow",
                   "red",
                   "turtle"};
    for(int i = 0; i < sizeof(array)/sizeof(char*); i++)
    {
        words.push_back(array[i]);
    }

//    string next_word;
//    while(cin >> next_word)
//        words.push_back(next_word);

    print_vec(words.begin(), words.end());

    sort(words.begin(), words.end());
    print_vec(words.begin(), words.end());

    vector<string>::iterator end_unique = unique(words.begin(), words.end());
    print_vec(words.begin(), words.end());
    print_vec(end_unique, words.end());

    words.erase(end_unique, words.end());
    print_vec(words.begin(), words.end());

    stable_sort(words.begin(), words.end(), isShorter);
    print_vec(words.begin(), words.end());
    vector<string>::size_type wc = count_if(words.begin(), words.end(), GT6);
    cout<<wc << " "<< "words" << "6 characters or longer" <<endl;

    return 0;
}
