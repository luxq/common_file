// Last Update:2017-03-16 17:30:38
/**
 * @file striptime.cpp
 * @brief 
 * @author luxueqian
 * @version 0.1.00
 * @date 2017-01-16
 */
#include <stdio.h>
#include <string.h>
#include <sys/time.h>
#include <time.h>
#include <vector>
#include <map>
#include <string>
#include <stdint.h>
#include <stdlib.h>
#include <algorithm>

class Cvar
{
    public:
        Cvar(){ m_val = "";}
        Cvar(std::string value) {m_val = value;}
        Cvar& operator= (Cvar other)
        {
            this->m_val = other.m_val;
            return *this;
        }
        Cvar& operator= (std::string val)
        {
            this->m_val = val;
            return *this;
        }
        Cvar& operator= (int val)
        {
            char buf[20];
            sprintf(buf, "%d", val);
            this->m_val = std::string(buf);
            return *this;
        }
        Cvar& operator= (uint64_t val)
        {
            char buf[20];
            sprintf(buf, "%ld", val);
            this->m_val = std::string(buf);
            return *this;
        }
        Cvar& operator= (double val)
        {
            char buf[20];
            sprintf(buf, "%f", val);
            this->m_val = std::string(buf);
            return *this;
        }

        std::string get_value_string()
        {
            return m_val;
        }

        bool get_value_bool()
        {
            int32_t ret = 0;
            if(!m_val.empty())
            {
                ret = atoi(m_val.c_str());
            }
            return (bool)ret;
        }
        int32_t get_value_int32_t()
        {
            int32_t ret = 0;
            if(!m_val.empty())
            {
                ret = atoi(m_val.c_str());
            }
            return ret;
        }
        uint32_t get_value_uint32_t()
        {
            int32_t ret = 0;
            if(!m_val.empty())
            {
                ret = atoi(m_val.c_str());
            }
            return (uint32_t)ret;
        }
        int64_t get_value_int64_t()
        {
            int64_t ret = 0;
            if(!m_val.empty())
            {
                ret = atol(m_val.c_str());
            }
            return ret;
        }
        uint64_t get_value_uint64_t()
        {
            int64_t ret = 0;
            if(!m_val.empty())
            {
                ret = atol(m_val.c_str());
            }
            return (uint64_t)ret;
        }
        float get_value_float()
        {
            float ret = 0.0;
            if(!m_val.empty())
            {
                ret = atof(m_val.c_str());
            }
            return ret;
        }
        double get_value_double()
        {
            double ret = 0.0;
            if(!m_val.empty())
            {
                ret = atof(m_val.c_str());
            }
            return ret;
        }
        bool empty()
        {
            return m_val.empty();
        }
    private:
        std::string m_val;
};
#if 0
void get_timestamp(char *datatime, char *pformat)
{
    struct tm timeinfo;
    memset(&timeinfo, 0, sizeof(tm));
    strptime(datatime, pformat,&timeinfo);
    time_t t = mktime(&timeinfo);
    printf("%s, to--> %ld\n", datatime, t);
}
#endif
static Cvar datatime_to_timestamp(std::string datatime_str)
{
    Cvar ret;
    struct tm timeinfo;
    memset(&timeinfo, 0, sizeof(tm));
    if(strptime(datatime_str.c_str(), "%Y%m%d%H%M%S",&timeinfo) != NULL)
    {
        time_t t = mktime(&timeinfo);
        ret = (uint64_t)t;
    }
    else if(strptime(datatime_str.c_str(), "%Y-%m-%d %H:%M:%S",&timeinfo) != NULL)
    {
        time_t t = mktime(&timeinfo);
        ret = (uint64_t)t;
    }
    else if(strptime(datatime_str.c_str(), "%Y/%m/%d %H:%M:%S",&timeinfo) != NULL)
    {
        time_t t = mktime(&timeinfo);
        ret = (uint64_t)t;
    }
    else
    {
        ret = (uint64_t)0;
    }
    return ret;
} 
static Cvar get_date_from_datetime(std::vector<Cvar *> argv)
{
    Cvar ret;
    if(argv.size() != 2)
        return ret;
    struct tm timeinfo;
    char buf[10] = {0};
    memset(&timeinfo, 0, sizeof(tm));
    std::string datatime_str = argv[0]->get_value_string();
    std::string str_formt = argv[1]->get_value_string();
    strptime(datatime_str.c_str(), str_formt.c_str(),&timeinfo);
    sprintf(buf, "%4d%02d%02d", timeinfo.tm_year+1900,timeinfo.tm_mon + 1,timeinfo.tm_mday);
    ret = std::string(buf);

    return ret;
} 
//从格式化的日期时间字符串获取时间，采用6位字符串格式:HHMMSS
//static Cvar get_time_from_datetime(std::string datatime_str, std::string format)
static Cvar get_time_from_datetime(std::vector<Cvar *> argv)
{
    Cvar ret;
    if(argv.size() != 2)
        return ret;
    struct tm timeinfo;
    char buf[10] = {0};
    memset(&timeinfo, 0, sizeof(tm));
    std::string datatime_str = argv[0]->get_value_string();
    std::string str_formt = argv[1]->get_value_string();
    strptime(datatime_str.c_str(), str_formt.c_str(),&timeinfo);
    sprintf(buf, "%02d%02d%02d", timeinfo.tm_hour,timeinfo.tm_min,timeinfo.tm_sec);
    ret = std::string(buf);

    return ret;
} 

