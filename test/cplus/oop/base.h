// Last Update:2017-12-19 13:30:06
/**
 * @file base.h
 * @brief 
 * @author luxueqian
 * @version 0.1.00
 * @date 2017-12-19
 */

#ifndef BASE_H
#define BASE_H
#include <string>

class Item_base{
    public:
        Item_base(const std::string &book = "",
                double sales_price = 0.0):isbn(book), price(sales_price) { }
        std::string book() const { return isbn; }
        virtual double net_price(std::size_t n) const 
        {
            return price * n;
        }
        virtual ~Item_base() {}
    private:
        std::string isbn;
    protected:
        double price;
};

class Bulk_item: public Item_base {
    public:
        double net_price(std::size_t n) const;
    private:
        std::size_t min_qty;
        double discount;
};


#endif  /*BASE_H*/
