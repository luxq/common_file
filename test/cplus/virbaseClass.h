// Last Update:2016-11-12 11:35:30
/**
 * @file virbaseClass.h
 * @brief 
 * @author luxueqian
 * @version 0.1.00
 * @date 2016-11-12
 */

#ifndef VIRBASE_CLASS_H
#define VIRBASE_CLASS_H
#include <string>
class PB_Base{
    public:
        inline PB_Base() {};
        virtual ~PB_Base(){};
        virtual int pb_getFieldValue(std::string &fieldName, void *pValue) = 0;
};

#endif  /*VIRBASE_CLASS_H*/
