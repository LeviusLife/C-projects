#ifndef HASHTABLE_H
#define HASHTABLE_H


#include <iostream>
#include <vector>
#include <list>
#include <typeinfo>
#include <fstream>
#include <string>
#include <algorithm>
#include <iterator>
#include <cstdlib>
#include <cctype>

static const unsigned int default_capacity = 11;
static const unsigned int max_prime = 1301081;


//note to self if a word is still white in vscode that means something is wrong
//in my case, I was trying to use vector and list without #including them, so the words
//std::vector or std::list were white even though I was using them correctly

namespace cop4530 {

    template <typename T>
    class HashTable {
        public:

        HashTable(size_t size = 101);
        ~HashTable();
        bool contains(const T &x);
        bool insert(const T & x);
        bool insert (T &&x);
        bool remove(const T &x);
        void clear();
        bool load(const char *filename);
        void dump();
        bool write_to_file(const char *filename);
        int hashSize() const;



        private:
    
        std::vector<std::list<T>> theList;
        int thisSize; //this represents the number of elements in all of the lists combined. So the size of the hashtable itself 
        void makeEmpty();
        void rehash();
        size_t myhash(const T &x);
        unsigned long prime_below (long);
        void setPrimes(std::vector<long>&);


    }; //end of class


} //end of namespace

#include "hashtable.hpp"
#endif


