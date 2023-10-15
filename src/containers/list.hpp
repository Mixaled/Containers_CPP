#include <iostream>
#include <limits>
#include <stack>
#include <string>

namespace s21 {
template <typename T>
class Node {
 public:
  T data;
  Node* next;
  Node() {
    data = 0;
    next = NULL;
  }

  Node(int data) {
    this->data = data;
    this->next = NULL;
  }
};

template <typename T>
class iterator {
 public:
  Node<T>* iter_prt;

 public:
  iterator(Node<T>* ptr) { iter_prt = ptr; }

  iterator& operator++() {
    if (iter_prt == nullptr) {
    } else {
      iter_prt = iter_prt->next;
    }
    return *this;
  }
  bool operator>(const iterator<T>& other) const {
    return iter_prt > other.iter_prt;
  }
  // is it cringe?
  template <typename Offset>
  iterator operator+(Offset reference) const {
    iterator result = *this;
    for (Offset i = 0; i < reference; i++) {
      if (result.iter_prt != nullptr) {
        result.iter_prt = result.iter_prt->next;
      }
    }
    return result;
  }

  bool operator!=(const iterator& i) { return iter_prt != i.iter_prt; }
  bool operator==(iterator& i) { return iter_prt == i.iter_prt; }

  T& operator*() { return iter_prt->data; }
};

template <typename T>
class list {
 public:
  using value_type = T;
  using reference = T&;
  using const_reference = const T&;
  // using iterator = T *;
  using const_iterator = const T*;
  using size_type = size_t;

 private:
  Node<T>*head, *tail;

 public:
  list() : head(nullptr), tail(nullptr){};
  list(size_type size) {
    for (int i = 0; i < size; i++) {
      Node<T>* new_node = new Node<T>;
      if (i == 0) {
        head = new_node;
        tail = new_node;
      } else {
        tail->next = new_node;
        tail = new_node;
      }
    }
  }
  list(std::initializer_list<value_type> const& items)
      : head(nullptr), tail(nullptr) {
    for (const auto& it : items) {
      Node<T>* new_node = new Node<T>(it);
      if (head == nullptr) {
        head = new_node;
        tail = new_node;
      } else {
        tail->next = new_node;
        tail = new_node;
      }
    }
  }
  // copy constructor
  list(const list& copy_from) : head(nullptr), tail(nullptr) {
    for (auto it = copy_from.begin(); it != copy_from.end(); ++it) {
      Node<T>* new_node = new Node<T>(*it);
      if (head == nullptr) {
        head = new_node;
        tail = new_node;
      } else {
        tail->next = new_node;
        tail = new_node;
      }
    }
  }

  // move constructor
  list(list&& move_from) noexcept : head(move_from.head), tail(move_from.tail) {
    move_from.head = nullptr;
    move_from.tail = nullptr;
  }

  // assignment operator
  list& operator=(list&& l) {
    if (this != &l) {
      while (head != nullptr) {
        Node<T>* current = head;
        head = head->next;
        delete current;
      }
      tail = nullptr;
      this->head = l.head;
      this->tail = l.tail;
      l.head = nullptr;
      l.tail = nullptr;
    }
    return *(this);
  }

  bool empty() const { return head == nullptr; }

  size_type size() const {
    size_type count = 0;
    iterator<T> it = begin();
    while (it != end()) {
      ++count;
      ++it;
    }
    return count;
  }

  size_type max_size() const { return std::numeric_limits<size_type>::max(); }

  void clear() {
    head = nullptr;
    tail = nullptr;
  }

  const_reference front() { return head->data; }
  const_reference back() { return tail->data; }

  iterator<T> begin() const { return iterator(head); }
  iterator<T> end() const { return iterator<T>(nullptr); }

  iterator<T> insert(iterator<T> pos, const_reference value) {
    Node<T>* new_node = new Node<T>(value);
    if (pos.iter_prt == head) {
      new_node->next = head;
      head = new_node;
    } else {
      Node<T>* current = head;
      while (current != nullptr && current->next != pos.iter_prt) {
        current = current->next;
      }
      if (current != nullptr) {
        new_node->next = current->next;
        current->next = new_node;
      }
    }
    if (pos.iter_prt == nullptr) tail = new_node;
    return iterator<T>(new_node);
  }
  // need to add an out of range throw
  void erase(iterator<T> pos) {
    if (pos.iter_prt == nullptr) {
      throw std::runtime_error("ERR: Nothing to erace");
    }
    if (pos.iter_prt == head) {
      head = head->next;
    } else {
      Node<T>* previous = head;
      while (previous->next != pos.iter_prt) {
        previous = previous->next;
      }
      previous->next = pos.iter_prt->next;
      if (pos.iter_prt == tail) {
        tail = previous;
      }
    }
    delete pos.iter_prt;
  }
  void push_back(const_reference value) {
    Node<T>* new_node = new Node<T>(value);
    if (tail == nullptr) {
      tail = new_node;
      head = new_node;
    } else {
      tail->next = new_node;
      tail = new_node;
    }
  }

  void pop_back() {
    if (head == nullptr) {
      return;
    }
    if (head == tail) {
      delete head;
      head = nullptr;
      tail = nullptr;
    } else {
      Node<T>* previous = head;
      while (previous->next != tail) previous = previous->next;
      delete tail;
      tail = previous;
      tail->next = nullptr;
    }
  }
  void push_front(const_reference value) {
    Node<T>* new_node = new Node<T>(value);
    if (head == nullptr) {
      head = new_node;
      tail = new_node;
    } else {
      new_node->next = head;
      head = new_node;
    }
  }

