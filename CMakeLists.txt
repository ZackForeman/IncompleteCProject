cmake_minimum_required(VERSION 3.16)
project(AArch64 C)

set(CMAKE_C_STANDARD 99)

add_executable(emulate Emulator/main.c
        Emulator/Processor.h
        Emulator/Processor.c
        Emulator/Decode.c
        Emulator/Decode.h
        Emulator/Execute.c
        Emulator/Execute.h
        Emulator/Execution/DPImmediate.c
        Emulator/Execution/DPImmediate.h
)
