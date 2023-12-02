#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <limits.h>
#include "Set.h"

// !Contains , !Modify, !Push, !Pop, !Clear, !IsSubset, !UnionSet, !Intersection, !Difference


// ������������� ������� ���������
void InitializeSet(Set* set) 
{
    set->head = NULL;
}

// ������� ��� ��������, ����������� �� ������ ���������
bool Contains(const Set* set, int value) 
{
    struct Node* current = set->head;
    while (current != NULL) {
        if (current->data == value) {
            return true;
        }
        current = current->next;
    }
    return false;
}

// ������� ��� ���������� ������� � ���������
void Push(Set* set, int value)
{
    if (!Contains(set, value)) 
    {
        struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
        if (newNode == NULL) {
            // ��������� ������ - �� ������� �������� ������
            exit(1);
        }
        newNode->data = value;
        newNode->next = set->head;
        set->head = newNode;
    }
}

// ������� ��� ���������� ������� �� ���������
void Pop(Set* set, int value) 
{
    if (set->head == NULL) {
        return;
    }
    if (set->head->data == value) {
        struct Node* temp = set->head;
        set->head = set->head->next;
        free(temp);
    }
    else {
        struct Node* current = set->head;
        while (current->next != NULL && current->next->data != value) {
            current = current->next;
        }
        if (current->next != NULL) {
            struct Node* temp = current->next;
            current->next = current->next->next;
            free(temp);
        }
    }
}

// ������� ��� ������� ���������
void Clear(Set* set) 
{
    while (set->head != NULL) {
        struct Node* temp = set->head;
        set->head = set->head->next;
        free(temp);
    }
}

// ����������� ������������
bool IsSubset(const Set* set1, const Set* set2)
{
    struct Node* current = set2->head;
    while (current != NULL) {
        if (!Contains(set1, current->data)) {
            return false;
        }
        current = current->next;
    }
    return true;
}

// ������� ��� ����������� ���� ��������
Set UnionSet(const Set* set1, const Set* set2) 
{
    Set result;
    InitializeSet(&result);

    struct Node* current = set1->head;
    while (current != NULL) {
        Push(&result, current->data);
        current = current->next;
    }

    current = set2->head;
    while (current != NULL) {
        Push(&result, current->data);
        current = current->next;
    }

    return result;
}

// ����� ��� ���������� ����������� ���� ��������
Set Intersection(const Set* set1, const Set* set2) 
{
    Set result;
    InitializeSet(&result);
    struct Node* current = set1->head;
    while (current != NULL) {
        if (Contains(set2, current->data)) {
            Push(&result, current->data);
        }
        current = current->next;
    }

    return result;
}

// ������� ��� �������� ���� ��������
Set Difference(const Set* set1, const Set* set2) 
{
    Set result;
    InitializeSet(&result);

    struct Node* current = set1->head;
    while (current != NULL) {
        if (!Contains(set2, current->data)) {
            Push(&result, current->data);
        }
        current = current->next;
    }

    return result;
}

// ������� ��� ��������� ������� � ���������
void Modify(Set* set, int oldValue, int newValue) 
{
    // ������� ������ ��������, ���� ��� ����������
    Pop(set, oldValue);

    // ��������� ����� ��������
    Push(set, newValue);
}

// ������� ��� ����������� ���������
void ShowSet(const Set* set) 
{
    struct Node* current = set->head;
    printf("���������: { ");
    while (current != NULL) {
        printf("%d ", current->data);
        current = current->next;
    }
    printf("}\n");
}

int main() 
{
    system("chcp 1251");
    Set set1, set2;
    InitializeSet(&set1);
    InitializeSet(&set2);
    int key, value, newValue;
    bool isContained, isSubsetResult;
    bool flag = true;
    while (flag)
    {
        do
        {
         printf("1 - �������� ������� � ��������� 1\n"
                "2 - �������� ������� � ��������� 2\n"
                "3 - �������� ������� � ��������� 1\n"
                "4 - ��������� �������������� �������� ��������� 1\n"
                "5 - ���������, �������� �� ��������� �������������\n"
                "6 - ��������� ����������� ��������\n"
                "7 - ������� ������� �� ���������\n"
                "8 - ��������� �����������\n"
                "9 - ��������� ��������\n"
                "10 - �������� ���������\n"
                "11 - �����\n");
            scanf_s("%i", &key);
        } while (key < 1 or key > 11);
        system("cls");
        switch (key) 
        {
        case 1:
            printf("������� ��������, ������� ������ �������� � ��������� 1: ");
            scanf("%d", &value);
            Push(&set1, value);
            break;
        case 2:
            printf("������� ��������, ������� ������ �������� � ��������� 2: ");
            scanf("%d", &value);
            Push(&set2, value);
            break;
        case 3:
            printf("������� ������ ��������, ������� ������ �������� � ��������� 1: ");
            scanf("%d", &value);
            printf("������� ����� ��������: ");
            scanf("%d", &newValue);
            Modify(&set1, value, newValue);
            break;
        case 4:
            printf("������� �������, ������� ������ ��������� �� ��������������: ");
            scanf("%d", &value);
            isContained = Contains(&set1, value);
            printf("����������� �� ������� ��������� 1: %s\n", isContained ? "��" : "���");
            break;
        case 5:
            isSubsetResult = IsSubset(&set1, &set2);
            printf("��������� 1 �������� ������������� ��������� 2: %s\n", isSubsetResult ? "��" : "���");
            break;
        case 6:
            Set unionResult = UnionSet(&set1, &set2);
            printf("����������� �������� ���������.\n");
            ShowSet(&unionResult);
            break;
        case 7:
            printf("������� �������, ������� ������ ������� �� ��������� 1: ");
            scanf("%d", &value);
            Pop(&set1, value);
            break;
        case 8:
            Set intersectionResult = Intersection(&set1, &set2);
            printf("����������� �������� ���������.\n");
            ShowSet(&intersectionResult);
            break;
        case 9:
            Set differenceResult = Difference(&set1, &set2);
            printf("�������� �������� ���������.\n");
            ShowSet(&differenceResult);
            break;
        case 10:
            Clear(&set1);
            Clear(&set2);
            break;
        case 11:
            return 0;
        }
        ShowSet(&set1);
        ShowSet(&set2);
    }

    return 0;
}
