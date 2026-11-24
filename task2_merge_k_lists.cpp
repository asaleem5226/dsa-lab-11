#include <iostream>
#include <queue>
#include <vector>

using namespace std;

struct ListNode {
    int value;
    ListNode* next;
};

struct HeapEntry {
    ListNode* node;
    int listIndex;
};

struct CompareEntries {
    bool operator()(const HeapEntry& a, const HeapEntry& b) const {
        if (a.node->value != b.node->value) {
            return a.node->value > b.node->value;
        }
        return a.listIndex > b.listIndex;
    }
};

int main() {
    int k;

    // First input: number of linked lists.
    if (!(cin >> k) || k < 0) {
        return 1;
    }

    vector<ListNode*> heads(k, nullptr);

    // For each list, enter its length followed by its sorted values.
    for (int i = 0; i < k; ++i) {
        int length;

        if (!(cin >> length) || length < 0) {
            return 1;
        }

        ListNode* tail = nullptr;

        for (int j = 0; j < length; ++j) {
            int value;
            if (!(cin >> value)) {
                return 1;
            }

            ListNode* newNode = new ListNode{value, nullptr};

            if (heads[i] == nullptr) {
                heads[i] = newNode;
            } else {
                tail->next = newNode;
            }

            tail = newNode;
        }
    }

    priority_queue<HeapEntry, vector<HeapEntry>, CompareEntries> minHeap;

    // Add the first node of each non-empty list to the heap.
    for (int i = 0; i < k; ++i) {
        if (heads[i] != nullptr) {
            minHeap.push({heads[i], i});
        }
    }

    ListNode dummy{0, nullptr};
    ListNode* resultTail = &dummy;

    while (!minHeap.empty()) {
        HeapEntry smallest = minHeap.top();
        minHeap.pop();

        ListNode* node = smallest.node;
        ListNode* nextNode = node->next;

        // Append the smallest node to the merged list.
        resultTail->next = node;
        resultTail = node;
        resultTail->next = nullptr;

        // Add the next node from the same list, if there is one.
        if (nextNode != nullptr) {
            minHeap.push({nextNode, smallest.listIndex});
        }
    }

    cout << "Merged list: ";

    if (dummy.next == nullptr) {
        cout << "(empty)";
    } else {
        ListNode* current = dummy.next;

        while (current != nullptr) {
            cout << current->value;
            if (current->next != nullptr) {
                cout << ' ';
            }
            current = current->next;
        }
    }

    cout << '\n';

    // Free the merged list.
    ListNode* current = dummy.next;
    while (current != nullptr) {
        ListNode* nextNode = current->next;
        delete current;
        current = nextNode;
    }

    return 0;
}