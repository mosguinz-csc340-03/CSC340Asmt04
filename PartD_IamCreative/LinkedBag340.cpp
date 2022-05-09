#include <cstdlib>
#include <ctime>

#include "LinkedBag.h"

template<typename ItemType>
bool LinkedBag<ItemType>::removeSecondNode340() {
    if (itemCount < 2) { return false; }
    return remove(headPtr->getNext()->getItem());
}

template<typename ItemType>
bool LinkedBag<ItemType>::addEnd340(const ItemType &toAdd) {
    if (headPtr == nullptr) {
        headPtr = std::make_unique<Node<ItemType>>(toAdd);
        return true;
    }

    Node<ItemType> *thisNode = headPtr.get();
    while (thisNode->getNext() != nullptr) {
        thisNode = thisNode->getNext();
    }
    thisNode->setNext(std::make_unique<Node<ItemType>>(toAdd));
    itemCount++;
    return true;
}

template<typename ItemType>
int LinkedBag<ItemType>::getCurrentSize340Iterative() const {
    int count;
    Node<ItemType> *thisNode = headPtr.get();
    while (thisNode->getNext() != nullptr) {
        thisNode = thisNode->getNext();
        count++;
    }
    return count;
}

template<typename ItemType>
int LinkedBag<ItemType>::getCurrentSize340Recursive() const {
    if (headPtr == nullptr) { return 0; }
    Node<ItemType> *thisNode = headPtr.get();
    return getCurrentSize340RecursiveHelper(thisNode);
}

template<typename ItemType>
int LinkedBag<ItemType>::getCurrentSize340RecursiveHelper(Node<ItemType> *thisNode) const {
    if (thisNode == nullptr) { return 0; }
    return 1 + getCurrentSize340RecursiveHelper(thisNode->getNext());
}

template<typename ItemType>
int LinkedBag<ItemType>::getCurrentSize340RecursiveNoHelper() const {
    static Node<ItemType> *thisNode = headPtr.get();
    if (thisNode == nullptr) {
        delete thisNode;
        return 0;
    }
    thisNode = thisNode->getNext();
    return 1 + getCurrentSize340RecursiveNoHelper();
}

template<typename ItemType>
int LinkedBag<ItemType>::getFrequencyOf340Recursive(const ItemType &target) const {
    Node<ItemType> *thisNode = headPtr.get();
    return getFrequencyOf340RecursiveHelper(thisNode, target);
}

template<typename ItemType>
int LinkedBag<ItemType>::getFrequencyOf340RecursiveHelper(Node<ItemType> *thisNode, const ItemType &target) const {
    if (thisNode == nullptr) {
        delete thisNode;
        return 0;
    }
    int a = thisNode->getItem() == target ? 1 : 0;
    thisNode = thisNode->getNext();
    return a + getFrequencyOf340RecursiveHelper(thisNode, target);
}

template<typename ItemType>
int LinkedBag<ItemType>::getFrequencyOf340RecursiveNoHelper(const ItemType &target) const {
    static Node<ItemType> *thisNode = headPtr.get();
    if (thisNode == nullptr) {
        thisNode = headPtr.get();
        return 0;
    }
    int a = thisNode->getItem() == target ? 1 : 0;
    thisNode = thisNode->getNext();
    return a + getFrequencyOf340RecursiveNoHelper(target);
}

template<typename ItemType>
ItemType LinkedBag<ItemType>::removeRandom340() {
    int i;
    Node<ItemType> *thisNode = headPtr.get();

    std::srand(std::time(0));
    int toRemove = std::rand() % itemCount;
    while (i < toRemove) {
        thisNode = thisNode->getNext();
        i++;
    }
    ItemType itemToRemove = thisNode->getItem();
    return remove(itemToRemove) ? itemToRemove : nullptr;
}

/**
 * Create a LinkedBag instance from a given unique_ptr containing a vector.
 * @tparam ItemType The type matching the provided vector's template arg.
 * @return A unique_ptr of the created LinkedBag instance.
 */
template<typename ItemType>
std::unique_ptr<LinkedBag<ItemType>> LinkedBag<ItemType>::fromVector(std::unique_ptr<std::vector<ItemType>> vec) {
    auto newBag{std::make_unique<LinkedBag<ItemType>>()};
    std::vector<std::string>::const_iterator cItr;
    for (cItr = vec->begin(); cItr != vec->end(); cItr++) {
        newBag->add(*cItr);
    }
    return std::move(newBag);
}
