#ifndef S21_STACK_HPP_
#define S21_STACK_HPP_
#include <iostream>
#include <stdexcept>

namespace s21 {
template <typename T>
class stack {
 private:
  T* m_data;
  size_t m_capasity;
  size_t m_size;

 public:
  using value_type = T;
  using reference = T&;
  using const_reference = const T&;
  using iterator = T*;
  using const_iterator = const T*;
  using size_type = size_t;

 public:
  // default constructor
  stack() : m_capasity(0), m_size(0), m_data(nullptr){};

  // create with size
  stack(int len) : m_capasity(len), m_size(0) { m_data = new T[m_capasity]; }

  // copy constructor
  stack(const stack& copy_from)
      : m_capasity(copy_from.m_capasity), m_size(copy_from.m_size) {
    m_data = new T[m_size];
    for (size_type i = 0; i < m_size; i++) {
      m_data[i] = copy_from.m_data[i];
    }
  }

  // move constructor
  stack(stack&& move_from) noexcept
      : m_capasity(0), m_size(0), m_data(nullptr) {
    m_data = move_from.m_data;
    m_capasity = move_from.m_capasity;
    m_size = move_from.m_size;
    move_from.m_data = 0;
    move_from.m_capasity = 0;
    move_from.m_size = 0;
  }

  // copy assigment opertor
  stack& operator=(const stack& copy_from) {
    if (this == &copy_from) return *this;
    delete[] m_data;
    m_size = copy_from.m_size;
    m_capasity = copy_from.m_capasity;
    m_data = new T[m_size];
    for (size_type i = 0; i < m_size; i++) {
      m_data[i] = copy_from.m_data[i];
    }
    return *this;
  }

  // move assigment operator
  stack& operator=(const stack&& move_from) noexcept {
    if (this == &move_from) return *this;
    delete[] m_data;
    m_data = move_from.m_data;
    m_size = move_from.m_size;
    m_capasity = move_from.m_capasity;

    move_from.m_data = nullptr;
    move_from.m_capasity = 0;
    move_from.m_size = 0;

    return *this;
  }

  size_type size() const { return m_size; }

  const_reference top() { return m_data[m_size - 1]; }

  iterator begin() { return iterator(m_data); }
  iterator end() { return iterator(m_data + m_size); }

  bool empty() { return m_size == 0; }
  void push(const_reference value) {
    if (m_data == nullptr) {
      m_capasity = 2;
      m_data = new T[m_capasity];
    }

    if (m_size == m_capasity) {
      m_capasity *= 2;
      iterator newData = new T[m_capasity];
      for (size_t i = 0; i < m_size; ++i) {
        newData[i] = m_data[i];
      }
      delete[] m_data;
      m_data = newData;
    }
    m_data[m_size++] = value;
  }

  void pop() {
    if (m_size == 0) throw std::runtime_error("ERR: Stack underflow ");
    --m_size;
  }

  void swap(stack& other) noexcept {
    std::swap(m_data, other.m_data);
    std::swap(m_capasity, other.m_capasity);
    std::swap(m_size, other.m_size);
  }
  // destructor
  ~stack() { delete[] m_data; }
};
}  // namespace s21

template <typename T>
std::ostream& operator<<(std::ostream& os, const s21::stack<T>& l) {
  os << "Stack(";
  for (auto it = l.begin(); it != l.end(); ++it) {
    os << static_cast<T>(*it);
    if (it != l.end() - 1) {
      os << ", ";
    }
  }
  os << ")";
  return os;
}

#endif  // S21_STACK_HPP_