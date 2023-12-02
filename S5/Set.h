#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <limits.h>

struct Node {
    int data;
    struct Node* next;
};

typedef struct {
    struct Node* head;
} Set;

void InitializeSet(Set* set);
bool Contains(const Set* set, int value);
void Push(Set* set, int value);
void Pop(Set* set, int value);
void Clear(Set* set);
bool IsSubset(const Set* set1, const Set* set2);
Set UnionSet(const Set* set1, const Set* set2);
Set Intersection(const Set* set1, const Set* set2);
Set Difference(const Set* set1, const Set* set2);
void Modify(Set* set, int oldValue, int newValue);
void ShowSet(const Set* set);