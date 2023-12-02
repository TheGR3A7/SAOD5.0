#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <limits.h>
#include "Set.h"

// !Contains , !Modify, !Push, !Pop, !Clear, !IsSubset, !UnionSet, !Intersection, !Difference


// Инициализация пустого множества
void InitializeSet(Set* set) 
{
    set->head = NULL;
}

// Функция для проверки, принадлежит ли объект множеству
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

// Функция для добавления объекта в множество
void Push(Set* set, int value)
{
    if (!Contains(set, value)) 
    {
        struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
        if (newNode == NULL) {
            // Обработка ошибки - не удалось выделить память
            exit(1);
        }
        newNode->data = value;
        newNode->next = set->head;
        set->head = newNode;
    }
}

// Функция для исключения объекта из множества
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

// Функция для очистки множества
void Clear(Set* set) 
{
    while (set->head != NULL) {
        struct Node* temp = set->head;
        set->head = set->head->next;
        free(temp);
    }
}

// Определение подмножества
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

// Функция для объединения двух множеств
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

// Метод для вычисления пересечения двух множеств
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

// Функция для разности двух множеств
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

// Функция для изменения объекта в множестве
void Modify(Set* set, int oldValue, int newValue) 
{
    // Удаляем старое значение, если оно существует
    Pop(set, oldValue);

    // Вставляем новое значение
    Push(set, newValue);
}

// Функция для отображения множества
void ShowSet(const Set* set) 
{
    struct Node* current = set->head;
    printf("Множество: { ");
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
         printf("1 - добавить элемент в множество 1\n"
                "2 - добавить элемент в множество 2\n"
                "3 - изменить элемент в множестве 1\n"
                "4 - проверить принадлежность элемента множеству 1\n"
                "5 - проверить, является ли множество подмножеством\n"
                "6 - выполнить объединение множеств\n"
                "7 - удалить элемент из множества\n"
                "8 - вычислить пересечение\n"
                "9 - вычислить разность\n"
                "10 - очистить множества\n"
                "11 - выйти\n");
            scanf_s("%i", &key);
        } while (key < 1 or key > 11);
        system("cls");
        switch (key) 
        {
        case 1:
            printf("Введите значение, которое хотите добавить в множество 1: ");
            scanf("%d", &value);
            Push(&set1, value);
            break;
        case 2:
            printf("Введите значение, которое хотите добавить в множество 2: ");
            scanf("%d", &value);
            Push(&set2, value);
            break;
        case 3:
            printf("Введите старое значение, которое хотите изменить в множестве 1: ");
            scanf("%d", &value);
            printf("Введите новое значение: ");
            scanf("%d", &newValue);
            Modify(&set1, value, newValue);
            break;
        case 4:
            printf("Введите элемент, который хотите проверить на принадлежность: ");
            scanf("%d", &value);
            isContained = Contains(&set1, value);
            printf("Принадлежит ли элемент множеству 1: %s\n", isContained ? "Да" : "Нет");
            break;
        case 5:
            isSubsetResult = IsSubset(&set1, &set2);
            printf("Множество 1 является подмножеством множества 2: %s\n", isSubsetResult ? "Да" : "Нет");
            break;
        case 6:
            Set unionResult = UnionSet(&set1, &set2);
            printf("Объединение множеств выполнено.\n");
            ShowSet(&unionResult);
            break;
        case 7:
            printf("Введите элемент, который хотите удалить из множества 1: ");
            scanf("%d", &value);
            Pop(&set1, value);
            break;
        case 8:
            Set intersectionResult = Intersection(&set1, &set2);
            printf("Пересечение множеств выполнено.\n");
            ShowSet(&intersectionResult);
            break;
        case 9:
            Set differenceResult = Difference(&set1, &set2);
            printf("Разность множеств выполнена.\n");
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
