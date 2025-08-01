/*
 * Deskflow -- mouse and keyboard sharing utility
 * SPDX-FileCopyrightText: (C) 2012 - 2016 Symless Ltd.
 * SPDX-FileCopyrightText: (C) 2003 Chris Schoeneman
 * SPDX-License-Identifier: GPL-2.0-only WITH LicenseRef-OpenSSL-Exception
 */

#pragma once

#include <algorithm>
#include <vector>

//! A priority queue with an iterator
/*!
This priority queue is the same as a standard priority queue except:
it sorts by std::greater, it has a forward iterator through the elements
(which can appear in any order), and its contents can be swapped.
*/
template <
    class T, class Container = std::vector<T>,
#if defined(_MSC_VER)
    class Compare = std::greater<Container::value_type>>
#else
    class Compare = std::greater<typename Container::value_type>>
#endif
class PriorityQueue
{
public:
  using value_type = Container::value_type;
  using size_type = Container::size_type;
  using iterator = Container::iterator;
  using const_iterator = Container::const_iterator;
  using container_type = Container;

  PriorityQueue() = default;
  explicit PriorityQueue(Container &swappedIn)
  {
    swap(swappedIn);
  }
  ~PriorityQueue() = default;

  //! @name manipulators
  //@{

  //! Add element
  void push(const value_type &v)
  {
    c.push_back(v);
    std::ranges::push_heap(c, comp);
  }

  //! Remove head element
  void pop()
  {
    std::ranges::pop_heap(c, comp);
    c.pop_back();
  }

  //! Erase element
  void erase(iterator i)
  {
    c.erase(i);
    std::ranges::make_heap(c, comp);
  }

  //! Get start iterator
  iterator begin()
  {
    return c.begin();
  }

  //! Get end iterator
  iterator end()
  {
    return c.end();
  }

  //! Swap contents with another priority queue
  void swap(PriorityQueue<T, Container, Compare> &q) noexcept
  {
    c.swap(q.c);
  }

  //! Swap contents with another container
  void swap(Container &c2) noexcept
  {
    c.swap(c2);
    std::ranges::make_heap(c, comp);
  }

  //@}
  //! @name accessors
  //@{

  //! Returns true if there are no elements
  bool empty() const
  {
    return c.empty();
  }

  //! Returns the number of elements
  size_type size() const
  {
    return c.size();
  }

  //! Returns the head element
  const value_type &top() const
  {
    return c.front();
  }

  //! Get start iterator
  const_iterator begin() const
  {
    return c.begin();
  }

  //! Get end iterator
  const_iterator end() const
  {
    return c.end();
  }

  //@}

private:
  Container c;
  Compare comp;
};
