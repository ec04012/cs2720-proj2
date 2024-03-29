#include "SortedList.h"

// Class constructor.
template <class ItemType>
SortedList<ItemType>::SortedList() {
    listData = NULL;
    Length = 0;
}

// Class destructor.
template <class ItemType>
SortedList<ItemType>::~SortedList() {
    makeEmpty();
}

// Function: Deallocates all list nodes, and reinitializes the list to its empty state.
// Pre: List is initialized
// Post: list is empty.
template <class ItemType>
void SortedList<ItemType>::makeEmpty() {
    Node<ItemType>* tempPtr;
    while (listData != NULL) {
        tempPtr = listData;
        listData = listData->next;
        delete tempPtr;
    }
    Length = 0;
}

// Function: Determines whether the list is empty.
// Pre: List is initialized
// Post: Function value = (list is empty)
template <class ItemType>
bool SortedList<ItemType>::isEmpty() const {
    return listData == NULL;
}

// Function: Determines whether the list is full.
// Pre: List is initialized
// Post: Function value = (list is full)
template <class ItemType>
bool SortedList<ItemType>::isFull() const {
    // Try to allocate a new node, if not possible then list if full
    try {
        Node<ItemType>* temp = new Node<ItemType>;
        delete temp;
        return false;
    } catch (std::bad_alloc) {
        return true;
    }
}

// Function: Adds newItem to the end of the list.
// Pre: List is initialized
// Post: If (List is full) FullList exception is thrown
//       If item is already in the list DuplicateItem exception is thrown
//       else newItem is in the list at the correct position based on key value.
//         list maintains the sortedness property
template <class ItemType>
void SortedList<ItemType>::putItem(ItemType newItem) {
    // Check for full list
    if (isFull()) {
        throw FullList();
    }

    // predecessor node
    Node<ItemType>* pred = NULL;

    // Attemp to insert item
    if (findItem(newItem, pred)) {
        // if item is in list, throw exception
        throw DuplicateItem();
    } else {
        Node<ItemType>* newNode = new Node<ItemType>;
        newNode->info = newItem;
        if (pred == NULL) {
            // special case for inserting at beginning
            newNode->next = listData;
            listData = newNode;
        } else {
            // regular case, insert a new node in middle or at end of list
            newNode->next = pred->next;
            pred->next = newNode;
        }
    }
    Length++;
}

// Function: deletes Item from the list.
// Post: If List is empty, EmptyList exception is thrown.
// If item is not in the list, DeletingMissingItem exception is thrown.
//   else Item is not in the list.
template <class ItemType>
void SortedList<ItemType>::deleteItem(ItemType item) {
    // predecessor node
    Node<ItemType>* pred;

    if (isEmpty()) {
        throw EmptyList();
    }

    if (!findItem(item, pred)) {
        // if item is not in list, throw exception
        throw DeletingMissingItem();
    } else if (pred == NULL) {
        // special case for deleting first element
        Node<ItemType>* loc = listData;
        listData = listData->next;
        loc->next = NULL;
        delete loc;
    } else {
        // regular case, connect pred to next next
        // then delete the loc node
        Node<ItemType>* loc = pred->next;
        pred->next = loc->next;
        loc->next = NULL;
        delete loc;
    }
    Length--;
}

// Function: returns the number of items in the list
// pre: List is initialized.
// post: Function value = number of elemnts in the list.
template <class ItemType>
int SortedList<ItemType>::getLength() const {
    return Length;
}

// Function: returns the ith element of the list
// pre: List is initialized.
// post: if 0< i <= getLength(), Function value =  the ith list element.
// Throws the exception OutOfBound, if i>getLenghth() or i <=0
template <class ItemType>
ItemType SortedList<ItemType>::getAt(int i) {
    if (i > getLength() || i <= 0) {
        throw OutOfBound();
    }
    Node<ItemType>* temp = listData;
    for (int j = 1; j < i; j++) {
        temp = temp->next;
    }
    return temp->info;
}

// Function: Merges two sorted lists in place.
// Preconditions: List is initialized. otherList is initialized.
//               otherList is sorted.
// Postconditions: Function returns the implicit list (current List)
// after inserting all elements of otherList at their correct positions.
// Current list is sorted and with no duplicate keys.
// otherList is empty.
template <class ItemType>
void SortedList<ItemType>::merge(SortedList& otherList) {
    // Check for null/empty lists
    if (listData == NULL) {
        // If this list is empty, then set its listData to otherList
        // We dont care whether otherList is empty or not
        listData = otherList.listData;
        otherList.listData = NULL;
        return;
    } else if (otherList.listData == NULL || otherList.listData == listData) {
        // If other list is empty, we have nothing to merge
        // if we are trying to merge a list with itself, exit
        return;
    }

    // Both lists are non-empty and sorted
    Node<ItemType>* p = this->listData;
    Node<ItemType>* q = otherList.listData;
    Node<ItemType>* current;  // current is the last element inserted into the merged list

    // Set listData to the list whose first element is smaller. Update the current pointer
    if (p->info == q->info) {
        // special case if the first elements of both lists are duplicates, delete a duplicate
        // listData already = p
        current = p;
        p = p->next;

        // delete duplicate
        Node<ItemType>* temp = q;
        q = q->next;
        delete temp;
    }
    if (p->info < q->info) {
        // listData already = p
        current = p;
        p = p->next;
    } else {
        listData = q;
        current = q;
        q = q->next;
    }
    this->Length = 1;

    while (p != NULL && q != NULL) {
        if (p->info == q->info) {
            // Link the duplicate from this list
            current->next = p;
            current = current->next;
            p = p->next;

            // Delete duplicate from other list
            Node<ItemType>* temp = q;
            q = q->next;
            temp->next = NULL;
            delete temp;

        } else if (p->info < q->info) {
            current->next = p;
            current = current->next;
            p = p->next;
        } else {
            current->next = q;
            current = current->next;
            q = q->next;
        }
        Length++;
    }

    // link current node to the non-empty list
    if (p != NULL) {
        current->next = p;
    } else {
        current->next = q;
    }
    
    // Make other list null and empty
    otherList.listData = NULL;
    otherList.Length = 0;
}

// Function: Prints the list to a file
// pre: List is initialized
// post: List is not changed
template <class ItemType>
void SortedList<ItemType>::printList(ofstream& stream) {
    Node<ItemType>* temp = listData;
    stream << "List Items : ";
    while (temp != NULL) {
        stream << temp->info << "->";
        temp = temp->next;
    }
    stream << "NULL" << endl;
}

// Function: Searches the list for item and returns a pointer to item's predecessor node.
// pre: list is initialized
// post: (1) If item is in the list, function value =  true
//       (2) if item is not in the list, function value is false
//       (3) predecessor contains the address of item's predecessor node ( i.e. node with largest value < item's key)
//        if no predescessor exit, predecessor is set to NULL.
template <class ItemType>
bool SortedList<ItemType>::findItem(ItemType item, Node<ItemType>*& predecessor) {
    predecessor = NULL;

    Node<ItemType>* location = listData;
    while (location != NULL && location->info < item) {
        predecessor = location;
        location = location->next;
    }

    if (location != NULL && location->info == item) {
        return true;
    }

    return false;
}
