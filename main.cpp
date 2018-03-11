// MergeSort on Linked List

#include <iostream>
#include <memory>

using namespace std;

struct List {
    int val;
    List* next = nullptr;
    List() {}
    List(int _val) {
        val = _val;
    }
};

void Print(List* head) {
    if (head == nullptr) {
        cout << "empty\n";
        return;
    }
    List* tmp = head;
    while (tmp->next != nullptr) {
        cout << tmp->val << ' ';
        tmp = tmp->next;
    }
    cout << tmp->val << '\n';
}

List* Merge(List* first, List* second) {
    List* new_head = new List();
    List* cur = new_head;
    while (first != nullptr && second != nullptr) {
        if (first->val < second->val) {
            cur->next = first;
            first = first->next;
        } else {
            cur->next = second;
            second = second->next;
        }
        cur = cur->next;
    }
    if (first == nullptr) {
        cur->next = second;
    } else {
        cur->next = first;
    }
    return new_head->next;
}

List* MergeSort(List* head, int cur_size) {
    if (cur_size < 2)
        return head;
    List* middle = head;
    int mid = cur_size >> 1;
    for (int i = 0; i < mid - 1; ++i) {
        middle = middle->next;
    }
    List* second_head = middle->next;
    middle->next = nullptr;
    return Merge(MergeSort(head, mid), MergeSort(second_head, cur_size - mid));
}

void ClearMemory(List* &head) {
    while (head != nullptr) {
        List* cur = head;
        head = head->next;
        delete cur;
    }
}

int main()
{
    int n;
    cin >> n;
    int a;
    cin >> a;
    List* head = new List(a);
    for (int i = 0; i < n - 1; ++i) {
        int a;
        cin >> a;
        List* tmp = new List(a);
        tmp->next = head;
        head = tmp;
    }
    head = MergeSort(head, n);
    Print(head);
    ClearMemory(head);
    return 0;
}
