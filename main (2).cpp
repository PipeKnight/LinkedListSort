#include <iostream>
#include <memory>
#include <cstdio>

template <typename T>
struct List {
    T val;
    List* next = nullptr;
    List() = default;
    List(const T& _val): val(_val) {}
};

template <typename T>
void Print(List<T>*& head) {
    if (head == nullptr) {
        std::cout << "empty" << std::endl;
        return;
    }
    List<T>* tmp = head;
    while (tmp->next != nullptr) {
        std::cout << tmp->val << ' ';
        tmp = tmp->next;
    }
    std::cout << tmp->val << std::endl;
}

template <typename T>
void ClearMemory(List<T>*& head) {
    while (head != nullptr) {
        List<T>* cur = head;
        head = head->next;
        delete cur;
    }
}

template <typename T>
List<T>* Merge(List<T>*&& first, List<T>*&& second) {
    List<T>* new_head = new List<T>();
    List<T>* cur = new_head;
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
    auto tmp = new_head->next;
    delete new_head;
    return tmp;
}

template <typename T>
List<T>* MergeSort(List<T>*& head, int cur_size) {
    if (cur_size < 2)
        return head;
    List<T>* middle = head;
    int mid = cur_size >> 1;
    for (int i = 0; i < mid - 1; ++i) {
        middle = middle->next;
    }
    List<T>* second_head = middle->next;
    middle->next = nullptr;
    return Merge(MergeSort(head, mid), MergeSort(second_head, cur_size - mid));
}

int main()
{
    freopen("input.txt", "r", stdin);
    int n;
    std::cin >> n;
    int val;
    std::cin >> val;
    List<int>* head = new List<int>(val);
    for (int i = 0; i < n - 1; ++i) {
        std::cin >> val;
        List<int>* tmp = new List<int>(val);
        tmp->next = head;
        head = tmp;
    }
    head = MergeSort(head, n);
    Print(head);
    ClearMemory(head);
    return 0;
}
