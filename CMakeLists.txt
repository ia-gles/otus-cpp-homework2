cmake_minimum_required(VERSION 3.12)

set(PATCH_VERSION "1" CACHE INTERNAL "Patch version")
set(PROJECT_VERSION 0.0.${PATCH_VERSION})

project(ip_filter VERSION ${PROJECT_VERSION})

option(WITH_BOOST_TEST "Whether to build Boost test" OFF)
option(WITH_GOOGLE_TEST "Whether to build Google test" ON)

configure_file(version.h.in version.h)

add_executable(ip_filter IP.hpp main.cpp)
add_library(ip_filter_lib lib.cpp)

set_target_properties(ip_filter ip_filter_lib PROPERTIES
    CXX_STANDARD 17
    CXX_STANDARD_REQUIRED ON
)

target_include_directories(ip_filter_lib
    PRIVATE "${CMAKE_BINARY_DIR}"
)

target_link_libraries(ip_filter PRIVATE
    ip_filter_lib
)

if(WITH_BOOST_TEST)
    find_package(Boost COMPONENTS unit_test_framework REQUIRED)
    add_executable(ip_filter_test test_version.cpp)

    set_target_properties(ip_filter_test PROPERTIES
        CXX_STANDARD 17
        CXX_STANDARD_REQUIRED ON
    )

    set_target_properties(ip_filter_test PROPERTIES
        COMPILE_DEFINITIONS BOOST_TEST_DYN_LINK
        INCLUDE_DIRECTORIES ${Boost_INCLUDE_DIR}
    )

    target_link_libraries(ip_filter_test
        ${Boost_LIBRARIES}
        ip_filter_lib
    )
endif()

if(WITH_GOOGLE_TEST)
    add_executable(ip_filter_gtest gtest_version.cpp)

    include(FetchContent)
    FetchContent_Declare(
        googletest
	GIT_REPOSITORY https://github.com/google/googletest.git
        GIT_TAG v1.16.0
    )

    # For Windows: Prevent overriding the parent project's compiler/linker settings
    set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
    FetchContent_MakeAvailable(googletest)

    set_target_properties(ip_filter_gtest PROPERTIES
        CXX_STANDARD 17
        CXX_STANDARD_REQUIRED ON
    )
    
    target_link_libraries(ip_filter_gtest
        GTest::gtest_main
        ip_filter_lib
    )
endif()

if (MSVC)
    target_compile_options(ip_filter PRIVATE
        /W4
    )
    target_compile_options(ip_filter_lib PRIVATE
        /W4
    )
    if(WITH_BOOST_TEST)
        target_compile_options(ip_filter_test PRIVATE
            /W4
        )
    endif()
else ()
    target_compile_options(ip_filter PRIVATE
        -Wall -Wextra -pedantic -Werror
    )
    target_compile_options(ip_filter_lib PRIVATE
        -Wall -Wextra -pedantic -Werror
    )
    if(WITH_BOOST_TEST)
        target_compile_options(ip_filter_test PRIVATE
            -Wall -Wextra -pedantic -Werror
        )
    endif()
    if(WITH_GOOGLE_TEST)
	target_compile_options(ip_filter_gtest PRIVATE
	    -Wall -Wextra -pedantic -Werror
	)
    endif()
endif()

install(TARGETS ip_filter RUNTIME DESTINATION bin)

set(CPACK_GENERATOR DEB)
set(CPACK_PACKAGE_VERSION_MAJOR "${PROJECT_VERSION_MAJOR}")
set(CPACK_PACKAGE_VERSION_MINOR "${PROJECT_VERSION_MINOR}")
set(CPACK_PACKAGE_VERSION_PATCH "${PROJECT_VERSION_PATCH}")
set(CPACK_PACKAGE_CONTACT example@example.com)
include(CPack)

if(WITH_BOOST_TEST)
    enable_testing()
    add_test(ip_filter_test ip_filter_test)
endif()

if(WITH_GOOGLE_TEST)
    enable_testing()
    add_test(ip_filter_gtest ip_filter_gtest)

    include(GoogleTest)
    gtest_discover_tests(ip_filter_gtest)
endif()
