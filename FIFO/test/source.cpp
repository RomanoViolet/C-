#include "header.hpp"
#include <iostream>
void MyClass::update_a()
{
    this->a_ = 4;
    std::cout << "a: " << this->a_ << std::endl;
}
