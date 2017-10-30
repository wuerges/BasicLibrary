cmake_minimum_required (VERSION 2.6)
project (BasicLibrary)
include_directories("include")
add_library(BasicLibrary 
  src/BCommandLine.cpp src/BFile.cpp src/BFunctions.cpp src/BMessages.cpp  src/BPoint.cpp src/BSet.cpp
  src/BState.cpp src/BString.cpp src/BTimeStatistics.cpp src/BVector.cpp src/nrutil.cpp)
