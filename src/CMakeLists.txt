cmake_minimum_required(VERSION 2.8)


add_definitions(-m32)
add_definitions(-nostdlib)
add_definitions(-fno-stack-protector)
add_definitions(-fno-rtti)
add_definitions(-fno-exceptions)

add_custom_command(OUTPUT secbootinit.s.o
    COMMAND gcc -m32 -c -o ${CMAKE_CURRENT_BINARY_DIR}/secbootinit.s.o ${CMAKE_CURRENT_SOURCE_DIR}/secbootinit.s
    DEPENDS secbootinit.s)

add_custom_command(OUTPUT pm_entry.s.o
    COMMAND gcc -m32 -c -o ${CMAKE_CURRENT_BINARY_DIR}/pm_entry.s.o ${CMAKE_CURRENT_SOURCE_DIR}/pm_entry.s
    DEPENDS pm_entry.s)


add_executable(secboot.elf
    pm_entry.s.o
    secbootinit.s.o
    secboot.c
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
    -Wl,-T${CMAKE_CURRENT_SOURCE_DIR}/link.ld
    )

