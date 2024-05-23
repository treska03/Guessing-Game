# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  "CMakeFiles\\CPP_PROJEKT_RANDOM_autogen.dir\\AutogenUsed.txt"
  "CMakeFiles\\CPP_PROJEKT_RANDOM_autogen.dir\\ParseCache.txt"
  "CPP_PROJEKT_RANDOM_autogen"
  )
endif()
