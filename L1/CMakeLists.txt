PROJECT(L1)

FILE(GLOB SOURCE *.cpp)

ADD_EXECUTABLE(L1 ${SOURCE})

ADD_DEPENDENCIES(L1 TestFunctions)

TARGET_LINK_LIBRARIES(L1 PUBLIC TestFunctions)

TARGET_INCLUDE_DIRECTORIES(L1 PRIVATE /)
