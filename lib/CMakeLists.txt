set(SRC_FILES
        src/bmp_creating.cpp
        src/parser.cpp
        src/process_iterations.cpp
        src/sandpile.cpp
)

include_directories(include)

add_library(sandpile ${SRC_FILES})