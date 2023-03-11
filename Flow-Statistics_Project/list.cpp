//
//  list.cpp
//
//  Created by Mariya Podgaietska on 25.11.2022.
//
#include <fstream>
#include <stdlib.h>
#include <iostream>
#include "list.hpp"

using namespace std;

FlowList::FlowList(){
    head = 0;
}

Node *FlowList::add(const ListItem& newItem){
    Node *newNode = new Node;
    newNode->item.year = newItem.year;
    newNode->item.flow = newItem.flow;
    
    if (head == nullptr){
        head = newNode;
        return head;
    }
    Node *current = head;
    Node *previous = nullptr;
    while (current != nullptr && current->item.year < newNode->item.year){
        previous = current;
        current = current->next;
    }
    if (current == nullptr){
        previous->next = newNode;
        return newNode;
    }
    if (current->item.year == newItem.year){
        return nullptr;
    }
    if (previous == nullptr){
        head = newNode;
        newNode->next = current;
        return newNode;
    }
    previous->next = newNode;
    newNode->next = current;
    return newNode;
}

Node *FlowList::_delete(int year){
    Node *current = head;
    Node *previous = nullptr;
    while (current != nullptr && current->item.year != year){
        previous = current;
        current = current->next;
    }
    if (current == nullptr){
        return nullptr;
    }
    if (previous == nullptr){
        head = current->next;
        current->next = nullptr;
        return current;
    }
    previous->next = current->next;
    current->next = nullptr;
    return current;
}
