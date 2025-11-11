#pragma once

#include "List_header.h"
#include "MyDoubleList.h"
#include "TableHash.h"



template<typename T>
class LRU{
private:
    TableHash<T> table;
    DoubleList<HashNode<T>> cash;
    int capacity;
    
public:
    LRU(int cap) : capacity(cap){}
    
    T GET(T key){
        if (!table.HT_AT(key)){
            return -1;
        }
        T value = table.GET(key);
        HashNode<T> nd{key, value};
        LDEL_val(cash, nd);
        LPUSH_front(cash, nd);
        return value;
    }
    
    void SET(const T& key, const T& value){
        if (table.HT_AT(key)){
            
            T oldElement = table.GET(key);
            
            table.HTDEL(key);
            table.HTADD(key, value);
            
            HashNode<T> old_node{key, oldElement};
            HashNode<T> nd{key, value};
            
            LDEL_val(cash, old_node);
            LPUSH_front(cash, nd);
            return;
        }
        
        if (cash.size >= capacity){
            
            HashNode<T> nd{key, value};
            table.HTDEL((cash.tail -> key).key);
            LDEL_back(cash);
            LPUSH_front(cash, nd);
            table.HTADD(key, value);
            
            return;
        }
        HashNode<T> nd{key, value};
        LPUSH_front(cash, nd);
        table.HTADD(key, value);
    }
    
    void PRINT(){
        ::PRINT(cash);
    }
};
