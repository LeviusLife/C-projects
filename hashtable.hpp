#include <iostream>
#include <functional>

//i need functional in order to use the stl hash container

namespace cop4530 {

    // returns largest prime number <= n or zero if input is too large
    // This is likely to be more efficient than prime_above(), because
    // it only needs a vector of size n


    //thisSize(prime_below(size)),

    template <typename T>
    HashTable<T>::HashTable(size_t size) :  theList(prime_below(size)), thisSize(0) {
        
        for(auto & itr : theList) {

            itr = std::list<T>();

        }

    }





    template <typename T>
    HashTable<T>::~HashTable() {

        clear();

    }
        /*
        
        Overall, contains is supposed to act like our search function. Contains looks for the 
        value of x within the HashTable. If it's there it will return true, if not it will return false.


        To be more specific,

        First off what does myhash do?
        So it looks like myhash is basically the hash function. It's responsible for
        determining where a value should be stored in the hashtable. In terms of this code.
        my hash will calculate what element in the vector x should go into. myhash will give me
        the index number of the vector where x will be in.

        In the first line of code:
        myhash(x) will return the index of the vector of where x should lie within. 
        Then we use that index number with theList (vector itself) and we create a 
        reference variable for that element. Meaning we have now created a reference variable
        for that specific list within the vector.

        In the second line:
        we're using != to help us return true or false.

        First we're looking for x value with the find function (on our list).
        If x is found then find() will return an iterator somewhere between begin 
        (inclusive) and end(not included), and then if that iterator is not equal to 
        whichList's end iterator then the contains functions will return true. If find() does
        not find x in whichList then find() will return whichList's end iterator. From there this
        expression will be evaluated by the program:

        end(whichList) != end(whichList)

        which is false. So contains will return false.


        
        
        
        */
    template <typename T>
    bool HashTable<T>::contains(const T &x) {
       
       
         auto & whichList = theList[ myhash(x)];
            return find( begin(whichList), end(whichList), x) != end(whichList);

    }



    /*
    
    
    template <typename T>
    bool HashTable<T>::contains(const T& x) {


        auto& whichList = List[myhash(x)];

        return find(begin(whichList, end(whichList), x));

    }
    
    */

        /*
        
        The gist of the insert function is: the program will return false
        and do nothing if x is not found but if x is within the "hashtable"
        then we will insert the element (afterwards if the size is greater than the hashtable's size 
        then we will rehash it). And then the program will return true.
        
        
        
        
        
        */




    template <typename T>
    bool HashTable<T>::insert(const T & x) {
        auto & whichList = theList[ myhash( x ) ];
        if( find( begin( whichList ), end( whichList ), x ) != end( whichList ) )
            return false;
    
        whichList.push_back( x );
    
            // Rehash; see Section 5.5
        if( ++thisSize > theList.size( ) )
            rehash( );
        
        return true;

    }



    /*
    
    bool contains(const T& x) {

        auto &whichList = List[myhash(x)];
        return find(begin(whichList), end(whichList), x);


    }
    
    
    */


   /*
    bool insert(T&& x) {

        auto & whichList = theList[myhash(x)];
        if (std::find(begin(whichList), end(whichList), x) != end(whichList))
            return false;

        whichList.push_back(std::move(x));

        if(++thisSize > theSize)
            rehash();


    }
   
   */
   

    template <typename T>
    bool HashTable<T>::insert (T &&x) {

         auto & whichList = theList[ myhash( std::move(x) ) ];
        if( std::find( std::begin( whichList ), std::end( whichList ), const_cast<T&> (x) ) != std::end( whichList ) )
            return false;
    
        whichList.push_back( std::move(x) );
    
            // Rehash; see Section 5.5
        if( ++thisSize > theList.size( ) )
            rehash( );
        
        return true;

    }



    /*
    
    the program uses myhash to find where x would be in the vector<list<>> theList, 
    then we access that specific element with theList[whatever the index is] and assign a reference
    variable to it. This makes it easier to call on that specific list later on

    then we're using the find function to identify what iterator represents the location of
    x. In other words the return value of find(which is an iterator) is assigned to another
    iterator named itr. From there we evaluate if itr is equal to whichList's end iterator. If itr is 
     equal to whichList's end iterator that means that x is not within whichList and we will only
     return false. (This works because a list's end iterator is after its last element. If find() only finds
     end iterator that means we have gone through the entire list and found nothing).

        Anyway, if itr is not equal to whichList's end iterator the if statement does not
        go through and we move on to the next lines. 
        whichList.erase(itr) means we will erase the element at the iterator itr.
        Then we will decrement the size of thisSize and return true.
    
    */
    template <typename T>
    bool HashTable<T>::remove(const T &x) {

        auto & whichList = theList[ myhash( x ) ];
        auto itr = find( begin( whichList ), end( whichList ), x );
        if( itr == end( whichList ) )
            return false;

        whichList.erase( itr );
        --thisSize;
        return true;

    }

    /*
    
    auto & whichList = theList[myhash(x)];
    
    
    */

    template <typename T>
    void HashTable<T>::clear() {

        makeEmpty();

    }

