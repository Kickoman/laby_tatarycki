//-------------------------------------------------------------------------—

#include <conio.h>
#include <vcl.h>
#pragma hdrstop
#include <math.h>
#include <iostream>


using namespace std;

struct Queue
{
    int value;
    Queue *prev, *next;
} * _begin, *_end, *t;

void task(Queue *first, Queue *last, int kod) // task for the defence
{
    Queue *minimum, *maximum;
    if (kod == 1)
        minimum = maximum = last;
    else
        minimum = maximum = first;
    int minpos = 1, maxpos = 1;
    int i = 1;
    Queue *cur;
    if (kod == 0)
        cur = first;
    else
        cur = last;

    while (cur)
    {
        if (cur->value > maximum->value)
        {
            maximum = cur;
            maxpos = i;
        }
        if (cur->value < minimum->value)
        {
            minimum = cur;
            minpos = i;
        }
        i++;
        if (kod == 0)
                cur = cur->next;
        else
                cur = cur->prev;
    }
    cout << "Maximum number position = " << maxpos << endl;
    cout << "Minimum number position = " << minpos << endl;
}

void addToFront(Queue **first, Queue **last, int value)
{
    Queue *temp = new Queue;
    temp->value = value;
    if (*first == NULL) {
        *first = *last = temp;
    }
    else {
        (*first)->prev = temp;
        temp->next = *first;
        *first = temp;
    }
}

void addToBack(Queue **first, Queue **last, int value)
{
    Queue *temp = new Queue;
    temp->value = value;
    if (*first == NULL) {
        *first = *last = temp;
    }
    else {
        (*last)->next = temp;
        temp->prev = *last;
        *last = temp;
    }
}

Queue *pop(Queue *parent, int &out)
{
    if (parent == NULL) return NULL;
    out = parent->value;
    Queue *tmp = parent->next;
    delete parent;
    return tmp;
}

void Del_All(Queue **p)
{
    Queue *t;
    while (*p != NULL)
    {
        t = *p;
        *p = (*p)->next;
        delete t;
    }
}

void print(int code, Queue *t)
{
    while (t != NULL)
    {
        cout << t->value << ", ";
        if (code == 0) t = t->next;
        else
            t = t->prev;
    }
    cout << "\n";
}


void delFromBack(Queue **first, Queue **last)
{
    if (*first == *last)
    {
        delete *first;
        *last = NULL;
        return;
    }

    Queue *tmp = (*last)->prev;
    delete *last;
    *last = tmp;
    (*last)->next = NULL;
}

void delFromFront(Queue **first, Queue **last)
{
    if (*first == *last)
    {
        delete *first;
        *last = NULL;
        return;
    }

    Queue *tmp = (*first)->next;
    delete *first;
    *first = tmp;
    (*first)->prev = NULL;
}


void sortValues(Queue *first, Queue *last, int dir = 0)
{
    Queue *edge = NULL, *cur;
    int tmp;
    do {
        for (cur = first; cur->next != edge; cur = cur->next)
            if ((cur->value > cur->next->value) == ! (bool) dir) {
                tmp = cur->value;
                cur->value = cur->next->value;
                cur->next->value = tmp;
            }
        edge = cur;
    } while (first->next != edge);
}

void sortPointers(Queue **first, Queue **last, int dir = 0)
{
    addToBack(&(*first), &(*last), 0); // Kastuś, ty daŭbajob, što za chujnia?
    addToFront(&(*first), &(*last), 0);

    Queue *edge = *last, *cur, *tmp;
    if ((*first)->next->next == *last) return;
    do {
        for (cur = *first; cur->next->next != edge; cur = cur->next)
            if ((cur->next->value > cur->next->next->value) == ! (bool) dir) {
                tmp = cur->next->next;
                cur->next->next = tmp->next;
                tmp->next->prev = cur->next;
                tmp->next = cur->next;
                cur->next->prev = tmp;
                tmp->prev = cur;
                cur->next = tmp;
            }
        edge = cur->next;
    } while ((*first)->next->next != edge);

    delFromBack(first, last);
    delFromFront(first, last);
}

void idz()
{
    Queue *_max = _begin, *_min = _begin;
    Queue *cur = _begin;
    int _max_number = 0, _min_number = 0, cnt = 0;
    while (cur != NULL)
    {
        if (cur->value > _max->value) _max = cur, _max_number = cnt;
        if (cur->value < _min->value) _min = cur, _min_number = cnt;
        cur = cur->next;
        cnt++;
    }

    int number_between = abs(_max_number - _min_number) - 1;
    cout << "Rasstoyanie: " << number_between << endl;
    Queue *first, *last;
    if (_max_number > _min_number)
        first = _min, last = _max;
    else
        first = _max, last = _min;
    if (first->next != last)
    {
        for (Queue *tmp = first->next; tmp->next != last;)
        {
            Queue *p = tmp;
            tmp = tmp->next;
            delete p;
        }
        first->next = last;
        last->prev = first;
    }
    cout << "rezult: ";

    print(0, _begin);
}

#pragma argsused
int main()
{
    int i, in, n, kod, toBegin;
    while (true)
    {
        cout << "\n\tCreate - 1.\n\tAdd - 2.\n\tView - 3.\n\tDel - 4.\n\tIDZ - "
        "5.\n\tSort1 - 6.\n\tSort2 - 7.\n\tEXIT - 0. : ";
        cin >> kod;
        switch (kod)
        {
        case 1:
        case 2:
            if (kod == 1 && _begin != NULL)
            {
                cout << "Clear Memory!" << endl;
                break;
            }
            cout << "Input to begin - 1; input to end - 2: ";
            cin >> toBegin;
            cout << "Input kol = ";
            cin >> n;
            for (i = 1; i <= n; i++)
            {
// in = random(20);
                in = rand() % 20;
                if (toBegin == 1)
                    addToFront(&_begin, &_end, in);
                else
                    addToFront(&_begin, &_end, in);
            }
            if (kod == 1)
                cout << "Create " << n << endl;
            else
                cout << "Add " << n << endl;
            break;
        case 3:
            if (!_begin)
            {
                cout << "Queue Pyst!" << endl;
                break;
            }
            cout << "From begin - 1; From end - 2;";
            cin >> toBegin;
            cout << "-— Queue —-" << endl;
            if (toBegin == 1)
                print(0, _begin);
            else
                print(1, _end);
            break;
        case 4:
            Del_All(&_begin);
            cout << "Memory Free!" << endl;
            break;
        case 5:
            idz();
            break;
        case 6:
            cout << "Sort from Begin - 1, Sort from End - 2 : ";
            cin >> kod;
            if (kod == 1) {
                sortValues(_begin, _end);
            } else {
                sortValues(_begin, _end, 1);
            }
            break;
        case 7:
            cout << "Sort from Begin - 1,Sort from End - 2 : ";
            cin >> kod;
            if (kod == 1) {
                sortPointers(&_begin, &_end);
            } else {
                sortPointers(&_begin, &_end, 1);
            }
            break;
        case 0:
            if (_begin != NULL) Del_All(&_begin);
            return 0;
        }
    }

    char k;
    return 0;
}
//------------------------------------------------------------
