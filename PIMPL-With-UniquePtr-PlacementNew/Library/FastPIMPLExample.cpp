#include "FastPIMPLExample.hpp"
#include <iostream>




class MyClassWithFastPimpl::impl
{
    public:
        impl() : numberToReturn(-4), index(0) {}
        void doPrintMessage()
        {
            std::cout << "Hello, World!" << std::endl;
        }

        int returnSomething()
        {
            numberToReturn++;
            internalStorage[index] = numberToReturn;
            index++;
            internalStorage[98] = 1000;
            return (internalStorage[index-1]);
        }
    private:

        int numberToReturn;
        uint8_t index;
        int internalStorage[99];
}; // class MyClassWithFastPimpl::impl


MyClassWithFastPimpl::MyClassWithFastPimpl() : pimpl{std::unique_ptr<impl, Deleter> (new (MyClassWithFastPimpl::allocatedMemory) impl)}
{
    std::cout << "Memory allocated at address: " << &(MyClassWithFastPimpl::allocatedMemory) << std::endl;
    std::cout << "Initialized class at address: " << pimpl.get() << std::endl;
}

void MyClassWithFastPimpl::doPrintSomething()
{
    pimpl->doPrintMessage();
}

int MyClassWithFastPimpl::returnSomething()
{
    return(pimpl->returnSomething());
}
