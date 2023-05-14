//
//  Sequence.hpp
//  CS32 Project 2
//
//  Created by Arash Dewan on 4/25/23.
//

#ifndef Sequence_hpp
#define Sequence_hpp

#include <string>

using ItemType = std::string;

class Sequence
{
public:
    Sequence();
    ~Sequence();
    Sequence(const Sequence& other);
    Sequence& operator=(const Sequence& other);
    bool empty() const;
    int size() const;
    int insert(int pos, const ItemType& value);
    int insert(const ItemType& value);
    bool erase(int pos);
    int remove(const ItemType& value);
    bool get(int pos, ItemType& value) const;
    bool set(int pos, const ItemType& value);
    int find(const ItemType& value) const;
    void swap(Sequence& other);
    void dump() const;
private:
    struct Node
    {
        ItemType val;
        Node* next;
        Node* prev;
    };
    Node* head;
    Node* tail;
    int s_size;
};
    
int subsequence(const Sequence& seq1, const Sequence& seq2);
void concatReverse(const Sequence& seq1, const Sequence& seq2, Sequence& result);


#endif /* Sequence_hpp */
