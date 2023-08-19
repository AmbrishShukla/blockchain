#include <iostream>
using namespace std;

class node
{
public:
    string data;
    string currdata;
    string prevdata;
    node *next;
    node *prev;

    node(string data)
    {
        this->data = data;
        next = NULL;
        prev = NULL;
    }
    node(string data, string currdata)
    {
        this->data = data;
        this->prevdata = prevdata;
        this->currdata = currdata;
        next = NULL;
        prev = NULL;
    }
    node(string data, string currdata, string prevdata)
    {
        this->data = data;
        this->prevdata = prevdata;
        this->currdata = currdata;
        next = NULL;
        prev = NULL;
    }
};