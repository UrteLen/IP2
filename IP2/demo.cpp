#include "OrderedSet.h"
#include <iostream>
#include <string>

using namespace orderedset;
using namespace std;

int main(){

    cout << "1. Default constructor: " << endl;
    OrderedSet s;
    cout << "New set: " << s.toString() <<endl;
    cout << "empty(): " << (s.empty() ? "true" : "false") << endl;
    cout << "size(): " << s.size() << endl;
    cout << "height(): " << s.height() << endl;

    cout << endl;
    cout << "2. Insert(): " <<endl;
    s.insert(20);
    s.insert(10);
    s.insert(30);
    s.insert(25);
    s.insert(40);
    cout << s.toString() << endl;
    cout << "height(): " << s.height() << endl;

    cout << endl;
    cout << "3. operator += : " << endl;
    s += 50;
    s += 5;
    s += 35;
    cout << s.toString() << endl;

    cout << endl;
    cout << "4. contains(): " << endl;
    cout << "contains(25): " << (s.contains(25) ? "true" : "false") << endl;
    cout << "contains(25): " << (s.contains(100) ? "true" : "false") << endl;

    cout << endl;
    cout << "5. operator[] (1 = found, 0 = not found): " << endl;
    cout << "s[10]: " << s[10] << endl;
    cout << "s[99]: " << s[99] << endl;

    cout << endl;
    cout << "6. update(): " << endl;
    s.update(30, 55);
    cout << s.toString() << endl;

    cout << endl;
    cout << "7. operator*= :" << endl;
    s *= make_pair(5, 2);
    cout << s.toString() <<endl;

    cout << endl;
    cout << "8. remove(): " << endl;
    s.remove(10);
    cout << s.toString();

    cout << endl;
    cout << "9. Copy constructor: " << endl;
    OrderedSet copy(s);
    cout << "Original: " << s.toString() << endl;
    cout << "Copy: " << copy.toString() << endl;

    cout << endl;
    cout << "10. Copy assignment: " << endl;
    OrderedSet assigned;
    assigned = s;
    assigned += 200;
    cout << "Original: " << s.toString() << endl;
    cout << "Assigned: " << assigned.toString() << endl;

    cout << endl;
    cout << "11. Move constructor: " << endl;
    OrderedSet moved(std::move(assigned));
    cout << "Moved: " << moved.toString() << endl;

    cout << endl;
    cout << "12. Comparison operators: " << endl;
    OrderedSet a, b;
    a += 10; 
    a += 20;
    a += 30;
    b += 10;
    b += 20;
    b += 30;
    cout << "a: " << a.toString() << endl;
    cout << "b: " << b.toString() << endl;
    cout << "a == b: " << (a == b ? "true" : "false") << endl;
    cout << "a != b: " << (a != b ? "true" : "false") << endl;
    b += 32;
    cout << "b after += 32: " << b.toString() << endl;
    cout << "a < b: " << (a < b ? "true" : "false") << endl;
    cout << "a <= b: " << (a <= b ? "true" : "false") << endl;
    cout << "a > b: " << (a > b ? "true" : "false") << endl;
    cout << "a >= b: " << (a >= b ? "true" : "false") << endl;

    cout << endl;
    cout << "13. operator! : " << endl;
    cout << "Before: " << b.toString() << endl;
    !b;
    cout << "After: " << b.toString() << endl;
    cout << "empty(): " << (b.empty() ? "true" : "false") << endl;

    cout << endl;
    cout << "14. Duplicate Value Exception: " << endl;
    OrderedSet d;
    d += 7;
    try{
        d += 7;
    } catch (const DuplicateValueException &e){
        cout << e.what() << endl;
    }

    cout << endl;
    cout << "15. Out of range: " << endl;
    try{
        a.remove(900);
    } catch (const out_of_range &e){
        cout << e.what() << endl;
    }

    cout << endl;
    cout << "16. Out of range update: " << endl;
    try
    {
        a.update(900, 1);
    }
    catch(const out_of_range &e)
    {
        cout << e.what() << endl;
    }
    
    return 0;
}