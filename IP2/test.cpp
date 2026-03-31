#include "OrderedSet.h"
#include <iostream>
#include <cassert>
#include <string>

using namespace orderedset;
using namespace std;

int main(){

    cout << "Test 1 (constructor): ";
    {
        OrderedSet s;
        assert(s.empty());
        assert(s.size() == 0);
        assert(s.height() == 0);
        cout << "Pass." << endl;
        cout << "Current state: " << s.toString() << endl;
    }
   

    cout << "Test 2 (insert and contains): ";
    {
        OrderedSet s;
        s.insert(10);
        s.insert(20);
        s.insert(15);
        assert(s.size() == 3);
        assert(s.contains(10));
        assert(s.contains(15));
        assert(!s.contains(11));
        assert(!s.empty());
        cout << "Pass." << endl;
        cout << "Current state: " << s.toString() << endl;
    }

    cout << "Test 3 (contains)";
    {
        OrderedSet s;
        s += 1;
        s += 2;
        s += 3;
        assert(s.size() == 3);
        assert(s.contains(1));
        assert(s.contains(2));
        assert(s.contains(3));
        cout << "Pass." << endl;
        cout << "Current state: " << s.toString() << endl;
    }
    

    cout << "Test 4 (operator[]): ";
    {
        OrderedSet s;
        s += 42;
        assert(s[42] == 1);
        assert(s[0]  == 0);
        cout << "Pass." << endl;
        cout << "Current state: " << s.toString() << endl;
    }

    cout << "Test 5 (remove and operator-=)";
    {
        OrderedSet s;
        s += 10; 
        s += 20;
        s += 30; 
        s.remove(30);
        assert(!s.contains(30));
        assert(s.size() == 2);
        s -= 10;
        assert(!s.contains(10));
        assert(s.size() == 1);
        cout << "Pass." << endl;
        cout << "Current state: " << s.toString() << endl;
    }

    cout << "Test 6 (update and operator*=): ";
    {
        OrderedSet s;
        s += 10; 
        s += 20;
        s += 30;
        s.update(20, 25);
        assert(!s.contains(20));
        assert(s.contains(25));
        assert(s.size() == 3);
        s *= make_pair(10, 15);
        assert(!s.contains(10));
        assert(s.contains(15));
        cout << "Pass." << endl;
        cout << "Current state: " << s.toString() << endl;
    }
   

    cout << "Test 7 (operator! clear): ";
    {
        OrderedSet s;
        s += 1;
        s += 2;
        s += 3; 
        s += 4; 
        s += 5;
        !s;
        assert(s.empty());
        assert(s.size() == 0);
        cout << "Pass." << endl;
        cout << "Current state: " << s.toString() << endl;
    }
   

    cout << "Test 8 (operator== and operator!=): ";
    {
        OrderedSet a, b;
        a += 5; 
        a += 10; 
        a += 15;
        b += 5; 
        b += 10; 
        b += 15;
        assert(a == b);
        assert(!(a != b));
        b += 20;
        assert(a != b);
        assert(!(a == b));
        cout << "Pass." << endl;
        cout << "Current state (a): " << a.toString() << endl;
        cout << "Current state (b): " << b.toString() << endl;
    }

    cout << "Test 9 (subset/superset operators): ";
    {
        OrderedSet a, b;
        a += 7; a += 8; a += 9;
        b += 7; b += 8; b += 9;
        assert(a <= b);
        assert(a >= b);
        assert(!(a < b));
        assert(!(a > b));
        cout << "Pass." << endl;
        cout << "Current state (a): " << a.toString() << endl;
        cout << "Current state (b): " << b.toString() << endl;
    }


    cout << "Test 10 (copy constructor): ";
    {
        OrderedSet og;
        og += 10; 
        og += 20; 
        og += 30;
        OrderedSet copy(og);
        assert(copy == og);
        copy += 40;
        assert(copy != og);
        assert(!og.contains(40));
        cout << "Pass." << endl;
        cout << "Current state (original): " << og.toString() << endl;
        cout << "Current state (copy): " << copy.toString() << endl;
    }
    

    cout << "Test 11 (copy assignment): ";
    {
        OrderedSet og;
        og += 5; 
        og += 6; 
        og += 7;
        OrderedSet assigned;
        assigned = og;
        assert(assigned == og);
        assigned += 100;
        assert(!og.contains(100));
        cout << "Pass." << endl;
        cout << "Current state (original): " << og.toString() << endl;
        cout << "Current state (assigned): " << assigned.toString() << endl;
    }
   

    cout << "Test 12 (self-assignment): ";
    {
        OrderedSet s;
        s += 1;
        s += 2; 
        s += 3;

        OrderedSet& ref = s;
        s = ref; 

        assert(s.size() == 3);
        cout << "Pass." << endl;
        cout << "Current state: " << s.toString() << endl;
    }

    cout << "Test 13 (move constructor): ";
    {
        OrderedSet src;
        src += 1; 
        src += 2; 
        src += 3;
        int ogSize = src.size();
        OrderedSet dst(std::move(src));
        assert(dst.size() == ogSize);
        assert(dst.contains(2));
        cout << "Pass." << endl;
        cout << "Current state (original): " << src.toString() << endl;
        cout << "Current state (moved): " << dst.toString() << endl;
    }
   

    cout << "Test 14 (AVL height): ";
    {
        OrderedSet s;
        for (int i = 1; i <= 15; ++i){
            s += i;
        }
        assert(s.height() == 4);
        assert(s.size() == 15);
        cout << "Pass." << endl;
        cout << "Current state: " << s.toString() << endl;
    }

    cout << "Test 15 (toString): ";
    {
        OrderedSet s;
        s += 3; 
        s += 1; 
        s += 2;
        string expected = "OrderedSet { size=3, height=2, elements=[ 1 2 3 ] }";
        string actual   = s.toString();
        assert(actual == expected);
        cout << "Pass." << endl;
        cout << "Current state: " << s.toString() << endl;
    }

     cout << "Test 16 (DuplicateValueException on insert): ";
    {
        OrderedSet s;
        s += 7;
        bool caught = false;
        try {
            s += 7;
        } catch (const DuplicateValueException& e) {
            caught = true;
            cout << "\n  Exception: " << e.what() << endl;
            cout << "Test 16 continued: ";
        }
        assert(caught);
        assert(s.size() == 1);
        cout << "Pass." << endl;
        cout << "Current state: " << s.toString() << endl;
    }

    cout << "Test 17 (DuplicateValueException on update): ";
    {
        OrderedSet s;
        s += 1; 
        s += 2;
        bool caught = false;
        try {
            s.update(1, 2);
        } catch (const DuplicateValueException& e) {
            caught = true;
            cout << "\n  Exception: " << e.what() << endl;
            cout << "Test 17 continued: ";
        }
        assert(caught);
        assert(s.contains(1));
        cout << "Pass." << endl;
        cout << "Current state: " << s.toString() << endl;
    }

    cout << "Test 18 (out_of_range on remove): ";
    {
        OrderedSet s;
        s += 5;
        bool caught = false;
        try {
            s.remove(999);
        } catch (const out_of_range& e) {
            caught = true;
            cout << "\n  Exception: " << e.what() << endl;
            cout << "Test 18 continued: ";
        }
        assert(caught);
        cout << "Pass." << endl;
        cout << "Current state: " << s.toString() << endl;
    }

    cout << "Test 19 (out_of_range on update): ";
    {
        OrderedSet s;
        s += 5;
        bool caught = false;
        try {
            s.update(999, 1);
        } catch (const out_of_range& e) {
            caught = true;
            cout << "\n  Exception: " << e.what() << endl;
            cout << "Test 19 continued: ";
        }
        assert(caught);
        cout << "Pass." << endl;
        cout << "Current state: " << s.toString() << endl;
    }

     cout << "Test 20 (out_of_range on operator-=): ";
    {
        OrderedSet s;
        bool caught = false;
        try {
            s -= 42;
        } catch (const out_of_range& e) {
            caught = true;
        }
        assert(caught);
        cout << "Pass." << endl;
        cout << "Current state: " << s.toString() << endl;
    }

    return 0;

}