//static Cvar inner_check_imei(std::vector<Cvar *> argv)
static Cvar inner_check_imei(std::string imei)
{
    Cvar ret;
//    if(argv.size() != 1)
//        return ret;
//    std::string imei = argv[0]->get_value_string();
    int len = imei.length();
    if(len == 15)
    {
        for(int i = 0; i < len; i++)
        {
            if(imei.at(i) > '9' || imei.at(i) < '0')
            {
                imei = "";
                break;
            }
        }
    }
    else
    {
        imei = "";
    }

    ret = imei;
    return ret;
}

static Cvar del_char_group(std::string str, std::string sep_set)
{
    Cvar ret;
    std::string nstr = "";
    int slen = str.length();
    if(sep_set.length() == 0)
    {
        nstr = str; 
    }
    else
    {
        for(int i = 0; i < slen; i++)
        {
            char ch = str.at(i);
            if(sep_set.find(ch) == std::string::npos)
            {
                nstr += ch;
            }
        }
    }
    ret = nstr;
    return ret;

}
//删除字符串内的字符
//static Cvar inner_del_char(std::string str, std::string sep_set)
static Cvar inner_del_char(std::vector<Cvar *> argv)
{
    Cvar ret;
    if(argv.size() != 2)
        return ret;
    std::string str = argv[0]->get_value_string();
    std::string sep_char = argv[1]->get_value_string();
    ret = del_char_group(str, sep_char);
    return ret;
}

//format_id: 0:小写   1:大写
static std::string string_format(std::string str, unsigned int offset, unsigned int length, int format_id)
{
    int len = length;
    std::string n = "";
    if(str.length() <= offset)
        return n;
    if(str.length() < (offset + length))
    {
        len = str.length() - offset;
    }
    n.resize(len);
    switch(format_id)
    {
        case 0:
            transform(str.begin() + offset, str.begin()+offset+len, n.begin(), ::tolower);
            break;
        case 1:
            transform(str.begin() + offset, str.begin()+offset+len, n.begin(), ::toupper);
            break;
        default:
            n = str.substr(offset, len);
            break;
    }
    return n;
}

