#include <vector>
#include <string>
#include <memory>
#include <iostream>

#include "Include.h"

int main() {
    // A small vector of small objects to test the bag
    auto items{std::make_unique<std::vector<std::string>>()};
    items->insert(items->end(),
                  {"#-END", "5-FIVE", "4-FOUR", "4-FOUR", "3-THREE", "2-TWO", "1-ONE", "0-ZERO", "#-BEGIN"});

    std::cout << "Convert heavy vectors to a linked bag using `LinkedBag<T>::fromVector()`" << std::endl;
    std::cout << "The function takes ownership of the vector and is destroyed once it finishes." << std::endl;
    auto newBag = LinkedBag<std::string>::fromVector(std::move(items));

    std::cout << "This bag contains " << newBag->getCurrentSize() << " items." << std::endl;

    std::cout << "Clearing the bag..." << std::endl << std::endl;
    newBag->clear();

    std::cout << "\nThe bag is now going out of scope..." << std::endl;

}