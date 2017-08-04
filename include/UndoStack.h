/************************************************************************
 * Copyright (C) 2017 Richard Palmer
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 ************************************************************************/

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
