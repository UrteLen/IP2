#ifndef ORDEREDSET_H
#define ORDEREDSET_H

#include <string>
#include <stdexcept>
#include <utility>

namespace orderedset {

        //An exception thrown when attempting to insert an existing value
    class DuplicateValueException : public std::logic_error {
    public:
        explicit DuplicateValueException(const std::string& value) 
            : std::logic_error("Duplicate value: '" + value + "' already exists in the set.") {}
    };
        //Implementation of the ADT "Set" using an AVL tree and the Pimpl idiom
    class OrderedSet {
        public:
    
            OrderedSet();                                   //Default constructor
            OrderedSet(const OrderedSet& other);            //Copy constructor (Deep copy)
            OrderedSet(OrderedSet&& other) noexcept;        //Move constructor
            OrderedSet& operator=(const OrderedSet& other); //Copy assignment operator
            ~OrderedSet();                                  //Destructor (frees memory)

            void insert(int value);                         //Inserts new value
            void remove(int value);                         //Removes value
            void update(int oldValue, int newValue);        //Changes old value to new value
            bool contains(int value) const;                 //Checks if value already exist   
            int height() const;                             //Returns AVL height
            int size() const;                               //Returns number of elements
            bool empty() const;                             //Checks if set is empty

            OrderedSet& operator-=(int value);                          //Removal operator
            OrderedSet& operator+=(int value);                          //Insertion operator
            OrderedSet& operator*=(const std::pair<int, int>& values);  //Update operator
            int operator[](int value) const;                            //Search operator (returns 1 if found, 0 if not)
            OrderedSet& operator!();                                    //Clear operator (removes all elements)

            //Comparison operators
            bool operator==(const OrderedSet& other) const;  
            bool operator!=(const OrderedSet& other) const; 
            bool operator<(const OrderedSet& other) const;  
            bool operator<=(const OrderedSet& other) const; 
            bool operator>(const OrderedSet& other) const;  
            bool operator>=(const OrderedSet& other) const; 

            std::string toString() const;

        private:
            class Impl;
            Impl* pImpl;
    };

} 
#endif