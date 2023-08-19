#include <bits/stdc++.h>
using namespace std;
#include "1_node.cpp"

void print(node *head)
{
    node *temp = head;
    while (temp != NULL)
    {
        cout << (*temp).data << " ";
        temp = (*temp).next;
    }
    cout << endl;
    cout << "reverse print" << endl;
    temp = head;
    while (temp->next != NULL)
    {
        temp = temp->next;
    }
    while (temp != NULL)
    {
        cout << temp->data << " ";
        temp = temp->prev;
    }
}

node *takeinput()
{
    int data;
    cin >> data;
    node *head = NULL;
    while (data != -1)
    {
        node *newnode = new node(data);
        if (head == NULL)
        {
            head = newnode;
        }
        else
        {
            node *temp = head;
            while ((*temp).next != NULL)
            {
                temp = (*temp).next;
            }
            temp->next = newnode;
            newnode->prev = temp;
        }
        cin >> data;
    }
    return head;
}

node *takeinputatend(node *head)
{
    node *temp = head;
    while (temp->next != NULL)
    {
        temp = temp->next;
    }
    node *mid = takeinput();
    temp->next = mid;
    return head;
}

int main()
{
    cout << "enter the linked list " << endl;
    node *head = takeinput();
    print(head);
    cout << endl;

    cout << "do you want to insert and node at end " << endl;
    cout << "yes 1: no 0" << endl;
    int n;
    cin >> n;
    if (n == 1)
    {
        cout << "write the nodes to be added" << endl;
        takeinputatend(head);
    }

    cout << "your new linked list is :" << endl;
    print(head);

    return 0;
}