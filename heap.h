#ifndef HEAP_H
#define HEAP_H
#include <functional>
#include <algorithm>
#include <stdexcept>
#include <vector>
#include <iostream>

using namespace std;

template <typename T, typename PComparator = std::less<T> >
class Heap
{
public:
  /**
   * @brief Construct a new Heap object
   * 
   * @param m ary-ness of heap tree (default to 2)
   * @param c binary predicate function/functor that takes two items
   *          as an argument and returns a bool if the first argument has
   *          priority over the second.
   */
  Heap(int m=2, PComparator c = PComparator());

  /**
  * @brief Destroy the Heap object
  * 
  */
  ~Heap();

  /**
   * @brief Push an item to the heap
   * 
   * @param item item to heap
   */
  void push(const T& item);

  /**
   * @brief Returns the top (priority) item
   * 
   * @return T const& top priority item
   * @throw std::underflow_error if the heap is empty
   */
  T const & top() const;

  /**
   * @brief Remove the top priority item
   * 
   * @throw std::underflow_error if the heap is empty
   */
  void pop();

  /// returns true if the heap is empty

  /**
   * @brief Returns true if the heap is empty
   * 
   */
  bool empty() const;

    /**
   * @brief Returns size of the heap
   * 
   */
  size_t size() const;

private:
  /// Add whatever helper functions and data members you need below
  std::vector<T> heap_;
  int m_;
  PComparator c_;

};

// Add implementation of member functions here
template <typename T, typename PComparator>
Heap<T,PComparator>::Heap(int m, PComparator c) : heap_(){
  m_ = m;
  c_ = c;
}

template <typename T, typename PComparator>
Heap<T,PComparator>::~Heap() {

}

template <typename T, typename PComparator>
bool Heap<T,PComparator>::empty() const {
  return heap_.size() == 0;
}

template <typename T, typename PComparator>
size_t Heap<T,PComparator>::size() const {
  return heap_.size();
}


template <typename T, typename PComparator>
void Heap<T,PComparator>::push(const T& item){
    heap_.push_back(item);
    std::size_t index = heap_.size() - 1;
    while (index != 0) {
        std::size_t parent_index = (index - 1) / m_;
        T& current = heap_[index];
        T& parent = heap_[parent_index];
        if (c_(parent, current)) {
            break;
        }
        std::swap(current, parent);
        index = parent_index;
    }
}

// We will start top() for you to handle the case of 
// calling top on an empty heap
template <typename T, typename PComparator>
T const & Heap<T,PComparator>::top() const
{
  // Here we use exceptions to handle the case of trying
  // to access the top element of an empty heap
  if(empty()){
    // ================================
    // throw the appropriate exception
    // ================================
    throw std::underflow_error("underflow"); 

  }
  // If we get here we know the heap has at least 1 item
  // Add code to return the top element
  return heap_.front();


}


// We will start pop() for you to handle the case of 
// calling top on an empty heap
template <typename T, typename PComparator>
void Heap<T,PComparator>::pop()
{
  if(empty()){
    // ================================
    // throw the appropriate exception
    // ================================
    throw std::underflow_error("underflow");
  }
  std::swap(heap_.back(), heap_.front());
  heap_.pop_back();
  size_t index = 0;
  while (index < size()) {
    size_t swap_index = index;
    size_t current_index = index;
    for (int i = 0; i < m_; i++) {
      size_t current_index = (m_*index) + (i+1);
      // if (c_(heap_[swap_index], heap_[swap_index])) {
      //   return;
      // }
      if (current_index < size() && (c_(heap_[current_index], heap_[swap_index]) || (heap_[current_index] == heap_[swap_index]))) {
        swap_index = current_index;
      }
    }
    if (swap_index == current_index) {
      break;
    }
    std::swap(heap_[current_index], heap_[swap_index]);
    index = swap_index;
  }
}



#endif

