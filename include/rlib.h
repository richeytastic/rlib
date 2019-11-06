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

#include "stdafx.h"
#include <string>
#include <algorithm>
#include <iostream>

#include "rlib/Vec.h"
#include "rlib/Vec2d.h"
#include "rlib/Vectors.h"
#include "rlib/Lock.h"
#include "rlib/ThreadManager.h"
#include "rlib/ThreadSafeQueue.h"
#include "rlib/Pack.h"
#include "rlib/ustring.h"
#include "rlib/CpuTimer.h"
#include "rlib/Model.h"
#include "rlib/ParseXFile.h"
#include "rlib/Scene.h"
#include "rlib/BmpImage.h"
#include "rlib/DataReader.h"
#include "rlib/ModelData.h"
#include "rlib/ProgressUpdater.h"
#include "rlib/FileIO.h"
#include "rlib/HttpClient.h"
#include "rlib/ImageParsing.h"
#include "rlib/Compression.h"
#include "rlib/Exceptions.h"
#include "rlib/Logger.h"