  void pop_front() {
    if (head == nullptr) {
      return;
    }
    if (head == tail) {
      delete head;
      head = nullptr;
      tail = nullptr;
    } else {
      Node<T>* old_head = head;
      head = head->next;
      delete old_head;
    }
  }

  void swap(list& other) {
    std::swap(head, other.head);
    std::swap(tail, other.tail);
  }
  void unique() {
    sort();
    if (head == tail || head == nullptr) {
      return;
    }
    Node<T>* current = head;
    while (current->next != nullptr) {
      if (current->data == current->next->data) {
        Node<T>* tmp = current->next;
        current->next = current->next->next;
        if (tmp == tail) tail = current;
        delete tmp;
      } else {
        current = current->next;
      }
    }
  }
  void reverse() {
    if (head == tail) {
      return;
    }
    Node<T>* previous = nullptr;
    Node<T>* current = head;
    Node<T>* next_node = nullptr;
    tail = head;
    while (current != nullptr) {
      next_node = current->next;
      current->next = previous;
      previous = current;
      current = next_node;
    }
    head = previous;
  }

  Node<T>* sortedMerge(Node<T>* a, Node<T>* b) {
    Node<T>* res = nullptr;
    if (a == nullptr)
      return b;
    else if (b == nullptr)
      return a;
    if (a->data <= b->data) {
      res = a;
      res->next = sortedMerge(a->next, b);
    } else {
      res = b;
      res->next = sortedMerge(a, b->next);
    }
    return res;
  }
  void Split(Node<T>* source, Node<T>** frontRef, Node<T>** backRef) {
    Node<T>* fast;
    Node<T>* slow;
    slow = source;
    fast = source->next;
    while (fast != nullptr) {
      fast = fast->next;
      if (fast != nullptr) {
        slow = slow->next;
        fast = fast->next;
      }
    }
    *frontRef = source;
    *backRef = slow->next;
    slow->next = nullptr;
  }
  void mergeSort(Node<T>** headRef) {
    Node<T>* head = *headRef;
    Node<T>* a;
    Node<T>* b;
    if ((head == nullptr) || (head->next == nullptr)) {
      return;
    }

    Split(head, &a, &b);

    mergeSort(&a);
    mergeSort(&b);

    *headRef = sortedMerge(a, b);
  }
  void sort() { mergeSort(&head); }
  void splice(iterator<T> pos, list& other) {
    if (other.empty()) {
      return;
    }
    Node<T>* pos_node = pos.iter_prt;
    if (pos_node == nullptr) {
      throw std::runtime_error("ERR: Invalid position");
    }
    Node<T>* other_head = other.head;
    Node<T>* other_tail = other.tail;
    other.tail->next = pos_node->next;
    pos_node->next = other.head;

    if (pos_node == tail) {
      tail = other.tail;
    }
    other.head = nullptr;
    other.tail = nullptr;
  }
  // comparing
  bool operator==(const list& l) const {
    if (this == &l) {
      return true;
    }
    if (size() != l.size()) return false;
    auto it1 = begin();
    auto it2 = l.begin();
    while (it1 != end() && it2 != l.end()) {
      if (*it1 != *it2) return false;
      ++it1;
      ++it2;
    }
    return true;
  }

  ~list() {
    while (head != nullptr) {
      Node<T>* current = head;
      head = head->next;
      delete current;
    }
    tail = nullptr;
  }
};

}  // namespace s21
template <typename T>
std::ostream& operator<<(std::ostream& os, const s21::list<T>& l) {
  os << "list(";
  for (auto it = l.begin(); it != l.end(); ++it) {
    if (it != l.begin()) {
      os << ", ";
    }
    os << *it;
  }
  os << ")";
  return os;
}

// int main() {
//   s21::list<int> school21;
//   int i = school21.size();
//   std::cout << "School_size: " << i << "\n";
//   s21::list<int> school({1, 2, 3});
//   school.push_back(2);
//   std::cout << "School: " << school << "\n";
//   school.pop_back();
//   std::cout << "School: " << school << "\n";
//   s21::list<int> orig({12, 2, 4, 4, 7});
//   int res = orig.empty();
//   std::cout << orig << "\n";
//   s21::list<int> copiedList = orig;
//   s21::list<int> movedList = std::move(orig);
//   s21::list<int> mo({2, 2});
//   movedList = std::move(mo);
//   std::cout << movedList << "\n";
//   std::cout << res << "\n";
//   std::cout << movedList.size() << "\n";
//   s21::list<int> orc({12, 2, 3, 4, 7});
//   orc.insert(orc.begin() + 2, 9);
//   std::cout << orc << "\n";
//   orc.push_front(2);
//   std::cout << orc << "\n";
//   orc.pop_front();
//   std::cout << orc << "\n";
//   s21::list<int> list1({1, 2, 3, 4});
//   s21::list<int> list2({5, 6, 7});
//   std::cout << "Original list1: " << list1 << std::endl;
//   std::cout << "Original list2: " << list2 << std::endl;
//   list1.swap(list2);
//   std::cout << "After swapping:" << std::endl;
//   std::cout << "list1: " << list1 << std::endl;
//   std::cout << "list2: " << list2 << std::endl;
//   s21::list<int> list3({9, 8, 8, 7, 9});
//   list3.unique();
//   std::cout << "list3: " << list3 << std::endl;
//   return 0;
// }
