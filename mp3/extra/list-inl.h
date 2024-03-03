/**
 * @file list.cpp
 * Doubly Linked List (MP 3).
 */

/**
 * Destroys the current List. This function should ensure that
 * memory does not leak on destruction of a list.
 */
template <class T>
List<T>::~List() {
  /// @todo Graded in MP3.1
  clear();
}

/**
 * Destroys all dynamically allocated memory associated with the current
 * List class.
 */
template <class T>
void List<T>::clear() {
  /// @todo Graded in MP3.1
  while ( head_->next != nullptr )
  {
    ListNode *node = head_;
    head_ = head_->next;
    delete node;
    length_--;
  }  
  delete head_;
  head_ = nullptr;
  tail_ = nullptr;
  length_ = 0;
}

/**
 * Inserts a new node at the front of the List.
 * This function **SHOULD** create a new ListNode.
 *
 * @param ndata The data to be inserted.
 */
template <class T>
void List<T>::insertFront(T const& ndata) {
  /// @todo Graded in MP3.1
  if (length_ == 0) {
    head_ = new ListNode(ndata);
    tail_ = head_;
  }
  if (length_ > 0) {
    ListNode *node = new ListNode(ndata);
    node->next = head_;
    head_->prev = node;
    head_ = node;
    if (length_ == 1) tail_->prev = head_;
  }
  length_++;
}

/**
 * Inserts a new node at the back of the List.
 * This function **SHOULD** create a new ListNode.
 *
 * @param ndata The data to be inserted.
 */
template <class T>
void List<T>::insertBack(const T& ndata) {
  /// @todo Graded in MP3.1
  if (length_ == 0) {
    head_ = new ListNode(ndata);
    tail_ = head_;
  }
  if (length_ > 0) {
    ListNode *node = new ListNode(ndata);
    tail_->next = node;
    node->prev = tail_;
    tail_=node;
    if (length_ == 1) head_->next = tail_;
  }
  length_++;
}

/**
 * Reverses the current List.
 */
template <class T>
void List<T>::reverse() {
  reverse(head_, tail_);
}

/**
 * Helper function to reverse a sequence of linked memory inside a List,
 * starting at startPoint and ending at endPoint. You are responsible for
 * updating startPoint and endPoint to point to the new starting and ending
 * points of the rearranged sequence of linked memory in question.
 *
 * @param startPoint A pointer reference to the first node in the sequence
 *  to be reversed.
 * @param endPoint A pointer reference to the last node in the sequence to
 *  be reversed.
 */
template <class T>
void List<T>::reverse(ListNode*& startPoint, ListNode*& endPoint) {
    /// @todo Graded in MP3.1
  if (startPoint == nullptr || endPoint == nullptr) return;
  if (startPoint == endPoint) return;
  ListNode *tnext = startPoint->next;
  ListNode *tprev = startPoint->prev;
  ListNode *curr = startPoint;
  if (startPoint->prev != nullptr) (startPoint->prev)->next = endPoint;
  if (endPoint->next != nullptr) (endPoint->next)->prev = startPoint;
  startPoint->next = endPoint->next;
  endPoint->prev = startPoint->prev;
  

  while (curr != endPoint)
  {
    tprev = curr;
    curr->prev = tnext;
    curr = tnext;
    tnext = curr->next;
    curr->next = tprev;
  }

  if (head_ == startPoint) head_ = endPoint;
  if (tail_ == endPoint ) tail_ = startPoint;
  return;





  /*if (startPoint == nullptr || endPoint == nullptr) return;
  if (startPoint == endPoint) return;


  if (startPoint->next == endPoint) {
    if (startPoint->prev != nullptr) (startPoint->prev)->next = endPoint;
    if (endPoint->next != nullptr) (endPoint->next)->prev = startPoint;
    startPoint->next = endPoint->next;
    endPoint->prev = startPoint->prev;
    startPoint->prev = endPoint;
    endPoint->next = startPoint;
    return;
  }
  else {
    if (startPoint->prev != nullptr) (startPoint->prev)->next = endPoint;
    if (startPoint->next != nullptr) (startPoint->next)->prev = endPoint;
    if (endPoint->prev != nullptr) (endPoint->prev)->next = startPoint;
    if (endPoint->next != nullptr) (endPoint->next)->prev = startPoint;
  }

  ListNode *p = startPoint->prev;
  ListNode *n = startPoint->next;
  startPoint->prev = endPoint->prev;
  startPoint->next = endPoint->next;
  endPoint->prev = p;
  endPoint->next = n;
  reverse(endPoint->next, startPoint->prev);
  if (head_ == startPoint) head_ = endPoint;
  if (tail_ == endPoint ) tail_ = startPoint;
  return;*/
}

/**
 * Reverses blocks of size n in the current List. You should use your
 * reverse( ListNode * &, ListNode * & ) helper function in this method!
 *
 * @param n The size of the blocks in the List to be reversed.
 */
