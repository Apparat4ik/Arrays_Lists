#pragma once

#include "List_header.h"
#include "MyArray.h"


template<typename T>
class MySet{
private:
    MyArray<T> buckets;
    size_t countItems = 0;
    
    size_t Hash(int key) const {
        size_t hash = 0;
        while (key > 0) {
            hash ^= (key & 0xFF); // берём младший байт и XOR с хэшем
            key >>= 8;            // сдвигаем на байт вправо
        }
        return hash % buckets.size;
    }
    
    size_t Hash(const string& s) const {
        size_t sum = 0;
        for (unsigned char c : s){
            sum += c;
        }
        return sum % buckets.size;
    }
    
    size_t get_bucket_index(const T& key) const {
        return Hash(key) % buckets.capacity;
    }
    
    void rehash() {
        MyArray<T> newBuckets{buckets.capacity * 2};
        
        for (int i = 0; i < buckets.capacity; i++) {
            size_t newIndex = Hash(buckets.data[i].key) % newBuckets.capacity;
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
        
        size_t index = get_bucket_index(key);
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
    
    
    bool SET_AT_XY(const T& key) const {
        if (buckets.size == 0) return false;
        
        size_t index = get_bucket_index(key);
        
        if (buckets.data[index].key != T()) return true;

        return false;
    }
    
    void SETADD_XY(const T& key, const T& value){
        if (SET_AT(key)) {
            return;
        }
        
        size_t index = get_bucket_index(key);
        if (buckets.data[index].key != T()) {
            rehash();
            index = get_bucket_index(key);
            MPUSH_index(buckets, index, value);
            countItems++;
            return;
        }
        
        MPUSH_index(buckets, index, value);
        countItems++;
    }
    
    T SET_GET_XY(const T& key){
        size_t index = get_bucket_index(key);
        return buckets.data[index].key;
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

