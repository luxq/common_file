// Last Update:2017-12-20 17:32:15
/**
 * @file handle.cpp
 * @brief 
 * @author luxueqian
 * @version 0.1.00
 * @date 2017-12-20
 */
#include <stdio.h>
#include <stdexcept>

template <class T> class Handle {
    public:
        Handle(T *p=0): ptr(p), use(new size_t(1)) {}
        T& operator*();
        T* operator->();
        const T& operator*() const;
        const T* operator->() const;
        Handle(const Handle& h): ptr(h.ptr), use(h.use)
        { ++*use; }
        Handle& operator=(const Handle&);
        ~Handle() { rem_ref(); }
    private:
        T* ptr;
        size_t *use;
        void rem_ref()
        {
            if (--*use == 0)
            {
                delete ptr;
                delete use;
            }
        }

};

template <class T>
inline Handle<T>& Handle<T>::operator=(const Handle &rhs)
{
    ++*rhs.use;
    rem_ref();
    ptr = rhs.ptr;
    use = rhs.use;
    return *this;
}

template <class T>
inline T& Handle<T>::operator*()
{
    if (ptr) return *ptr;
    throw std::runtime_error ("dereference of unbound Handle");
}

template <class T>
inline T* Handle<T>::operator->()
{
    if(ptr) return ptr;
    throw std::runtime_error ("access through unbound Handle");

}


template <class T>
const T& Handle<T>::operator*() const
{
    return 
}

template <class T>
const T* Handle<T>::operator->() const
{
}