template <class T>
void List<T>::reverseNth(int n) {
  /// @todo Graded in MP3.1
  if (n == 1) return;
  int i = 2;
  ListNode *start = head_;
  ListNode *end = start->next;

  while (true)
  {
    while (i < n)
    {
      if (end->next == nullptr) break;
      end = end->next;
      i++;
    }
    reverse(start, end);
    if (start->next != nullptr) start = start->next;
    else return;
    if (start->next != nullptr) end = start->next;
    else return;
    i = 2;
  }
  

}

/**
 * Modifies the List using the waterfall algorithm.
 * Every other node (starting from the second one) is removed from the
 * List, but appended at the back, becoming the new tail. This continues
 * until the next thing to be removed is either the tail (**not necessarily
 * the original tail!**) or NULL.  You may **NOT** allocate new ListNodes.
 * Note that since the tail should be continuously updated, some nodes will
 * be moved more than once.
 */
template <class T>
void List<T>::waterfall() {
  /// @todo Graded in MP3.1
  if (length_ < 3) return;
  ListNode *curr = head_;
  while (curr != tail_) {
    curr = curr->next;
    if (curr == tail_) break;
    (curr->prev)->next = curr->next;
    (curr->next)->prev = curr->prev;
    tail_->next = curr;
    curr->prev = tail_;
    tail_ = curr;
    curr = curr->next;
    tail_->next = nullptr;
  }
}

/**
 * Splits the given list into two parts by dividing it at the splitPoint.
 *
 * @param splitPoint Point at which the list should be split into two.
 * @return The second list created from the split.
 */
template <class T>
List<T> List<T>::split(int splitPoint) {
    if (splitPoint > length_)
        return List<T>();

    if (splitPoint < 0)
        splitPoint = 0;

    ListNode* secondHead = split(head_, splitPoint);

    int oldLength = length_;
    if (secondHead == head_) {
        // current list is going to be empty
        head_ = NULL;
        tail_ = NULL;
        length_ = 0;
    } else {
        // set up current list
        tail_ = head_;
        while (tail_->next != NULL)
            tail_ = tail_->next;
        length_ = splitPoint;
    }

    // set up the returned list
    List<T> ret;
    ret.head_ = secondHead;
    ret.tail_ = secondHead;
    if (ret.tail_ != NULL) {
        while (ret.tail_->next != NULL)
            ret.tail_ = ret.tail_->next;
    }
    ret.length_ = oldLength - splitPoint;
    return ret;
}

/**
 * Helper function to split a sequence of linked memory at the node
 * splitPoint steps **after** start. In other words, it should disconnect
 * the sequence of linked memory after the given number of nodes, and
 * return a pointer to the starting node of the new sequence of linked
 * memory.
 *
 * This function **SHOULD NOT** create **ANY** new List objects!
 *
 * @param start The node to start from.
 * @param splitPoint The number of steps to walk before splitting.
 * @return The starting node of the sequence that was split off.
 */
template <class T>
typename List<T>::ListNode* List<T>::split(ListNode* start, int splitPoint) {
    /// @todo Graded in MP3.2
    return nullptr;
}

/**
 * Merges the given sorted list into the current sorted list.
 *
 * @param otherList List to be merged into the current list.
 */
template <class T>
void List<T>::mergeWith(List<T>& otherList) {
    // set up the current list
    head_ = merge(head_, otherList.head_);
    tail_ = head_;

    // make sure there is a node in the new list
    if (tail_ != NULL) {
        while (tail_->next != NULL)
            tail_ = tail_->next;
    }
    length_ = length_ + otherList.length_;

    // empty out the parameter list
    otherList.head_ = NULL;
    otherList.tail_ = NULL;
    otherList.length_ = 0;
}

/**
 * Helper function to merge two **sorted** and **independent** sequences of
 * linked memory. The result should be a single sequence that is itself
 * sorted.
 *
 * This function **SHOULD NOT** create **ANY** new List objects.
 *
 * @param first The starting node of the first sequence.
 * @param second The starting node of the second sequence.
 * @return The starting node of the resulting, sorted sequence.
 */
template <class T>
typename List<T>::ListNode* List<T>::merge(ListNode* first, ListNode* second) {
  /// @todo Graded in MP3.2
  return nullptr;
}

/**
 * Sorts the current list by applying the Mergesort algorithm.
 */
template <class T>
void List<T>::sort() {
    if (empty())
        return;
    head_ = mergesort(head_, length_);
    tail_ = head_;
    while (tail_->next != NULL)
        tail_ = tail_->next;
}

/**
 * Sorts a chain of linked memory given a start node and a size.
 * This is the recursive helper for the Mergesort algorithm (i.e., this is
 * the divide-and-conquer step).
 *
 * @param start Starting point of the chain.
 * @param chainLength Size of the chain to be sorted.
 * @return A pointer to the beginning of the now sorted chain.
 */
template <class T>
typename List<T>::ListNode* List<T>::mergesort(ListNode* start, int chainLength) {
    /// @todo Graded in MP3.2
    return nullptr;
}
