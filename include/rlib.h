/************************************************************************
 * Copyright (C) 2019 Richard Palmer
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

#include <string>
#include <algorithm>
#include <iostream>

#include "rlib/ConvexOptimiser.h"
#include "rlib/Convert.h"
#include "rlib/CmdLnArgsParser.h"
#include "rlib/CpuTimer.h"
#include "rlib/Exceptions.h"
#include "rlib/FileIO.h"
#include "rlib/LinearRegressor.h"
#include "rlib/MathUtil.h"
#include "rlib/Memory.h"
#include "rlib/NewtonRaphson.h"
#include "rlib/Pack.h"
#include "rlib/Profiling.h"
#include "rlib/ProgressDelegate.h"
#include "rlib/ProgressUpdater.h"
#include "rlib/Random.h"
#include "rlib/RangedScalarDistribution.h"
#include "rlib/Round.h"
#include "rlib/SymmetricBitSet.h"
#include "rlib/SymmetricMatrix.h"
#include "rlib/Timer.h"
#include "rlib/Vectors.h"
