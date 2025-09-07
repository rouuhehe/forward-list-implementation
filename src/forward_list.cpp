#include <iostream>

/* -------- node structure -------- */
template <typename T>
struct Node {
    T data;
    Node *next;

    Node(T data) : data(data), next(nullptr) {}
    Node() {}
};

/* -------- forward_list implementation --------*/
template <typename T>
class forward {
private:
    Node<T> *head;

public:
    forward() : head(nullptr) {}
    ~forward() {
        while (head) {
            Node<T> *temp = head;
            head = head->next;
            delete temp;
        }
    }

    T front() {
        if (!head)
            throw std::runtime_error("List is empty!");
        return head->data;
    }

    T back() {
        if (!head)
            throw std::runtime_error("List is empty!");
        Node<T> *curr = head;
        while (curr->next)
            curr = curr->next;
        return curr->data;
    }

    bool empty() {
        return head == nullptr;
    }

    int size() {
        int c = 0;
        Node<T> *curr = head;
        while (curr) {
            curr = curr->next;
            c++;
        }
        return c;
    }

    void push_front(T val) {
        Node<T> *temp = new Node<T>(val);
        temp->next = head;
        head = temp;
    }

    void push_back(T val) {
        if (!head) {
            head = new Node<T>(val);
            return;
        }
        Node<T> *temp = new Node<T>(val);
        auto curr = head;
        while (curr->next)
            curr = curr->next;
        curr->next = temp;
    }

    T operator[](int idx) {
        if (!head)
            throw std::runtime_error("List is empty!");
        else if (idx >= this->size() || idx < 0)
            throw std::out_of_range("Index out of bounds");

        int c = 0;
        Node<T> *temp = head;
        while (c < idx) {
            temp = temp->next;
            c++;
        }
        return temp->data;
    }

    void pop_front() {
        if (!head)
            throw std::runtime_error("List is empty!");
        Node<T> *temp = head;
        head = temp->next;
        delete temp;
    }

    void pop_back() {
        if (!head)
            throw std::runtime_error("List is empty!");
        
        if (!head->next) {
            head = nullptr;
            return;
        }
        
        Node<T> *temp = head;
        while (temp->next->next) {
            temp = temp->next;
        }
        temp->next = nullptr;
    }

    void clear() {
        while (head) {
            Node<T> *temp = head;
            head = head->next;
            delete temp;
        }
    }

    Node<T> *getMiddle(Node<T> *node){
        if (!node)
            return node;
        Node<T> *p1 = node, *p2 = node->next;
        while (p2 && p2->next) {
            p1 = p1->next;
            p2 = p2->next->next;
        }
        return p1;
    }

    Node<T> *merge(Node<T> *list1, Node<T> *list2) {
        if (!list1 && list2) return list2;
        else if (!list1 && !list2) return list1;
        else if (list1 && !list2) return list1;

        Node<T> list;
        Node<T> *temp = &list;
        while (list1 && list2) {
            if (list1->data < list2->data){
                temp->next = list1;
                list1 = list1->next;
            }
            else{
                temp->next = list2;
                list2 = list2->next;
            }
            temp = temp->next;
        }
        temp->next = (list1) ? list1 : list2;
        return list.next;
    }

    Node<T> *mergeSort(Node<T> *node) {
        if (!node || !node->next)
            return node;

        Node<T> *middle = getMiddle(node);
        Node<T> *right = middle->next;
        middle->next = nullptr;
        Node<T> *left = node;

        Node<T> *leftSorted = mergeSort(left);
        Node<T> *rightSorted = mergeSort(right);
        return merge(leftSorted, rightSorted);
    }

    void sort() {
        head = mergeSort(head);
    }
    
    void print() {
        Node<T> *p1 = head;
        while (p1) {
            std::cout << p1->data << " ";
            p1 = p1->next;
        }
        delete p1;
    }

    Node<T> *reverseEXTRA(Node<T> *node) {
        if (!node || !node->next)
            return node;
        Node<T> *middle = getMiddle(node);
        Node<T> *right = middle->next;
        middle->next = nullptr;
        Node<T> *left = node;

        Node<T> *leftInverted = reverseEXTRA(left);
        Node<T> *rightInverted = reverseEXTRA(right);

        auto tail = rightInverted;
        while(tail->next != nullptr)
            tail = tail->next;
        tail->next = leftInverted;
        return rightInverted;
    }

    Node<T> *reverse1(Node<T> *node){
        if (!node || !node->next)
            return node;

        Node<T> *reverse = reverse1(node->next);
        node->next->next = node;
        node->next = nullptr;        
        return reverse;
    }

    void reverse(){
        head = reverse1(head);
    }

    void reverseEXTRA(){
        head = reverseEXTRA(head);
    }
};


int main()
{
    forward<int> hello;
    hello.push_front(1);
    
    hello.push_front(5);
    /*
    hello.push_front(2);
    hello.push_front(3);
    hello.push_back(0);
    std::cout << "front: " << hello.front() << " back: " << hello.back() << "\n";
    std::cout << "size: " << hello.size() << "\n";
    hello.print();
    std::cout<<"\n";
    hello.sort();
    hello.print();
    std::cout << "\n";
    hello.reverse();
    hello.print();
    */
    hello.pop_back();
    hello.print();
    // hello.pop_front();
    // std::cout << "front: " << hello.front() << " back: " << hello.back() << "\n";
    // std::cout << "size: " << hello.size() << "\n";

    // hello.pop_back();
    // std::cout << "front: " << hello.front() << " back: " << hello.back() << "\n";
    // std::cout << "size: " << hello.size() << "\n";
}