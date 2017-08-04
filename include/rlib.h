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

#include "Vec.h"
#include "Vec2d.h"
#include "Vectors.h"
#include "Lock.h"
#include "ThreadManager.h"
#include "ThreadSafeQueue.h"
#include "Pack.h"
#include "ustring.h"
#include "CpuTimer.h"
#include "Model.h"
#include "ParseXFile.h"
#include "Scene.h"
#include "BmpImage.h"
#include "DataReader.h"
#include "ModelData.h"
#include "ProgressUpdater.h"
#include "FileIO.h"
#include "HttpClient.h"
#include "ImageParsing.h"
#include "Compression.h"
#include "Exceptions.h"
#include "Logger.h"
