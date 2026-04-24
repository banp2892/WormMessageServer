# 1. Сначала версия
cmake_minimum_required(VERSION 3.10)

# 2. Потом название проекта (это уберет твой ворнинг)
project(WormMessageServer LANGUAGES CXX)

# 3. Настройки стандарта
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# 4. Исходники
# Указываем путь к хедерам
include_directories(include)

# Обновляем пути к исходникам
add_executable(WormMessageServer 
    src/main.cpp 
    src/TcpServer.cpp
)

# 5. Линковка (только для Windows)
if(WIN32)
    target_link_libraries(WormMessageServer ws2_32)
endif()