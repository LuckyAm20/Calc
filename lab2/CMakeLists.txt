# CMakeList.txt: проект CMake для lab2; включите исходный код и определения,
# укажите здесь логику для конкретного проекта.
#
cmake_minimum_required (VERSION 3.8)

# Включение горячей перезагрузки для компиляторов MSVC, если поддерживается.
if (POLICY CMP0141)
  cmake_policy(SET CMP0141 NEW)
  set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT "$<IF:$<AND:$<C_COMPILER_ID:MSVC>,$<CXX_COMPILER_ID:MSVC>>,$<$<CONFIG:Debug,RelWithDebInfo>:EditAndContinue>,$<$<CONFIG:Debug,RelWithDebInfo>:ProgramDatabase>>")
endif()

project ("lab2")

add_executable (lab2 "main.cpp"  "node.cpp" "node.h" "xml_file.cpp" "xml_file.h")

configure_file(
    ${CMAKE_CURRENT_SOURCE_DIR}/example.xml
    ${CMAKE_CURRENT_BINARY_DIR}/example.xml
    COPYONLY
)

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET lab2 PROPERTY CXX_STANDARD 17)
endif()

# TODO: Добавьте тесты и целевые объекты, если это необходимо.
