#ifndef __STACK_H__
#define __STACK_H__
#include "list.h"
template <typename T>
class Stack: public List<T>
{
public:
    T pop(){
        return List::popFront();
    }
    void push(T data){
        List::pushFront(data);
    }
};


#endif // __STACK_H__
