#ifndef FAST_PIMPL_EXAMPLE_HPP
#define FAST_PIMPL_EXAMPLE_HPP

#include <memory>

// https://stackoverflow.com/questions/52669202/storing-a-unique-ptr-with-custom-deleter-in-a-map
// https://en.cppreference.com/w/cpp/memory/unique_ptr
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
        alignas(64) char allocatedMemory[500];
        class impl;
        //impl* pimpl;

        struct Deleter
        {
            void operator()(impl* ptr)
            {
                // do nothing as the allocation is on the stack
                ptr = nullptr;
            }
        };

        std::unique_ptr< impl, Deleter > pimpl;

}; // class MyClassWithFastPimpl

#endif
