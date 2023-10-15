#ifndef S21_VECTOR_HPP_
#define S21_VECTOR_HPP_

#include <cstdint>
#include <cstdlib>
#include <cstring>
#include <initializer_list>
#include <limits>

#include "../util.hpp"

namespace s21 {
template <typename T> class vector {
private:
  T *m_data;
  size_t m_capacity;
  size_t m_length;

public:
  // member types
  using value_type = T;
  using reference = T &;
  using const_reference = const T &;
  using iterator = T *;
  using const_iterator = const T *;
  using size_type = size_t;

private:
  void increase_size() {
    reserve(m_capacity * 9 / 8 + 16);
  }

  void check_iterator(const_iterator iter) {
    if (iter >= begin() && iter <= end()) {
      // ok
    } else {
      throw std::runtime_error("Iterator out of bounds");
    }
  }

public:
  // Implementation
  vector() noexcept : m_data(nullptr), m_capacity(0), m_length(0){};

  vector(const vector &copy_from) : vector(copy_from.size()) {
    for (size_type i = 0; i < copy_from.size(); i++)
      push_back(T(copy_from.at(i)));
  }
  vector(vector &&move_from)
      : m_data(move_from.m_data), m_capacity(move_from.m_capacity),
        m_length(move_from.m_length) {
    move_from.m_data = nullptr;
    move_from.m_length = 0;
    move_from.m_capacity = 0;
  }

  vector &operator=(const vector &copy_from) {
    if (this == &copy_from)
      return *this;

    (*this) = std::move(vector(copy_from));
    return (*this);
  }

  vector &operator=(vector &&move_from) {
    if (this == &move_from)
      return *this;

    util::call_destructor(*this);

    m_data = move_from.m_data;
    m_length = move_from.m_length;
    m_capacity = move_from.m_capacity;

    move_from.m_data = nullptr;
    move_from.m_length = 0;
    move_from.m_capacity = 0;

    return (*this);
  }

  ~vector() { delete[] m_data; }

  // Actual functionality
  explicit vector(size_type size) : vector() { reserve(size); }

  vector(const std::initializer_list<T> &data) : vector(data.size()) {
    std::copy(data.begin(), data.end(), m_data);
    m_length = data.size();
  }

  void reserve(size_type new_cap) {
    if (new_cap == m_capacity)
      return;

    T *new_data = new_cap <= 0 ? nullptr : new T[new_cap];
    size_type new_len = m_length < new_cap ? m_length : new_cap;

    for (size_type i = 0; i < new_len && m_data && new_data; i++)
      new_data[i] = std::move(m_data[i]);

    delete[] m_data;
    m_data = new_data;
    m_length = new_len;
    m_capacity = new_cap;
  }

  size_type size() const { return m_length; }

  value_type &at(size_type i) {
    if (i >= m_length)
      throw std::runtime_error(util::stringfmt(
          "Invalid index % for vector of length %", i, m_length));

    return m_data[i];
  }
  const value_type &at(size_type i) const {
    if (i >= m_length)
      throw std::runtime_error(util::stringfmt(
          "Invalid index % for vector of length %", i, m_length));

    return m_data[i];
  }

  void push_back(value_type &&v) {
    if (m_length >= m_capacity)
      increase_size();

    m_data[m_length++] = std::move(v);
  }

  void push_back(const value_type &v) {
    if (m_length >= m_capacity)
      increase_size();

    m_data[m_length++] = v;
  }

  iterator begin() const { return &m_data[0]; }
  iterator end() const { return &m_data[m_length]; }

  T &operator[](size_type pos) { return at(pos); }

  const T &operator[](size_type pos) const { return at(pos); }

  const T &front() const { return at(0); };

  const T &back() const { return at(m_length - 1); }

  T *data() { return m_data; }

  const T *data() const { return m_data; }

  bool empty() const { return m_length == 0; }
  size_type max_size() const { return std::numeric_limits<size_t>::max; }
  size_type capacity() const { return m_capacity; }

  void shrink_to_fit() { reserve(m_length); }

void clear() {
  reserve(0);
}

iterator insert(iterator pos, T&& value) {
  check_iterator(pos);
  ptrdiff_t index = pos - begin();

  if (m_capacity < (m_length + 1))
    increase_size();

  util::move_r(begin() + index, end(), end() + 1);
  at(index) = std::move(value);
  m_length++;
  return pos;
}

iterator insert(iterator pos, const_reference value) {
  check_iterator(pos);
  ptrdiff_t index = pos - begin();
  if (m_capacity < (m_length + 1))
    increase_size();

  util::move_r(begin() + index, end(), end() + 1);
  at(index) = value;
  m_length++;
}

void erase(iterator pos) {
  util::move_l(pos + 1, end(), pos);
  m_length--;
}

void pop_back()	{
  /*
  T& object = m_data[m_length - 1];
  m_length--;
  return std::move(object);
  */
  at(m_length - 1) = T();
  m_length--;
}

void swap(vector& other) {
  std::swap(other.m_data, m_data);
  std::swap(other.m_length, m_length);
  std::swap(other.m_capacity, m_capacity);
}

bool operator==(const vector& other) const {
  if (m_length != other.m_length)
    return false;

  for (size_type i = 0; i < m_length; i++) {
    if (at(i) != other.at(i))
      return false;
  }

  return true;
}

template<typename O>
bool operator==(const O&) const { return false; }

template<typename O>
bool operator!=(const O& other) const { return !((*this) == other); }
};


} // namespace s21

#endif // S21_VECTOR_HPP_