//字符串转大小写转换
//format_id:
//0: 转为小写
//1: 转为大写
//static Cvar inner_string_format(std::string str, unsigned int offset, unsigned int length, int format_id)
static Cvar inner_string_format(std::vector<Cvar *> argv)
{
    Cvar ret;
    if(argv.size() != 4)
        return ret;
    std::string str = argv[0]->get_value_string();
    unsigned int offset = argv[1]->get_value_uint32_t();
    unsigned int len = argv[2]->get_value_uint32_t();
    int format_id = argv[3]->get_value_int32_t();
    std::string r = string_format(str, offset, len, format_id);
    ret = r;
    return ret;
}


//归一化MAC地址
//format_id:
//0     无冒号分隔，全部小写
//1     无冒号分隔，全部大写
static Cvar inner_format_macaddr(std::string mac_str, int format_id)
//static Cvar inner_format_macaddr(std::vector<Cvar *> argv)
{
    Cvar ret;
//   if(argv.size() != 2)
//        return ret;
//    std::string mac_str = argv[0]->get_value_string();
//    int format_id = argv[1]->get_value_int32_t();

    switch(format_id)
    {
        case 0:
            //全部小写
            mac_str = string_format(mac_str, 0, mac_str.length(), 0);
            //删除冒号
            ret = del_char_group(mac_str, ":");
            break;
        case 1:
            //全部大写
            mac_str = string_format(mac_str, 0, mac_str.length(), 1);
            //删除冒号
            ret = del_char_group(mac_str, ":");
            break;
        default:
            ret = mac_str;
            break;
    }
    return ret;
}

static Cvar inner_get_cur_timestamp(void)
{
    Cvar ret;
    time_t now;
    now = time(NULL);
    ret = (uint64_t)now;
    return ret;
}

int main(int argc, char *argv[])
{
    //Cvar str("20161223131423");
    //Cvar format("%Y%m%d%H%M%S");
    //std::vector<Cvar *> gv;
    //gv.push_back(&str);
    //gv.push_back(&format);
    Cvar ret;
    ret = datatime_to_timestamp("20170102121212");
    printf("ret = %ld\n", ret.get_value_uint64_t());
    ret = datatime_to_timestamp("2017-01-02 12:12:12");
    printf("ret = %ld\n", ret.get_value_uint64_t());
    ret = datatime_to_timestamp("2017/01/02 12:12:12");
    printf("ret = %ld\n", ret.get_value_uint64_t());
    double lb = 312.012;
    ret = lb;
    printf("ret = %f\n", ret.get_value_double());
    double lb1 = 312.0123456;
    printf("ret = %f\n", lb1);
    ret = lb1;
    printf("ret = %f\n", ret.get_value_double());
    //ret = get_date_from_datetime(gv);
    //printf("getdate = %s\n", ret.get_value_string().c_str());
    //ret = get_time_from_datetime(gv);
    //printf("gettime = %s\n", ret.get_value_string().c_str());
    //std::string ustr = "ABCDEFGH";//"ABCDEFGHIKLJ";
    //std::string low = string_format(ustr, 3,8,1);
    //std::string lstr = "abcdefghiklj";
    //std::string upp = string_format(lstr, 3,8,0);
    //printf("low = %s, upp = %s.\n", low.c_str(), upp.c_str());
    //std::string mac = "A3:23:33:45:dC:fF";
    //std::string fm = inner_format_macaddr(mac, 0).get_value_string();
    //printf("mac format 0 = %s\n", fm.c_str());
    //fm = inner_format_macaddr(mac, 1).get_value_string();
    //printf("mac format 1 = %s\n", fm.c_str());
    //std::string im = "128y1943djkl323";
    //fm = inner_check_imei(im).get_value_string();
    //printf("wrong imei = %s\n", fm.c_str());
    //im = "1289433231232345667";
    //fm = inner_check_imei(im).get_value_string();
    //printf("wrong imei = %s\n", fm.c_str());
    //im = "128943323123234";
    //fm = inner_check_imei(im).get_value_string();
    //printf("ok imei = %s\n", fm.c_str());

    //fm = inner_get_cur_timestamp().get_value_string();
    //printf("cur time = %s\n", fm.c_str());

    return 0;
}
