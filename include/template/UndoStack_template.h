#include "UndoStack.h"
using RLIB::UndoStack;

template <typename T>
struct UndoStack<T>::UNode
{
    UNode( const T& t) : item(t), prev(NULL), next(NULL) {}

    T item;
    UNode* prev;
    UNode* next;
};  // end struct


template <typename T>
UndoStack<T>::UndoStack( const T& t, size_t maxSz)
    : _original(t), _maxSz( maxSz < 1 ? 1 : maxSz), _undos(NULL)
{
    _undos = new UNode(t);
    _cur = _undos;
    _count = 1;
}   // end ctor


template <typename T>
UndoStack<T>::~UndoStack()
{
    UNode* cnode;
    while ( _undos)
    {
        cnode = _undos;
        _undos = cnode->next;
        delete cnode;
    }   // end while
}   // end dtor


template <typename T>
void UndoStack<T>::push( const T& t)
{
    UNode* rn = _cur->next;
    while ( rn)
    {
        UNode* nn = rn->next;
        delete rn;
        rn = nn;
        _count--;
    }   // end while

    // Add the new current
    UNode* newUNode = new UNode(t);
    _cur->next = newUNode;
    newUNode->prev = _cur;
    _cur = newUNode;
    _count++;

    // If the maximum size has been reached, remove the oldest to make room.
    while ( _count > _maxSz)
    {
        UNode* newStart = _undos->next;
        newStart->prev = NULL;
        delete _undos;
        _undos = newStart;
        _undos->item = _original;   // Ensure the original is always available
        _count--;
    }   // end while
}   // end push


template <typename T>
bool UndoStack<T>::canUndo() const
{
    return _cur->prev != NULL;
}   // end canUndo


template <typename T>
bool UndoStack<T>::canRedo() const
{
    return _cur->next != NULL;
}   // end canRedo


template <typename T>
const T& UndoStack<T>::undo()
{
    assert(canUndo());
    _cur = _cur->prev;
    return _cur->item;
}   // end undo


template <typename T>
const T& UndoStack<T>::redo()
{
    assert(canRedo());
    _cur = _cur->next;
    return _cur->item;
}   // end redo
