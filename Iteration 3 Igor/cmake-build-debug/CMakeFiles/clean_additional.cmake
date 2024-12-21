# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  "CMakeFiles\\waterquality_autogen.dir\\AutogenUsed.txt"
  "CMakeFiles\\waterquality_autogen.dir\\ParseCache.txt"
  "waterquality_autogen"
  )
endif()
