template <class T>
List<T>::List() : head_(NULL), tail_(NULL), length_(0) { /* nothing */ }

template <class T>
int List<T>::size() const {
    return length_;
}

template <class T>
List<T>::List(List<T> const& other) {
    copy(other);
}

template <class T>
List<T>& List<T>::operator=(List<T> const& rhs) {
    if (this != &rhs) {
        clear();
        copy(rhs);
    }
    return *this;
}

template <class T>
bool List<T>::empty() const {
    return head_ == NULL && tail_ == NULL && length_ == 0;
}

template <class T>
void List<T>::copy(List<T> const& other) {
    // set up the default, empty list
    head_ = NULL;
    tail_ = NULL;
    length_ = 0;

    // if we have things to copy
    if (!other.empty()) {
        ListNode* curr = other.head_;
        ListNode* prev = NULL;
        // iterate down the parameter list
        while (curr != NULL) {
            ListNode* node = new ListNode(curr->data);

            // set the head of the new list
            if (head_ == NULL)
                head_ = node;

            // correct pointer of the previous node if it exists
            if (prev != NULL)
                prev->next = node;

            node->prev = prev;

            prev = node;
            curr = curr->next;
        }

        // prev will contain our new tail---set it up accordingly
        tail_ = prev;
        tail_->next = NULL;

        length_ = other.length_;
    }
}

template <class T>
void List<T>::print(ostream& os) const {
    os << "<";
    ListNode* curr = head_;
    while (curr != NULL) {
        os << " " << curr->data;
        curr = curr->next;
    }
    os << " >";
}

// overloaded operator<<
template <class T>
ostream& operator<<(ostream& os, const List<T>& list) {
    list.print(os);
    return os;
}

// ListNode constructors
template <class T>
List<T>::ListNode::ListNode() : next(NULL), prev(NULL), data(T())
{ /* nothing */ }

template <class T>
List<T>::ListNode::ListNode(const T& ndata) : next(NULL), prev(NULL), data(ndata)
{ /* nothing */ }

template <class T>
template <class Iter>
List<T>::List(const Iter& begin_iterator, const Iter& end_iterator)
    : head_(NULL), tail_(NULL), length_(0)
{
    for (Iter i = begin_iterator; i != end_iterator; ++i)
        insertBack(*i);
}
