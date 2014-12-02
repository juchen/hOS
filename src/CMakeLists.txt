cmake_minimum_required(VERSION 2.8)


add_definitions(-m32)
add_definitions(-nostdlib)
add_definitions(-fno-stack-protector)
add_definitions(-fno-rtti)
add_definitions(-fno-exceptions)

add_custom_command(OUTPUT secbootinit.s.o
    COMMAND gcc -m32 -c -o ${CMAKE_CURRENT_BINARY_DIR}/secbootinit.s.o ${CMAKE_CURRENT_SOURCE_DIR}/secbootinit.s
    DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/secbootinit.s)

add_custom_command(OUTPUT pm_entry.s.o
    COMMAND gcc -m32 -c -o ${CMAKE_CURRENT_BINARY_DIR}/pm_entry.s.o ${CMAKE_CURRENT_SOURCE_DIR}/pm_entry.s
    DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/pm_entry.s)

add_custom_command(OUTPUT boot3.s.o
    COMMAND gcc -m32 -c -o ${CMAKE_CURRENT_BINARY_DIR}/boot3.s.o ${CMAKE_CURRENT_SOURCE_DIR}/boot3.s
    DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/boot3.s)

add_library(boot1 STATIC boot1.c)

set_target_properties(boot1
    PROPERTIES
        COMPILE_FLAGS -Os
    )

add_executable(boot.elf
    boot3.s.o
    )

set_target_properties(boot.elf
    PROPERTIES
        LINKER_LANGUAGE CXX
    )

target_link_libraries(boot.elf
        boot1
        -m32
        -fno-stack-protector
        -nostdlib
        -Wl,-emain
        -Wl,-N
        -Wl,-Ttext=0x0
        )
# secbootinit.s.o has to be the first 16-bit file. But cmake postpone custom command outputs.
# Make secboot.c a lib so that it appears in rear of secbootinit.s.o
add_library(secboot STATIC secboot.c)

add_executable(secboot.elf
    secbootinit.s.o
    pm_entry.s.o
    printf-stdarg.c
    debug.cpp
    putchar.cpp
    sys_struct.cpp
    timer8253.cpp
    x86functions.cpp
    scheduler.cpp
    thread.cpp
    idlethread.cpp
    comport.cpp
    isr.cpp
    syscall.cpp
    user_syscall.cpp
    pm_c_entry.cpp
    )

target_link_libraries(secboot.elf
    -m32
    -nostdlib
    -fno-stack-protector
    -Wl,-T${CMAKE_CURRENT_SOURCE_DIR}/link.ld
    -Wl,-emain
    secboot
    )

