#pragma once

#include "List_header.h"
#include "MyArray.h"
#include "MyFList.h"


template<typename T>
class TableHash{
private:
    MyArray<ForwardList<T>> buckets;
    size_t countItems = 0;
    size_t bucketsThersSmtng = 0;
    const double loadFactor = 0.75;
    
    size_t Hash(const int& x) const {
        size_t h = static_cast<size_t>(x);
        h ^= (h >> 16);
        h *= 0x45d9f3b;
        h ^= (h >> 16);
        h *= 0x45d9f3b;
        h ^= (h >> 16);
        return h;
    }
    
    size_t Hash(const string& s) const {
        size_t h = 0x9e3779b97f4a7c15ULL; // число из золотого сечения
        const size_t prime = 0x100000001b3ULL; // простое число (FNV prime)

        for (unsigned char c : s) {
            h ^= static_cast<size_t>(c) + 0x9e3779b9 + (h << 6) + (h >> 2);
            h *= prime;
        }
        return h;
    }
    
    size_t get_bucket_index(const T& key) const {
        return Hash(key) % buckets.capacity;
    }
    
    void rehash() {
        MyArray<ForwardList<T>> newBuckets{buckets.capacity * 2};
        
        for (int i = 0; i < buckets.capacity; i++) {
            for (int j = 0; j < buckets.data[i].key.size; j++){
                T element = FGET_key(buckets.data[i].key, j);
                size_t newIndex = Hash(element) % newBuckets.capacity;
                FPUSH_back(newBuckets.data[newIndex].key, element);
            }
        }
        resize(buckets);
        for (int i = 0; i < buckets.capacity; i++){
            buckets.data[i].key = newBuckets.data[i].key;
        }
    }
    
public:
    TableHash(int initcap) : buckets(MyArray<ForwardList<T>>(initcap)) {};
    TableHash() : buckets(MyArray<ForwardList<T>>(10)) {};
    
    bool HT_AT(const T& key) const {
        if (buckets.size == 0) return false;
        
        size_t index = get_bucket_index(key);
        for (int i = 0; i < buckets.data[index].key.size; i++){
            if (FGET_key(buckets.data[index].key, i) == key){return true;}
        }

        return false;
    }
    
    void HTADD(const T& key) {
        if (HT_AT(key)) {
            return;
        }
        
        if (static_cast<double>(countItems) / static_cast<double>(buckets.capacity) >= loadFactor){
            rehash();
        }
        
        int index = get_bucket_index(key);
        
        if (buckets.data[index].key.size == 0){bucketsThersSmtng++;}
        FPUSH_back(buckets.data[index].key, key);
        countItems++;
        buckets.size++;
        
        if (static_cast<double>(bucketsThersSmtng) / static_cast<double>(buckets.capacity) >= 0.9){
            rehash();   
        }
    }
    
    void HTDEL(const T& key) {
        if (buckets.size == 0) return;
        
        size_t index = get_bucket_index(key);
        if (buckets.data[index].key.size == 0) {return;}
        if (buckets.data[index].key.size == 1) {bucketsThersSmtng--;}

        FDEL_val(buckets.data[index].key, key);
    }
    
    
    size_t size() const {
        return countItems;
    }
    
    bool empty() const {
        return countItems == 0;
    }
    
    void PRINT(){
        for (int i = 0; i < buckets.capacity; i++){
            ::PRINT(buckets.data[i].key);
        }
    }
};

