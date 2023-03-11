//
//  list.hpp
//  Lab 8 ex C
//
//  Created by Mariya Podgaietska on 25.11.2022.
//
#include <fstream>
#include <iostream>

using namespace std;

#ifndef list_hpp
#define list_hpp

struct ListItem {
    int year;
    double flow;

};

struct Node{
    ListItem item;
    Node *next;
    
};

class FlowList{
public:
    FlowList();
    Node *head;
    Node* add(const ListItem& newItem);
    Node* _delete(int year);

    
};

#endif /* list_hpp */
