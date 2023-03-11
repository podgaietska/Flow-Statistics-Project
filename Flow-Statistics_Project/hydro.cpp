//
//  hydro.cpp
//
//  Created by Mariya Podgaietska on 25.11.2022.
//
#include <fstream>
#include <sstream>
#include <stdlib.h>
#include <iostream>
#include "list.hpp"
#include "hydro.hpp"

using namespace std;

FlowList* flowList;

void displayHeader(){
    cout<<"Program: Flow Studies\n";
    cout<<"Version: 1.0\n";
    cout<<"Produced by: Mariya Podgaietska\n";
}

int readData(){
    const char *infile = "/flow.txt";
    ifstream inObj;
    inObj.open(infile);
    int count = 0;
    if (inObj.fail()){
        cout<<"Error: the file could not be opened"<<endl;
        exit(1);
    }
    else{
        string input;
        while(getline(inObj,input)){
            string year , flow;
            int i = 0;
            while(input[i]!=' ')year+=input[i++];i++;
            while(i<input.size())flow+=input[i++];
            // now create a new listitem
            struct ListItem listItem = {stoi(year),stod(flow)};
            count++;
            flowList->add(listItem);
        }
        inObj.close();
    }
    return count;
}
void SaveData(){
    ofstream out;
    out.open("/flow.txt",ios::trunc);
    Node* head = flowList->head;
    while(head!=nullptr){
        string text =  to_string(head->item.year) + " " + to_string(head->item.flow);
        out<<text<<"\n";
        head=head->next;
    }
    out.close();
    cout<<"Data are saved into the file"<<endl;
}
int menu(){
    cout<<"Please select on the following operations.\n";
    cout<<"1. Display flow,list and the average\n";
    cout<<"2. Add data.\n";
    cout<<"3. Save data into the file.\n";
    cout<<"4. Remove data.\n";
    cout<<"5. Quit.\n";
    cout<<"Enter your choice (1, 2, 3, 4, of 5):";
    int choice; cin>>choice;
    return choice;
}
double Average(){
    Node* head = flowList->head;
    double sum = 0 , count = 0;
    while(head!=nullptr){
        sum += head->item.flow;
        count++;
        head = head->next;
    }
    return (count==0) ? 0 : (sum/count);
}
void display(){
    cout<<"Year  "<<"Flow\n";
    Node* head = flowList->head;
    while(head!=nullptr){
        cout<<head->item.year<<"   "<<head->item.flow<<"\n";
        head = head->next;
    }
    cout<<"The annual average of the flow is: "<<Average()<<" billions of cubic meter.\n";
}

void addData(){
    int year; double flow;
    cout<<"Please enter a year: "; cin>>year;
    cout<<"Please enter the flow: ";cin>>flow;
    struct ListItem listItem = {year,flow};
    Node* n=flowList->add(listItem);
    if(n==nullptr){
        cout<<"Error: duplicate data.\n";
    }
    else cout<<"New record inserted successfully.\n";
}

void removeData(){
    int year;
    cout<<"Please enter the year that you want to remove: ";cin>>year;
    Node* r=flowList->_delete(year);
    if(r==nullptr){
        cout<<"Error: No such data.\n";
    }
    else{
        cout<<"Record was successfully removed.\n";
    }
}

void pressEnter(){
    cout<<"\n<<< Press Enter to Continue >>>\n";
    cin.get();
}


int main(){
    flowList = new FlowList();
    int numRecord;
    displayHeader();
    numRecord = readData();
    int quit = 0;
    while(1){
        switch (menu())
        {
        case 1:
            display();
            pressEnter();
            break;
        case 2:
            addData();
            pressEnter();
            break;
        case 3:
            SaveData();
            pressEnter();
            break;
        case 4:
            removeData();
            pressEnter();
            break;
        case 5:
            cout<<"\nProgram Terminated.\n\n";
            quit=1;
            break;
        default:
            cout<<"\nNot a valid input.\n";
        }
        if(quit==1)break;
    }
}
