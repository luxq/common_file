// Last Update:2017-12-07 09:19:00
/**
 * @file pcre_test.cpp
 * @brief 
 * @author luxueqian
 * @version 0.1.00
 * @date 2017-12-04
 */
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <sys/types.h>
#include <pcre.h>
#include <pcrecpp.h>
#include <string>
#include <vector>
#include <iostream>
using namespace std;
using pcrecpp::RE;
struct timeval starttime;
struct timeval endtime;

#define PROFILE_START \
	gettimeofday(&starttime, NULL);

#define PROFILE_END \
	gettimeofday(&endtime, NULL);\
	cout<<"cost time = "<<(endtime.tv_sec * 1000000 + endtime.tv_usec - (starttime.tv_sec*1000000 + starttime.tv_usec))/1000 <<"ms"<<endl;\

#if 0
int main(int argc, char *argv[])
{
    
    //FullMatch
    RE re("h.*o");
    bool result = false;
    result = re.FullMatch("hello");
    cout<<"re.FullMatch(hello)=="<<result<<endl;
    int i;
    string s;
    string num;
    RE n("(\\w+):(\\d+)");
    n.FullMatch("ruby:1234", &s, &num);
    cout<<"get s="<<s<<", num="<<num<<endl;

    //quotemeta
    string unquoted = "1.5 - 2.0";
    string quoted = RE::QuoteMeta(unquoted);
    cout<<"unquoted="<<unquoted<<", quoted ="<<quoted<<endl;

    //parital matches 
    cout<<"partialMatch="<<RE("ell").PartialMatch("hello")<<endl;
    int num1 = 0,num2=0;
    RE m("(\\d+)");
    m.PartialMatch("1+2+3+4", &num1);
    cout<<"match num1="<<num1<<endl;
    RE p("(\\d+).(\\d+)");
    p.PartialMatch("1+2+3+4", &num1, &num2);
    cout<<"match num1="<<num1<<", num2="<<num2<<endl;

    //Consume
    string contents = "k1=10\nk2=20\nk3=30\nk4=40\n";
    string s_val;
    int i_val;
    pcrecpp::StringPiece input(contents);
    RE c("(\\w+)=(\\d+)\n");
    while(c.Consume(&input, &s_val, &i_val))
    {
        cout<<"consume get "<<s_val<<"="<<i_val<<endl;
    }
    //FindAndConsume
    RE f("(\\w+)");
    pcrecpp::StringPiece nin(contents);
    while(c.Consume(&nin, &s_val))
    {
        cout<<"consume get "<<s_val<<endl;
    }

    //Octal,Hex,CRadix,
    int a, b, l, d;
    pcrecpp::RE nre("(.*) (.*) (.*) (.*)");
    nre.FullMatch("100 40 0100 0x40",
            pcrecpp::Octal(&a), pcrecpp::Hex(&b),
            pcrecpp::CRadix(&l), pcrecpp::CRadix(&d));
    cout<<a<<" "<<b<<" "<<l<<" "<<d<<endl;

    //Replace 
    string ss = "yabba dabba doo";
    int rep_num = 0;
    // only replace once.
    rep_num = RE("b+").Replace("d", &ss);
    cout<<"Replace num="<<rep_num<<",result="<<ss<<endl;
    // only replace once.
    ss = "yabba dabba doo";
    RE("b+").GlobalReplace("d", &ss);
    cout<<"Replace num="<<rep_num<<",result="<<ss<<endl;

    RE sre("(.)(.)\\2\\1");
    result = sre.FullMatch("abba");
    cout<<"FullMatch(abba)= "<<result<<endl;
    result = sre.FullMatch("abaa");
    cout<<"FullMatch(abaa)= "<<result<<endl;

    return 0;
}
#endif

std::string random_ipv4()
{
    // rand() is perfectly fine for this use case
    // coverity[dont_call]
    char ip[16] = {0};
    int ip_int = rand();
    unsigned char *bytes = (unsigned char*)&ip_int;

    snprintf(ip, 16, "%u.%u.%u.%u",
            *bytes, *(bytes + 1), *(bytes + 2), *(bytes + 3));
    return string(ip);
}
#include <regex.h>
bool pcre_match_text(pcre *re, string pattern, const char *content)
{
    //return re.FullMatch(ip);
    int ovector[30];
    int rc = pcre_exec(re, NULL, content, strlen(content), 0, 0, ovector, 30);
    return (rc > 0 ? true : false);
}
bool pcre_match_text(RE &re, string pattern, const char *content)
{
    //return re.FullMatch(ip);
    return re.PartialMatch(content);
}
bool regex_match_text(regex_t *reg, string pattern, const char *content)
{
    int status;
    regmatch_t pmatch[1];
    const size_t nmatch = 1;
    status = regexec(reg, content, nmatch, pmatch, 0);
    return (status == 0) ? true: false;
}
bool pcre_match_ip(RE &re, string pattern, string ip)
{
    //return re.FullMatch(ip);
    return re.PartialMatch(ip);
}

