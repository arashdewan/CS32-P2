//
//  Sequence.cpp
//  CS32 Project 2
//
//  Created by Arash Dewan on 4/25/23.
//

#include <iostream>
#include "Sequence.h"

//constructor
Sequence::Sequence()
{
    this->head = nullptr;
    this->tail = nullptr;
    this->s_size = 0;
}
//destructor
Sequence::~Sequence()
{
    if (empty()==false){
        Node* i = head;
        while (i != nullptr)
        {
            Node* i_next = i->next;
            delete i;
            i = i_next;
        }
    }
    this->head = nullptr;
    this->tail = nullptr;
    this->s_size = 0;
}
//copy constructor
Sequence::Sequence(const Sequence& other)
{
    if(other.head == nullptr)
    {
        head = nullptr;
        tail = nullptr;
        s_size = 0;
        return;
    }
    
    this->head = nullptr;
    this->tail = nullptr;
    this->s_size = 0;
    
    int size = other.size();
    for(int i = 0; i < size; i++)
    {
        ItemType x;
        other.get(i, x);
        insert(i, x);
    }
}
//assignment operator
Sequence& Sequence::operator= (const Sequence& other)
{
    if(this == &other){
        return *this;
    }
    else{
        Sequence temp(other);
        this->swap(temp);
        return *this;
    }
}
//return true if sequence is empty, otherwise false
bool Sequence::empty() const
{
    if (head == nullptr && tail == nullptr && s_size == 0)
    {return true;}
    return false;
}
//return the number of items in the sequence
int Sequence::size() const
{
    return s_size;
}
//inserts node into sequence based on position
int Sequence::insert(int pos, const ItemType &value)
{
    if(pos > s_size || pos < 0)
     {
         return -1;
     }

     if(head == nullptr && pos == 0)
     {
         Node* nNode = new Node;
         nNode->val = value;
         head = nNode;
         tail = nNode;

         nNode->next = nullptr;
         nNode->prev = nullptr;
     }
     else if (pos == s_size)
     {
         Node* nNode = new Node;
         nNode->val = value;
         nNode->next = nullptr;
         nNode->prev = tail;
         tail->next = nNode;
         tail = nNode;
     }
     else if(head != nullptr && pos == 0)
     {
         Node* nNode = new Node;
         nNode->val = value;

         nNode->next = head;
         nNode->prev = nullptr;

         head->prev = nNode;
         head = nNode;
     }
     else if (pos > 0 && pos < s_size)
     {
         Node* nNode = new Node;
         nNode->val = value;

         int counter = 0;
         Node* temp = head;
         while (counter != pos)
         {
             temp = temp->next;
             counter++;
         }
         nNode->next = temp;
         nNode->prev = temp->prev;
         temp->prev->next = nNode;
         temp->prev = nNode;
     }
     s_size++;
     return pos;
    }


