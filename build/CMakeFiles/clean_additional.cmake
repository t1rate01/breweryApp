# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  "CMakeFiles\\breweryApp_autogen.dir\\AutogenUsed.txt"
  "CMakeFiles\\breweryApp_autogen.dir\\ParseCache.txt"
  "android-build"
  "breweryApp_autogen"
  )
endif()
