# $ cmake -DCMAKE_TOOLCHAIN_FILE=<dir>/cmake/toolchain-rpi.cmake <dir>
# クロスコンパイル用の環境設定

SET(CMAKE_SYSTEM_NAME Linux)
SET(CMAKE_SYSTEM_VERSION 1)

SET(CMAKE_FIND_ROOT_PATH /opt/rpi-sysroot)
SET(CMAKE_SYSROOT /opt/rpi-sysroot)

SET(CMAKE_C_COMPILER /usr/bin/clang)
SET(CMAKE_CXX_COMPILER /usr/bin/clang++)
SET(CMAKE_AR /usr/bin/ar CACHE FILEPATH "Archiver")

SET(triple arm-linux-gnueabihf)
SET(CMAKE_C_COMPILER_TARGET ${triple})
SET(CMAKE_CXX_COMPILER_TARGET ${triple})

# set(CMAKE_MAKE_PROGRAM ninja)

SET(CMAKE_FIND_ROOT_PATH_MODE_PROGRAM NEVER)

SET(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY ONLY)
SET(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE ONLY)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -march=armv7-a -mfloat-abi=hard -ftree-vectorize -mfpu=neon")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -march=armv7-a -mfloat-abi=hard -ftree-vectorize -mfpu=neon")

