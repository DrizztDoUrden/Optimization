PROJECT(L2)

FILE(GLOB SOURCE *.cpp)

ADD_EXECUTABLE(L2 ${SOURCE})

ADD_DEPENDENCIES(L2 TestFunctions)

TARGET_LINK_LIBRARIES(L2 PUBLIC TestFunctions)

TARGET_INCLUDE_DIRECTORIES(L2 PRIVATE /)
