#ifndef FAST_PIMPL_EXAMPLE_HPP
#define FAST_PIMPL_EXAMPLE_HPP

#include <memory>

// https://stackoverflow.com/questions/52669202/storing-a-unique-ptr-with-custom-deleter-in-a-map

// forward declaration 

class MyClassWithFastPimpl
{
    public:
        //MyClassWithFastPimpl(){}
        MyClassWithFastPimpl();
        ~MyClassWithFastPimpl() = default;

        void doPrintSomething();
        int returnSomething();
    
    //private: 
        char allocatedMemory[10];
        class impl;
        impl* pimpl;

}; // class MyClassWithFastPimpl

#endif
