// Last Update:2016-11-12 11:25:34
/**
 * @file canMsgClass.cpp
 * @brief 
 * @author luxueqian
 * @version 0.1.00
 * @date 2016-11-12
 */

#include "canMsgClass.h"
#include <string>
using namespace std;

int PB_CANMsg_Operator::pb_getFieldValue(std::string &fieldName, void *pValue)
{
    string *p = (string*)pValue;
    *p = msg();
    return 0;
}

