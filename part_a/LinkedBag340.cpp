#include <random>

#include "LinkedBag.h"

template<typename ItemType>
bool LinkedBag<ItemType>::removeSecondNode340() {
    if (itemCount < 2) { return false; }
    return remove(headPtr->getNext()->getItem());
}

template<typename ItemType>
bool LinkedBag<ItemType>::addEnd340(const ItemType &toAdd) {
    if (headPtr == nullptr) { return false; }
    Node<ItemType> *thisNode = headPtr;
    while (thisNode->getNext() != nullptr) {
        thisNode = thisNode->getNext();
    }
    // TODO: "new" vs declaring pointer and passing to setNext()?
    thisNode->setNext(new Node(toAdd));
    itemCount++;
    return true;
}

template<typename ItemType>
int LinkedBag<ItemType>::getCurrentSize340Iterative() const {
    int count;
    Node<ItemType> *thisNode = headPtr;
    while (thisNode->getNext() != nullptr) {
        thisNode = thisNode->getNext();
        count++;
    }
    return count;
}

template<typename ItemType>
int LinkedBag<ItemType>::getCurrentSize340Recursive() const {
    if (headPtr == nullptr) { return 0; }
    Node<ItemType> *thisNode = headPtr;
    return getCurrentSize340RecursiveHelper(thisNode);
}

template<typename ItemType>
int LinkedBag<ItemType>::getCurrentSize340RecursiveHelper(Node<ItemType> *thisNode) const {
    if (thisNode == nullptr) { return 0; }
    return 1 + getCurrentSize340RecursiveHelper(thisNode->getNext());
}

template<typename ItemType>
int LinkedBag<ItemType>::getCurrentSize340RecursiveNoHelper() const {
    // TODO: can static be avoided?
    static Node<ItemType> *thisNode = headPtr;
    if (thisNode == nullptr) {
        delete thisNode;
        return 0;
    }
    thisNode = thisNode->getNext();
    return 1 + getCurrentSize340RecursiveNoHelper();
}

template<typename ItemType>
int LinkedBag<ItemType>::getFrequencyOf340Recursive(const ItemType &target) const {
    Node<ItemType> *thisNode = headPtr;
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
    static Node<ItemType> *thisNode = headPtr;
    if (thisNode == nullptr) {
        thisNode = headPtr;
        return 0;
    }
    int a = thisNode->getItem() == target ? 1 : 0;
    thisNode = thisNode->getNext();
    return a + getFrequencyOf340RecursiveNoHelper(target);
}

template<typename ItemType>
ItemType LinkedBag<ItemType>::removeRandom340() {
    int i;
    Node<ItemType> *toRemove = headPtr;

    while (i > rand() % itemCount) {
        toRemove = toRemove->getNext();
    }
    ItemType itemToRemove = toRemove->getItem();
    return remove(itemToRemove) ? itemToRemove : nullptr;
}

