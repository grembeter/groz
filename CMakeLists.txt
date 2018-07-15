cmake_minimum_required(VERSION 3.6)

set(CMAKE_TOOLCHAIN_FILE "${CMAKE_SOURCE_DIR}/toolchain.cmk")

project(groz C)

set(TARGET_ARCH "armv5te")
set(TARGET_CPU "arm926ej-s")

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -mcpu=${TARGET_CPU} -march=${TARGET_ARCH} -msoft-float" CACHE STRING "")

set(DIALECT "-ATT")
set(CMAKE_ASM${DIALECT}_SOURCE_FILE_EXTENSIONS "S;s;asm")
enable_language(ASM-ATT)

set(CMAKE_ASM${DIALECT}_FLAGS "-march=${TARGET_ARCH} -mcpu=${TARGET_CPU} -mlittle-endian -EL --warn --fatal-warnings")
set(CMAKE_ASM${DIALECT}_FLAGS_DEBUG "-g")
set(CMAKE_ASM${DIALECT}_FLAGS_RELEASE "--strip-local-absolute")

set(CMAKE_C_LINK_FLAGS "-A ${TARGET_ARCH} --no-gc-sections -static --stats --print-gc-sections")
set(CMAKE_C_LINK_FLAGS "${CMAKE_C_LINK_FLAGS} -Map ${CMAKE_PROJECT_NAME}.map -T ${CMAKE_SOURCE_DIR}/mxslink.lds")
set(CMAKE_C_LINK_EXECUTABLE "<CMAKE_LINKER> <OBJECTS> <CMAKE_C_LINK_FLAGS> <LINK_FLAGS> -o <TARGET> <LINK_LIBRARIES>")

execute_process(
  COMMAND ${CMAKE_C_COMPILER} -print-libgcc-file-name
  OUTPUT_VARIABLE TARGET_LIBGCC
  OUTPUT_STRIP_TRAILING_WHITESPACE
  )

execute_process(
  COMMAND ${CMAKE_C_COMPILER} -print-file-name=libc.a
  OUTPUT_VARIABLE TARGET_LIBC
  OUTPUT_STRIP_TRAILING_WHITESPACE
  )

add_custom_command(
  OUTPUT "${CMAKE_BINARY_DIR}/mkimage"
  COMMAND "${CMAKE_SOURCE_DIR}/scripts/build_mkimage"
  )

include_directories("sources/include")

add_subdirectory("sources/hurd")
add_subdirectory("sources/diag")

add_custom_target(uboot_mkimage ALL DEPENDS "${CMAKE_BINARY_DIR}/mkimage")
add_executable(${CMAKE_PROJECT_NAME} "sources/entry.S" "sources/startup.c")
target_link_libraries(${CMAKE_PROJECT_NAME} diag hurd ${TARGET_LIBC} ${TARGET_LIBGCC})
add_dependencies(${CMAKE_PROJECT_NAME} uboot_mkimage)

add_custom_command(
  TARGET ${CMAKE_PROJECT_NAME}
  POST_BUILD
  COMMAND "${CMAKE_OBJDUMP}" -S -M reg-names-raw -f -F -x -w "$<TARGET_FILE:${CMAKE_PROJECT_NAME}>" > "$<TARGET_FILE:${CMAKE_PROJECT_NAME}>.asm"
  COMMAND "${CMAKE_OBJCOPY}" -O binary "$<TARGET_FILE:${CMAKE_PROJECT_NAME}>" "$<TARGET_FILE:${CMAKE_PROJECT_NAME}>.bin"
  COMMAND "${CMAKE_BINARY_DIR}/mkimage" -T mxsimage -d "${CMAKE_SOURCE_DIR}/mxsimage.cfg" -n "${CMAKE_SOURCE_DIR}/mxsimage.cfg" "$<TARGET_FILE:${CMAKE_PROJECT_NAME}>.sb"
  COMMAND ${CMAKE_COMMAND} -E cmake_echo_color --switch=$(COLOR) --blue "$<TARGET_FILE:${CMAKE_PROJECT_NAME}>"
  COMMAND ${CMAKE_COMMAND} -E cmake_echo_color --switch=$(COLOR) --blue "$<TARGET_FILE:${CMAKE_PROJECT_NAME}>.sb"
  COMMENT "Generating ${CMAKE_PROJECT_NAME} in ${CMAKE_BINARY_DIR}"
  )