    template <typename T>
    bool HashTable<T>::load(const char *filename) {

        std::ifstream my_reader;
        T unknownVal;


        my_reader.open(filename);

        
         if (my_reader.is_open()) {
            
            
            while( my_reader >> unknownVal) {

                auto & thisList = theList[myhash(unknownVal)];
                if( find( begin( thisList ), end( thisList ), unknownVal ) != end( thisList ) ) {

                    ; // do nothing

                }
                
                else {

                    thisList.push_back(unknownVal);

                    // Rehash; see Section 5.5
                    if( ++thisSize > theList.size( ) )
                    rehash( );

                }

                

            }



        }

        

        else {
            
            //std::cout << "Cannot open up file. Please try again with different method." << std::endl;
            return false;
        }

        my_reader.close();
        return true;


    }


    //we will use itr to loop through the vector itself. Now i need to make a reference 
    //dammnit i have to change dump in order to actually print all the vector numbers
    
    template <typename T>
    void HashTable<T>::dump() {
      
       

       for(int i = 0; i < theList.size(); ++i) {
            std::cout << "v[" << i << "]: "; 
            auto & something = theList[i];

            for (auto & itr : something) {

                    std::cout << itr << '\t';
            }

            std::cout << std::endl;
            
            
            
        }


    }


    template <typename T>
    bool HashTable<T>::write_to_file(const char *filename) {

         std::ofstream my_writer;
         my_writer.open(filename);

         if (my_writer.is_open()) {
            
            for(auto & thisList : theList) {

                    if(!thisList.empty()) {

                        for (auto & itr : thisList) {

                            my_writer << itr << std::endl;
                        }

            
                    }
            
            }

            
        }

        

        else {
            
            std::cout << "Cannot open up file. Please try again with different method." << std::endl;
            return false;
        }

        my_writer.close();
        return true;



    }


    /*
    In this function we're using a for each loop in order to delete all of the 
    elements in each list within the vector. To break it down further, the vector holds lists.

    Let's break down the for each loop:
    in a regular for each loop this is the syntax 

    for(type variable_name : array/vector_name){
    loop statements
    ...
    }


    the type is just the data type of the variable and the variable name is just the name of the 
    variable that will be used to iterate through the array or vector.
    whats important to note is that the variable will store the value of the current array 
    element with each loop and then go on to the next and so on and so forth. 
    So in other words, the variable will translate to v[0] in the first loop, then v[1], etc. with each loop.


    loop statements just refers to what steps will be taken with the use of the
    iterating variable.


    So with that in mind, thisList is probably a reference of list type because each element in the vector
    theList is of "list" type. This reference variable will help us loop through theList without the use of 
    indices (due for each functionality )but it will also allow us to use container function clear much easier.

    Because each element of the vector is a list we can just call clear on each element.
    
    */


    template <typename T>
    void HashTable<T>::makeEmpty() {
        
        for( auto & thisList : theList) {
            thisList.clear();
        }

        thisSize = 0;

    }


        /*
            within this function we are creating another vector of lists called 
            oldList and we are copying all of the elements from theList into it.

            Then we're taking the current size of theList, multiplying it by 2, and then taking
            that result and using the prime_below() function. This function will find the next 
            highest prime number before the result of our previous operation. After that is done the 
            program will then resize list with the result.

            Next the prog will empty out each list in the vector using a for each loop

            (One thing to note is that because the table has more buckets and the hash function is the same,
            the elements that will be moved back may may not be in the same buckets or cells as before )
            change theSize to 0? (why?) 

            im not exactly sure what the last three lines do yet

        
        */
    template <typename T>
    void HashTable<T>::rehash() {
        std::vector<std::list<T>> oldList = theList;

            //create new empty table
        theList.resize(prime_below(2 * theList.size()));
        for(auto & thisList : theList) {
            thisList.clear();
        }

            //copy table over
        thisSize = 0;
        for(auto & thisList : oldList)
            for(auto & x : thisList)
                insert(std::move(x));


    }



    /*
    
        void HashTable<T>::rehash() {

            std::vector<list<T>> oldList = theList;

            theList.resize(prime_below(2*theList.size()));
            for(auto & f : theList) {

                f.clear();
            }

            thisSize = 0;

            for(auto& thisList : oldList)
                for(auto & bum : thisList) {

                    insert(std::move(x));

                }




        }
    
    
    
    
    
    */

    //I need to use another strategy. thee instructions said to use the std::hash function or whatever

    //I have no idea what's going on with this hash function
    template <typename T>
    size_t HashTable<T>::myhash(const T &x) {

        static std::hash<T> hf;
        return hf(x) % theList.size();

    }

    template <typename T>
    unsigned long HashTable<T>::prime_below (long n)
    {
        if (n > max_prime){
            std::cerr << "** input too large for prime_below()\n";
            return 0;
        }
        if (n == max_prime){
            return max_prime;
        }
        if (n <= 1){
		    std::cerr << "** input too small \n";
            return 0;
        }

        // now: 2 <= n < max_prime
        std::vector <long> v (n+1);
        setPrimes(v);
        while (n > 2){
            if (v[n] == 1)
	            return n;
            --n;
        }

        return 2;
    }

    //Sets all prime number indexes to 1. Called by method prime_below(n) 
    template <typename T>
    void HashTable<T>::setPrimes(std::vector<long>& vprimes){
        int i = 0;
        int j = 0;

        vprimes[0] = 0;
        vprimes[1] = 0;
        int n = vprimes.capacity();

        for (i = 2; i < n; ++i)
            vprimes[i] = 1;

        for( i = 2; i*i < n; ++i){
            if (vprimes[i] == 1)
            for(j = i + i ; j < n; j += i)
                vprimes[j] = 0;
        }
    }



    template <typename T>
    int HashTable<T>::hashSize() const {

            return thisSize;
    }






} // end of namespace