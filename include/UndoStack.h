#pragma once
#ifndef RLIB_UNDO_STACK_H
#define RLIB_UNDO_STACK_H

#include <cstdlib>
#include <cassert>

namespace RLIB
{

template <typename T>
class UndoStack
{
public:
    UndoStack( const T& initial, size_t maxSize=30);
    ~UndoStack();

    void push( const T&);   // Push an item onto the undo stack to undo to

    bool canUndo() const;
    bool canRedo() const;

    const T& undo();
    const T& redo();

private:
    const T _original;
    const size_t _maxSz;
    struct UNode;
    UNode* _undos;
    UNode* _cur;
    size_t _count;
};  // end class

#include "template/UndoStack_template.h"

}   // end namespace

#endif
