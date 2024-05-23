cmake_minimum_required(VERSION 3.10)
project(DontStopEat)

set(CMAKE_CXX_STANDARD 17)

find_package(SFML 2.5 COMPONENTS system window graphics network audio REQUIRED)

add_executable(DontStopEat main.cpp AdapterInterface.h Animal.cpp Animal.h Bird.cpp Bird.h Cat.h Cat.cpp CipherInterface.cpp CipherInterface.h DrawPictures.cpp DrawPictures.h Factory.cpp Factory.h Food.cpp Food.h FoodInterface.cpp FoodInterface.h GameMenu.cpp GameMenu.h Horse.cpp Horse.h ISerialazable.h Mammal.cpp Mammal.h Observer.cpp Observer.h Parrot.cpp Parrot.h Subject.cpp Subject.h Table.cpp Table.h TextEffect.cpp TextEffect.h Timer.cpp Timer.h TInteract.cpp TInteract.h TransformInterface.h Rabbit.cpp Rabbit.h)
file(GLOB_RECURSE CPP_SOURCES "*.cpp")

# Добавить include директорию с json.hpp
include_directories("dependencies/include")

if (SFML_FOUND)
    include_directories(${SFML_INCLUDE_DIR})
    target_link_libraries(DontStopEat sfml-audio sfml-network sfml-graphics sfml-window sfml-system)
endif()
