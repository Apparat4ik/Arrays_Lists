#pragma once

#include "List_header.h"
#include "MyArray.h"


template<typename T>
class MySet{
private:
    MyArray<T> buckets;
    size_t countItems = 0;
    
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
        MyArray<T> newBuckets{buckets.capacity * 2};
        
        for (int i = 0; i < buckets.capacity; i++) {
            hash<T> newHasher;
            size_t newIndex = newHasher(buckets.data[i].key) % newBuckets.capacity;
            newBuckets.data[newIndex].key = buckets.data[i].key;
        }
        resize(buckets);
        for (int i = 0; i < buckets.capacity; i++){
            MSWAP(buckets, i, newBuckets.data[i].key);
        }
        }
    
public:
    MySet(int initcap) : buckets(MyArray<T>(initcap)) {};
    MySet() : buckets(MyArray<T>(10)) {};
    
    bool SET_AT(const T& key) const {
        if (buckets.size == 0) return false;
        
        size_t index = get_bucket_index(key);
        
        if (buckets.data[index].key == key) return true;

        return false;
    }
    
    void SETADD(const T& key) {
        if (SET_AT(key)) {
            return;
        }
        
        int index = get_bucket_index(key);
        if (buckets.data[index].key != T()) {
            rehash();
            index = get_bucket_index(key);
            MPUSH_index(buckets, index, key);
            countItems++;
            return;
        }
        
        MPUSH_index(buckets, index, key);
        countItems++;
    }
    
    void SETDEL(const T& key) {
        if (buckets.size == 0) return;
        
        size_t index = get_bucket_index(key);
    
        if (buckets.data[index].key == key){
            MDEL(buckets, index);
            countItems--;
        }
    }
    
    size_t size() const {
        return countItems;
    }
    
    bool empty() const {
        return countItems == 0;
    }
    
    void SPRINT(){
        PRINT(buckets);
    }
    
    void set_write_file(const string& filename) const {
        ofstream file(filename);
        if (!file.is_open()) {
            return;
        }
        

        file << buckets.capacity << ' ' << countItems << ' ' << endl;

        for (int i = 0; i < buckets.capacity; i++){
            file << buckets.data[i].key << ' ';
        }

        file.close();
    }
    
    void set_read_file(const string& filename){
        ifstream file(filename);
       if (!file.is_open()) {
           return;
       }
        
        int sz, count;
        file >> sz >> count;

        T value;
        while (file >> value) {
            SETADD(value);
        }

        file.close();
    }
};

