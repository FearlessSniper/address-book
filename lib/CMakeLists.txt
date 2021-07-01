set(ADDRESS_BOOK_SOURCES Database.cpp DatabaseException.cpp Record.cpp)

find_package(SQLite3)
add_library(lib_address_book ${ADDRESS_BOOK_SOURCES})
target_include_directories(
    lib_address_book PUBLIC ${PROJECT_SOURCE_DIR}/include
    )
target_link_libraries(lib_address_book SQLite::SQLite3)