bool regex_match_ip(regex_t *reg, string pattern, string ip)
{
    int status;
    regmatch_t pmatch[3];
    const size_t nmatch = 3;
    status = regexec(reg, ip.c_str(), nmatch, pmatch, 0);
    return (status == 0) ? true: false;
}
void profile_test()
{
    regex_t reg;
    bool ret;
    int cflags = REG_EXTENDED;
    int i = 0;
    //string pattern = "^(?:[0-9]{1,3}\\.){3}[0-9]{1,3}$";
    //string pattern = "^((25[0-5]|2[0-4]\\d|[01]?\\d\\d?)($|(?!\\.$)\\.)){4}$";
    //string pattern = "^103.*";
    //string pattern = "((25[0-5]|2[0-4]\\d|1\\d\\d|[1-9]\\d|\\d)\\.){3}(25[0-5]|2[0-4]\\d|1\\d\\d|[1-9]\\d|[1-9])";
    //string pattern = "((25[0-5]|2[0-4]\d|1\d\d|[1-9]\d|\d)\.){3}(25[0-5]|2[0-4]\d|1\d\d|[1-9]\d|[1-9])";
    string pattern = "((25[0-5]|2[0-4][0-9]|1[0-9][0-9]|[1-9][0-9]|[0-9])\\.){3}(25[0-5]|2[0-4][0-9]|1[0-9][0-9]|[1-9][0-9]|[1-9])";

    regcomp(&reg, pattern.c_str(), cflags);
    RE re(pattern);
    vector<string> vec_ip;
    for(i=0; i < 100000; i++)
    {
        vec_ip.push_back(random_ipv4());
    }
    int count = 0;
    PROFILE_START
    for(i=0; i < 100000; i++)
    {
        ret = pcre_match_ip(re, pattern, vec_ip[i]);
        
        if(ret)
        {
            count++;
            //cout<<vec_ip[i]<<endl;
        }
    }
    PROFILE_END
    cout<<"count = "<<count<<endl;

    count = 0;
    PROFILE_START
    for(i=0; i < 100000; i++)
    {
        ret = regex_match_ip(&reg, pattern, vec_ip[i]);
        if(ret)
        {
            count++;
            //cout<<vec_ip[i]<<endl;
        }
    }
    PROFILE_END
    cout<<"count = "<<count<<endl;
    regfree(&reg);
}

void longtext_test(const char *content)
{
    //string pattern = "Failers";
    //string pattern = "(.)(.)(.)\\3\\2\\1";
    string pattern = "jimi";
    regex_t reg;
    pcre *pre;
    bool ret;
    int cflags = REG_EXTENDED;
    int i = 0;
    char *error = NULL;
    int erroffset;

    regcomp(&reg, pattern.c_str(), cflags);
    pre = pcre_compile(pattern.c_str(), 0, (const char **)(&error), &erroffset, NULL);
    RE re(pattern);
    int count = 0;
    PROFILE_START
    for(i=0; i < 10000; i++)
    {
        ret = pcre_match_text(re, pattern, content);
        
        if(ret)
        {
            count++;
            //cout<<vec_ip[i]<<endl;
        }
    }
    PROFILE_END
    cout<<"count = "<<count<<endl;

    count = 0;
    PROFILE_START
    for(i=0; i < 10000; i++)
    {
        ret = pcre_match_text(pre, pattern, content);
        if(ret)
        {
            count++;
            //cout<<vec_ip[i]<<endl;
        }
    }
    PROFILE_END

    count = 0;
    PROFILE_START
    for(i=0; i < 10000; i++)
    {
        ret = regex_match_text(&reg, pattern, content);
        if(ret)
        {
            count++;
            //cout<<vec_ip[i]<<endl;
        }
    }
    PROFILE_END
    cout<<"count = "<<count<<endl;
    regfree(&reg);
}


char *buffer = NULL;
int main(int argc, char *argv[])
{
    long long fsize = 0;
    FILE *fp = fopen("./testdata","r");
    if(fp != NULL)
    {
        fseek(fp, 0, SEEK_END);
        fsize = ftell(fp);
        rewind(fp);
        buffer = (char*)malloc(fsize + 1);
        fread(buffer, fsize, 1, fp);
    }

    profile_test();
    longtext_test(buffer);
    
    return 0;
}
