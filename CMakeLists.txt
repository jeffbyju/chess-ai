cmake_minimum_required(VERSION 3.10)
project(ChessDQNQt LANGUAGES CXX)

# 1) Find Torch (libtorch)
find_package(Torch REQUIRED)

# 2) Find Qt5
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

find_package(Qt5 COMPONENTS Widgets Core Gui REQUIRED)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${TORCH_CXX_FLAGS}")

# Source files
set(SRC
    src/main.cpp
    src/ChessLogic.cpp
    src/DQN.cpp
    src/ReplayBuffer.cpp
    src/GameWindow.cpp
)

set(HDR
    src/ChessLogic.h
    src/DQN.h
    src/ReplayBuffer.h
    src/GameWindow.h
)

add_executable(ChessDQNQt ${SRC} ${HDR})

target_link_libraries(ChessDQNQt
    "${TORCH_LIBRARIES}"
    Qt5::Widgets
    Qt5::Core
    Qt5::Gui
)

# If needed, set rpath or copy libtorch .so/.dylib to final output folder
