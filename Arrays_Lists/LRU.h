#pragma once

#include "List_header.h"
#include "MyDoubleList.h"
#include "MySet.h"



template<typename T>
class LRU{
private:
    MySet<T> table;
    DoubleList<T> cash;
    int capacity;
    
public:
    LRU(int cap) : capacity(cap){}
    
    T GET(T key){
        if (!table.SET_AT_XY(key)){
            return -1;
        }
        T value = table.SET_GET_XY(key);
        LDEL_val(cash, value);
        LPUSH_front(cash, value);
        return value;
    }
    
    void SET(const T& key, const T& value){
        if (table.SET_AT_XY(key)){
            
            T oldElement = table.SET_GET_XY(key);
            
            table.SETDEL(key);
            table.SETADD_XY(key, value);
            
            LDEL_val(cash, oldElement);
            LPUSH_front(cash, value);
            return;
        }
        
        if (cash.size >= capacity){
            LDEL_back(cash);
            LPUSH_front(cash, value);
            table.SETADD_XY(key, value);
            return;
        }
        
        LPUSH_front(cash, value);
        table.SETADD_XY(key, value);
    }
    
    void PRINT(){
        ::PRINT(cash);
    }
};
