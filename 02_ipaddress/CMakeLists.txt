cmake_minimum_required(VERSION 3.10)

set(PATCH_VERSION "1" CACHE INTERNAL "Patch version")
set(PROJECT_VERSION 0.0.${PATCH_VERSION})

project(ip_filter VERSION ${PROJECT_VERSION})

find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})

add_library(filter 
    ip_filter.cpp
)

add_executable(ip_filter
    main.cpp
)

target_link_libraries(ip_filter PRIVATE
    filter
)

target_include_directories(filter
    PRIVATE "${CMAKE_BINARY_DIR}"
)

add_executable(test_filter
    test_filter.cpp 
)

if (MSVC)
    target_compile_options(ip_filter PRIVATE
        /W4
    )
    target_compile_options(filter PRIVATE
        /W4
    )
    target_compile_options(test_filter PRIVATE
        /W4
    )
else ()
    target_compile_options(ip_filter PRIVATE
        -Wall -Wextra -pedantic -Werror
    )
    target_compile_options(filter PRIVATE
        -Wall -Wextra -pedantic -Werror
    )
    target_compile_options(test_filter PRIVATE
        -Wall -Wextra -pedantic -Werror
    )
endif()

set_target_properties(ip_filter filter test_filter PROPERTIES
    CXX_STANDARD 14
    CXX_STANDARD_REQUIRED ON
)

install(TARGETS ip_filter RUNTIME DESTINATION bin)

set(CPACK_GENERATOR DEB)

set(CPACK_PACKAGE_VERSION_MAJOR "${PROJECT_VERSION_MAJOR}")
set(CPACK_PACKAGE_VERSION_MINOR "${PROJECT_VERSION_MINOR}")
set(CPACK_PACKAGE_VERSION_PATCH "${PROJECT_VERSION_PATCH}")

set(CPACK_PACKAGE_CONTACT example@example.com)

include(CPack)

enable_testing()

target_link_libraries(
    test_filter
    GTest::gtest_main
    filter
)

include(GoogleTest)
gtest_discover_tests(test_filter)

