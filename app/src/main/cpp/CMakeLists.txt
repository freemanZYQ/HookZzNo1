# For more information about using CMake with Android Studio, read the
# documentation: https://d.android.com/studio/projects/add-native-code.html

# Sets the minimum version of CMake required to build the native library.

cmake_minimum_required(VERSION 3.4.1)

# Creates and names a library, sets it as either STATIC
# or SHARED, and provides the relative paths to its source code.
# You can define multiple libraries, and CMake builds them for you.
# Gradle automatically packages shared libraries with your APK.

# 设置项目名称 如果没有其他设置也就是编译的库的名称
set(ProjectName HookZzNo1)

# 添加源文件 确定链接方式
add_library( # Sets the name of the library.
        ${ProjectName}

        # Sets the library as a shared library.
        SHARED

        # Provides a relative path to your source file(s).
        hook_utils.cpp
        hook__main.cpp
        hook_dl.cpp
        hook_libc.cpp)
        

# Searches for a specified prebuilt library and stores the path as a
# variable. Because CMake includes system libraries in the search path by
# default, you only need to specify the name of the public NDK library
# you want to add. CMake verifies that the library exists before
# completing its build.

# 查找日志库
find_library( # Sets the name of the path variable.
        log-lib

        # Specifies the name of the NDK library that
        # you want CMake to locate.0
        log )

# Specifies libraries CMake should link to your target library. You
# can link multiple libraries, such as libraries you define in this
# build script, prebuilt third-party libraries, or system libraries.


# 链接日志库
target_link_libraries( # Specifies the target library.
        ${ProjectName}

        # Links the target library to the log library
        # included in the NDK.
        ${log-lib} )




message(STATUS "[*] initialize HookZz")
macro(SET_OPTION option value)
    set(${option} ${value} CACHE INTERNAL "" FORCE)
endmacro()
SET_OPTION(ARCH arm64)
SET_OPTION(PLATFORM Android)
SET_OPTION(SHARED OFF) 
SET_OPTION(DEBUG ON)
SET_OPTION(CMAKE_VERBOSE_MAKEFILE ON)
add_subdirectory(3rd/HookZz HookZz.out)
target_link_libraries(${ProjectName} hookzz)


