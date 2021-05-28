#include <iostream>
#include <string>
#include <vector>
#include <cstdlib>
#include <stdexcept>
using namespace std;

template <typename R>
inline R const& Max (R const& a, R const& b){
    return a < b ? b:a;
}

template <class T>
    class Stack{
        private:
            vector<T> elems; //elements

        public:
            void push(T const&); //push elements
            void pop(); //pop elements
            T top() const; //return top element

            bool empty() const{
                return elems.empty();
            }
    };

template <class T>
    void Stack<T>::push (T const& elem){
        //append copy of passed element
        elems.push_back(elem);
    }


template <class T>
    void Stack<T>::pop(){
        if(elems.empty()){
            throw out_of_range("Stack<>::pop(): Empty Stack");
        }
        //remove last element
        elems.pop_back();
    }


template <class T>
    T Stack<T>::top() const {
        if(elems.empty()){
            throw out_of_range("Stack<>::top(): Empty Stack");
        }
        //return copy of last element
        return elems.back();
    }


int main(){
    int i = 39;
    int j = 20;
    cout << "Max(i, j): " << Max(i,j) << endl;

    double f1 = 13.5;
    double f2 = 20.7;
    cout << "Max(f1, f2): " << Max(f1, f2) << endl;

    string s1 = "Hello";
    string s2 = "World";
    cout << "Max(s1, s2): " << Max(s1, s2) << endl;

    try{
        Stack<int> intStack; //Stack of Ints
        Stack<string> stringStack; //stack of strings

        //manipulate int stack
        intStack.push(7);
        cout << intStack.top() << endl;

        //manipulate sting stack
        stringStack.push("hello");
        cout << stringStack.top() << std::endl;
        stringStack.pop();
        stringStack.pop();
    }catch (exception const& ex){
        cerr << "Exception: " << ex.what() << endl;
        return -1;
    }
}