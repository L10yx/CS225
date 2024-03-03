
template <class T>
void Stack<T>::push(T& t) {
  // If we are about to overflow, double the size of the array:
  if (count_ + 1 == size_) {
    size_ *= 2; 
    T ** newArray = new T*[size_];
    for (unsigned i=0; i < count_; i++) { 
        newArray[i] = arr_[i]; 
    }
    delete [] arr_;
    arr_ = newArray;
  }

  // Insert (push) the element into the array-backed stack:
  arr_[count_++] = &t;
}

template <class T>
T& Stack<T>::pop() {
  // no error checking
  return *(arr_[--count_]);
}

template <class T>
bool Stack<T>::isEmpty() const {
  return (count_ == 0);
}

template <typename T>
void Stack<T>::printStack() const {
    for (unsigned i=count_; i > 0; i--)
      cout << *(arr_[i-1]);
  cout << endl;
}


template <typename T>
Stack<T>::Stack() : arr_(new T*[1]), size_(1), count_(0) {
}

template <typename T>
Stack<T>::Stack(const Stack &other) {
  // not implemented
}

template <typename T>
Stack<T>::~Stack() {
  delete [] arr_;
}

template <typename T>
Stack<T>& Stack<T>::operator=(const Stack &other) {
  // not implemented
  return *this;
}

