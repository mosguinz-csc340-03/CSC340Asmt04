//  LinkedBag.cpp
//  Created by Frank M. Carrano and Timothy M. Henry.
//	Updated by Duc Ta
//  Copyright (c) 2017 Pearson Education, Hoboken, New Jersey.

#include <cstddef>
#include "Node.h"
#include "LinkedBag.h"

template<typename ItemType>
LinkedBag<ItemType>::LinkedBag() : headPtr(nullptr), itemCount(0) {}

template<typename ItemType>
LinkedBag<ItemType>::LinkedBag(const LinkedBag<ItemType> &aBag) {
    itemCount = aBag.itemCount;
    Node<ItemType> *origChainPtr = aBag.headPtr;

    if (origChainPtr == nullptr) {
        headPtr = nullptr;
    } else {
        headPtr = new Node<ItemType>();
        headPtr->setItem(origChainPtr->getItem());

        Node<ItemType> *newChainPtr = headPtr;
        origChainPtr = origChainPtr->getNext();

        while (origChainPtr != nullptr) {
            ItemType nextItem = origChainPtr->getItem();
            Node<ItemType> *newNodePtr = new Node<ItemType>(nextItem);
            newChainPtr->setNext(newNodePtr);
            newChainPtr = newChainPtr->getNext();
            origChainPtr = origChainPtr->getNext();
        }

        newChainPtr->setNext(nullptr);
    }
}

template<typename ItemType>
LinkedBag<ItemType>::~LinkedBag() {
    clear();
}

template<typename ItemType>
bool LinkedBag<ItemType>::isEmpty() const {
    return itemCount == 0;
}

template<typename ItemType>
int LinkedBag<ItemType>::getCurrentSize() const {
    return itemCount;
}

template<typename ItemType>
bool LinkedBag<ItemType>::add(const ItemType &newEntry) {
//    Node<ItemType> *nextNodePtr = new Node<ItemType>();

    auto newNode{std::make_unique<Node<ItemType>>(newEntry)};
    if (headPtr) {
        newNode->setNext(std::move(headPtr));
    }
    headPtr = std::move(newNode);
    itemCount++;
    return true;

//    nextNodePtr->setItem(newEntry);
//    nextNodePtr->setNext(headPtr);
//    headPtr = nextNodePtr;
//    itemCount++;
//    return true;
}

template<typename ItemType>
std::vector<ItemType> LinkedBag<ItemType>::toVector() const {
    std::vector<ItemType> bagContents;
    Node<ItemType> *curPtr = headPtr.get();
    int counter = 0;

    while ((curPtr != nullptr) && (counter < itemCount)) {
        bagContents.push_back(curPtr->getItem());
        curPtr = curPtr->getNext();
        counter++;
    }

    return bagContents;
}

template<typename ItemType>
bool LinkedBag<ItemType>::remove(const ItemType &anEntry) {
    Node<ItemType> *entryNodePtr = getPointerTo(anEntry);
    bool canRemoveItem = !isEmpty() && (entryNodePtr != nullptr);

    if (canRemoveItem) {
        entryNodePtr->setItem(headPtr->getItem());
        headPtr = std::move(headPtr->next);
        itemCount--;
    }

    return canRemoveItem;
}

template<typename ItemType>
void LinkedBag<ItemType>::clear() {
//    Node<ItemType> *nodeToDeletePtr = headPtr;
//
//    while (headPtr != nullptr) {
//        headPtr = headPtr->getNext();
//        nodeToDeletePtr->setNext(nullptr);
//        delete nodeToDeletePtr;
//        nodeToDeletePtr = headPtr;
//
    headPtr = nullptr;
    itemCount = 0;
}

template<typename ItemType>
int LinkedBag<ItemType>::getFrequencyOf(const ItemType &anEntry) const {
    int frequency = 0;
    int counter = 0;
    Node<ItemType> *curPtr = headPtr;

    while ((curPtr != nullptr) && (counter < itemCount)) {
        if (anEntry == curPtr->getItem()) {
            frequency++;
        }
        counter++;
        curPtr = curPtr->getNext();
    }

    return frequency;
}

template<typename ItemType>
bool LinkedBag<ItemType>::contains(const ItemType &anEntry) const {
    return (getPointerTo(anEntry) != nullptr);
}

template<typename ItemType>
Node<ItemType> *LinkedBag<ItemType>::getPointerTo(const ItemType &anEntry) const {

    Node<ItemType> *curPtr = headPtr.get();
    while (curPtr) {
        if (anEntry == curPtr->getItem()) {
            return curPtr;
        }
        curPtr->getNext().get();
    }

//    bool found = false;
//    Node<ItemType> *curPtr = headPtr;
//
//    while (curPtr) {
//        if (anEntry == curPtr->getItem()) {
//            return curPtr;
//        }
//        curPtr->getNext().get();
//    }
//
//    while (!found && (curPtr != nullptr)) {
//        if (anEntry == curPtr->getItem()) {
//            found = true;
//        } else {
//            curPtr = curPtr->getNext();
//        }
//    }
//
//    return curPtr;
} 