//inserts node without given position
int Sequence::insert(const ItemType &value)
{
    int p = 0;
    Node* current = head;
    if (head == nullptr && s_size == 0)//adding node to the front if list is empty
    {
        this->insert(p, value);
        return p;
    }
    while (current != nullptr)//adding node to list when val >= value because list is not empty
    {
        if(current->val >= value)
        {
            this->insert(p, value);
            return p;
        }
        p++;
        current = current->next;
    }
    this->insert(p, value);
    return p;
}
bool Sequence::erase(int pos)
{
    if(s_size == 0 || pos < 0 || pos > s_size)
    {
        return false;
    }
    else
    {
        if (s_size==1)//deletes head because list is only one node long
        {
            delete head;
            s_size--;
            return true;
        }
        else if(pos == 0)//deleting the first node with size bigger than one
        {
            Node* temp_head = head;
            head = head->next;
            delete temp_head;
            head->prev = nullptr;
            s_size--;
            return true;
        }
        else//deleting node by looping through to find the position
        {
            Node* current = head;
            for (int i = 0; i < pos && current->next != nullptr; i++)
            {
                current = current->next;
            }
            if(current==tail) //if node is at end of list, makes tails previous the new tail and deletes the last node
            {
                Node* temp_tail = tail;
                tail = tail->prev;
                tail->next = nullptr;
                delete temp_tail;
                s_size--;
                return true;
            }
            else //if node is somewhere in the index of the list, update prev and nexts of list and delete node in current position
            {
                Node* temp = current->next;
                temp->prev = current->prev;
                current->prev->next = temp;
                delete current;
                s_size--;
                return true;
            }
        }
    }
}
//erasing all nodes that = value
int Sequence::remove(const ItemType &value)
{
    int counter = 0;
    while (find(value) != -1)
    {
        erase(find(value));
        counter++;
    }
    return counter;
}
//copying value of node at the position
bool Sequence::get(int pos, ItemType &value) const
{
    if(pos < 0 || pos >= s_size)
    {
        return false;
    }
    Node* x = head;
    int counter;
    for(counter = 0; counter != pos; counter++)
    {
        x = x->next;
    }
    value = x->val;
    return true;
}
//replacing node at the given position with the value
bool Sequence::set(int pos, const ItemType &value)
{
    if(pos < 0 || pos >= s_size || head == nullptr)
    {
        return false;
    }
    Node* p = head;
    for (int i = 0; i < pos && p != nullptr; i++)
    {
        p = p->next;
    }
    p->val = value;
    return true;
}
//returning the position of a value if found
int Sequence::find(const ItemType &value) const
{
    Node* current = head;
    int p = 0;
    while (current != nullptr)
    {
        if(current->val == value)
        {
            return p;
        }
        p++;
        current = current->next;
    }
    return -1;
}
//exchanging the contents of a sequence with other, by first swapping heads, then tails, then sizes
void Sequence::swap(Sequence &other)
{
    Node* temp_head = other.head;
    other.head = head;
    head = temp_head;
    
    Node* temp_tail = other.tail;
    other.tail = tail;
    tail = temp_tail;
    
    int temp_size = other.s_size;
    other.s_size = s_size;
    s_size = temp_size;
}
//for testing purposes
void Sequence::dump() const
{
    Node* test = head;
    
    for (int i = 0; i < s_size; i++)
    {
        std::cerr << "prev: " << test->prev << std::endl;
        std::cerr << test << std::endl;
        std::cerr << "next: " << test->next << std::endl;
    }
    
    std::cerr << "full list:" << std::endl;
    for (int i = 0; i < s_size; i++)
    {
        std::cerr << test->val << std::endl;
        test = test->next;
    }
}

//tries to find if seq2 is a smaller subset of seq1
int subsequence(const Sequence& seq1, const Sequence& seq2)
{
    if(seq1.empty() == true || seq2.empty() == true || seq2.size() > seq1.size())
    {
        return -1;
    }
    ItemType s1_val;
    ItemType s2_val;
    for(int i = 0; i < seq1.size(); i++) //loop that iterates to see if node in seq1 matches first node in seq2
    {
        if ((seq1.size() - seq2.size() - i) < 0)
        {
            break;
        }
        seq1.get(i, s1_val);
        seq2.get(0, s2_val);
        if(s1_val == s2_val)
        {
            for(int j=0; j < seq2.size(); j++)
            {
                seq1.get(i+j, s1_val);
                seq2.get(j, s2_val);
                if (s1_val != s2_val)
                {
                    break;
                }
                else if(j == seq2.size() - 1)
                {
                    return i;
                }
            }
        }
    }
    return -1;
}
void concatReverse(const Sequence& seq1, const Sequence& seq2, Sequence& result)
{
    while(result.size() > 0)
    {
        result.erase(0);
    }
    if (seq1.empty() && seq2.empty())
    {
        return;
    }
    else if (seq1.empty())
    {
        int pos = 0;
        Sequence temp;
        ItemType v;
        for (int i = seq2.size() - 1; i >= 0; i--)
        {
            if (seq2.get(i,v))
            {
                temp.insert(pos, v);
                pos++;
            }
        }
        result = temp;
    }
    else if (seq2.empty())
    {
        int pos = 0;
        Sequence temp;
        ItemType v;
        for (int i = seq1.size() - 1; i >= 0; i--)
        {
            if (seq1.get(i,v))
            {
                temp.insert(pos, v);
                pos++;
            }
        }
        result = temp;
    }
    else
    {
        int pos = 0;
        Sequence temp;
        ItemType v1;
        ItemType v2;
        for (int i = seq1.size() - 1; i >= 0; i--)
        {
            if (seq1.get(i, v1))
            {
                temp.insert(pos, v1);
                pos++;
            }
        }
        
        for (int j = seq2.size()-1; j>=0; j--)
        {
            if (seq2.get(j, v2))
            {
                temp.insert(pos, v2);
                pos++;
            }
        }
        result = temp;
    }
}
