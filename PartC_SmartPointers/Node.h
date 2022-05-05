//	Node.h
//  Created by Frank M. Carrano and Timothy M. Henry.
//	Updated by Duc Ta
//  Copyright (c) 2017 Pearson Education, Hoboken, New Jersey.

#include <memory>

#pragma once

template<typename ItemType>
class Node {
 public:
    Node();
    ~Node();
    Node(const ItemType &);
    Node(const ItemType &, std::unique_ptr<Node<ItemType>>);
    void setItem(const ItemType &);
    void setNext(std::unique_ptr<Node<ItemType>>);
    ItemType getItem() const;
    std::unique_ptr<Node<ItemType>> getNext() const;

 private:
    ItemType item{};             // A data item
    std::unique_ptr<Node<ItemType>> next{nullptr}; // Pointer to next node
};