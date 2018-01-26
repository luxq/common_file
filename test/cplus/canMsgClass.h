// Last Update:2016-11-12 11:41:04
/**
 * @file canMsgClass.h
 * @brief 
 * @author luxueqian
 * @version 0.1.00
 * @date 2016-11-12
 */

#ifndef CAN_MSG_CLASS_H
#define CAN_MSG_CLASS_H
#include "virbaseClass.h"
#include <string>
using namespace std;

class PB_CANMsg_Operator :public PB_Base{
    public:
        PB_CANMsg_Operator()
        {
            msg_ = new string("1234567");
        }
        ~PB_CANMsg_Operator()
        {
            delete msg_;
        }
        string& msg()
        {
            return *msg_;
        }
        int pb_getFieldValue(std::string &fieldName, void *pValue);
    private:
        std::string *msg_;
};

#ifdef __cplusplus
extern "C" {
#endif
    PB_Base *attach()
    {
        return (PB_Base*) new PB_CANMsg_Operator();
    }
#ifdef __cplusplus
}
#endif


#endif  /*CAN_MSG_CLASS_H*/
