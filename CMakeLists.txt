cmake_minimum_required(VERSION 3.7.2)

set(PATCH_VERSION "1" CACHE INTERNAL "Patch version")
set(PROJECT_VERSION 0.0.${PATCH_VERSION})

project(mnist_fashion VERSION ${PROJECT_VERSION})

configure_file(version.h.in version.h)

add_executable(mnist_fashion_cli main.cpp)
add_library(mnist_fashion lib.cpp)

set_target_properties(mnist_fashion_cli mnist_fashion PROPERTIES
    CXX_STANDARD 14
    CXX_STANDARD_REQUIRED ON
)
target_include_directories(mnist_fashion
    PRIVATE "${CMAKE_BINARY_DIR}"
)

target_link_libraries(mnist_fashion_cli PRIVATE
    mnist_fashion
)

if (MSVC)
    target_compile_options(mnist_fashion_cli PRIVATE
        /W4
    )
    target_compile_options(mnist_fashion PRIVATE
        /W4
    )
else ()
    target_compile_options(mnist_fashion_cli PRIVATE
        -Wall -Wextra -pedantic -Werror
    )
    target_compile_options(mnist_fashion PRIVATE
        -Wall -Wextra -pedantic -Werror
    )
endif()



install(TARGETS mnist_fashion_cli RUNTIME DESTINATION bin)

set(CPACK_GENERATOR DEB)

set(CPACK_PACKAGE_VERSION_MAJOR "${PROJECT_VERSION_MAJOR}")
set(CPACK_PACKAGE_VERSION_MINOR "${PROJECT_VERSION_MINOR}")
set(CPACK_PACKAGE_VERSION_PATCH "${PROJECT_VERSION_PATCH}")

set(CPACK_PACKAGE_CONTACT example@example.com)

include(CPack)

enable_testing()

add_test(test_version test_version)
