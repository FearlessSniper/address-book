set(ADDRESS_BOOK_SOURCES Database.cpp DatabaseException.cpp Record.cpp)

# sqlite3 is called unofficial-sqlite3 in vcpkg
if (MSVC)
    find_package(unofficial-sqlite3 CONFIG REQUIRED)
else()
    find_package(SQLite3 REQUIRED)
endif()
find_package(SQLite3 REQUIRED NAMES unofficial-sqlite3)
add_library(lib_address_book ${ADDRESS_BOOK_SOURCES})
target_include_directories(
    lib_address_book PUBLIC ${PROJECT_SOURCE_DIR}/include
    )
target_link_libraries(
    lib_address_book
    $<$<C_COMPILER_ID:MSVC>:unofficial::sqlite3::sqlite3>
    $<$<NOT:$<C_COMPILER_ID:MSVC>>:SQLite::SQLite3>
    )
