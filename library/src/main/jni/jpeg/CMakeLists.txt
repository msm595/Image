# Copyright 2018 Hippo Seven
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#     http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.

cmake_minimum_required(VERSION 3.4.1)
project(image-jpeg C)

set(LIBJPEG_TURBO_SOURCES
    image_jpeg.c
    libjpeg-turbo/jaricom.c
    libjpeg-turbo/jcomapi.c
    libjpeg-turbo/jdapimin.c
    libjpeg-turbo/jdapistd.c
    libjpeg-turbo/jdarith.c
    libjpeg-turbo/jdatasrc.c
    libjpeg-turbo/jdatasrc-tj.c
    libjpeg-turbo/jdcoefct.c
    libjpeg-turbo/jdcolor.c
    libjpeg-turbo/jddctmgr.c
    libjpeg-turbo/jdhuff.c
    libjpeg-turbo/jdinput.c
    libjpeg-turbo/jdmainct.c
    libjpeg-turbo/jdmarker.c
    libjpeg-turbo/jdmaster.c
    libjpeg-turbo/jdmerge.c
    libjpeg-turbo/jdphuff.c
    libjpeg-turbo/jdpostct.c
    libjpeg-turbo/jdsample.c
    libjpeg-turbo/jdtrans.c
    libjpeg-turbo/jerror.c
    libjpeg-turbo/jfdctflt.c
    libjpeg-turbo/jfdctfst.c
    libjpeg-turbo/jfdctint.c
    libjpeg-turbo/jidctflt.c
    libjpeg-turbo/jidctfst.c
    libjpeg-turbo/jidctint.c
    libjpeg-turbo/jidctred.c
    libjpeg-turbo/jmemmgr.c
    libjpeg-turbo/jmemnobs.c
    libjpeg-turbo/jquant1.c
    libjpeg-turbo/jquant2.c
    libjpeg-turbo/jutils.c
    ../image/static_image.c
    ../image/image_convert.c
    ../image/image_utils.c
)
set(LIBJPEG_TURBO_INCLUDES
    .
    libjpeg-turbo
    ../image
    ../image/javah
    ../image/stream
)
set(LIBJPEG_TURBO_DEFINITIONS
)
set(LIBJPEG_TURBO_LIBRARIES
    log
)

if (${ANDROID_ABI} STREQUAL "armeabi-v7a")

  enable_language(ASM)

  set(LIBJPEG_TURBO_SOURCES
      ${LIBJPEG_TURBO_SOURCES}
      libjpeg-turbo/simd/jsimd_arm.c
      libjpeg-turbo/simd/jsimd_arm_neon.S
  )

elseif (${ANDROID_ABI} STREQUAL "arm64-v8a")

  enable_language(ASM)

  set(LIBJPEG_TURBO_SOURCES
      ${LIBJPEG_TURBO_SOURCES}
      libjpeg-turbo/simd/jsimd_arm64.c
      libjpeg-turbo/simd/jsimd_arm64_neon.S
  )

elseif (${ANDROID_ABI} STREQUAL "x86")

  enable_language(ASM_NASM)

  set(LIBJPEG_TURBO_SOURCES
      ${LIBJPEG_TURBO_SOURCES}
      libjpeg-turbo/simd/jsimd_i386.c
      libjpeg-turbo/simd/jsimdcpu.asm
      libjpeg-turbo/simd/jfdctflt-3dn.asm
      libjpeg-turbo/simd/jidctflt-3dn.asm
      libjpeg-turbo/simd/jquant-3dn.asm
      libjpeg-turbo/simd/jccolor-mmx.asm
      libjpeg-turbo/simd/jcgray-mmx.asm
      libjpeg-turbo/simd/jcsample-mmx.asm
      libjpeg-turbo/simd/jdcolor-mmx.asm
      libjpeg-turbo/simd/jdmerge-mmx.asm
      libjpeg-turbo/simd/jdsample-mmx.asm
      libjpeg-turbo/simd/jfdctfst-mmx.asm
      libjpeg-turbo/simd/jfdctint-mmx.asm
      libjpeg-turbo/simd/jidctfst-mmx.asm
      libjpeg-turbo/simd/jidctint-mmx.asm
      libjpeg-turbo/simd/jidctred-mmx.asm
      libjpeg-turbo/simd/jquant-mmx.asm
      libjpeg-turbo/simd/jfdctflt-sse.asm
      libjpeg-turbo/simd/jidctflt-sse.asm
      libjpeg-turbo/simd/jquant-sse.asm
      libjpeg-turbo/simd/jccolor-sse2.asm
      libjpeg-turbo/simd/jcgray-sse2.asm
      libjpeg-turbo/simd/jchuff-sse2.asm
      libjpeg-turbo/simd/jcsample-sse2.asm
      libjpeg-turbo/simd/jdcolor-sse2.asm
      libjpeg-turbo/simd/jdmerge-sse2.asm
      libjpeg-turbo/simd/jdsample-sse2.asm
      libjpeg-turbo/simd/jfdctfst-sse2.asm
      libjpeg-turbo/simd/jfdctint-sse2.asm
      libjpeg-turbo/simd/jidctflt-sse2.asm
      libjpeg-turbo/simd/jidctfst-sse2.asm
      libjpeg-turbo/simd/jidctint-sse2.asm
      libjpeg-turbo/simd/jidctred-sse2.asm
      libjpeg-turbo/simd/jquantf-sse2.asm
      libjpeg-turbo/simd/jquanti-sse2.asm
  )

  set(CMAKE_ASM_NASM_COMPILER_ARG1 "-DELF -DPIC")

elseif (${ANDROID_ABI} STREQUAL "x86_64")

  enable_language(ASM_NASM)

  set(LIBJPEG_TURBO_SOURCES
      ${LIBJPEG_TURBO_SOURCES}
      libjpeg-turbo/simd/jsimd_x86_64.c
      libjpeg-turbo/simd/jfdctflt-sse-64.asm
      libjpeg-turbo/simd/jccolor-sse2-64.asm
      libjpeg-turbo/simd/jcgray-sse2-64.asm
      libjpeg-turbo/simd/jchuff-sse2-64.asm
      libjpeg-turbo/simd/jcsample-sse2-64.asm
      libjpeg-turbo/simd/jdcolor-sse2-64.asm
      libjpeg-turbo/simd/jdmerge-sse2-64.asm
      libjpeg-turbo/simd/jdsample-sse2-64.asm
      libjpeg-turbo/simd/jfdctfst-sse2-64.asm
      libjpeg-turbo/simd/jfdctint-sse2-64.asm
      libjpeg-turbo/simd/jidctflt-sse2-64.asm
      libjpeg-turbo/simd/jidctfst-sse2-64.asm
      libjpeg-turbo/simd/jidctint-sse2-64.asm
      libjpeg-turbo/simd/jidctred-sse2-64.asm
      libjpeg-turbo/simd/jquantf-sse2-64.asm
      libjpeg-turbo/simd/jquanti-sse2-64.asm
  )

  set(CMAKE_ASM_NASM_COMPILER_ARG1 "-D__x86_64__ -DELF -DPIC")

else ()

  set(LIBJPEG_TURBO_SOURCES
      ${LIBJPEG_TURBO_SOURCES}
      libjpeg-turbo/jsimd_none.c
  )

endif ()

if(IMAGE_SINGLE_SHARED_LIB)
    set(LIBJPEG_TURBO_EXPORT_LIBRARIES ${LIBJPEG_TURBO_LIBRARIES} PARENT_SCOPE)
endif()

if(IMAGE_SINGLE_SHARED_LIB)
    # Compile a static library for image-singlelib
    add_library(image-jpeg-static STATIC ${LIBJPEG_TURBO_SOURCES})
    target_include_directories(image-jpeg-static PRIVATE ${LIBJPEG_TURBO_INCLUDES})
    target_compile_definitions(image-jpeg-static PRIVATE ${LIBJPEG_TURBO_DEFINITIONS})
else()
    # Compile a shared library for image-dynamic
    add_library(image-jpeg SHARED ${LIBJPEG_TURBO_SOURCES})
    target_include_directories(image-jpeg PRIVATE ${LIBJPEG_TURBO_INCLUDES})
    target_compile_definitions(image-jpeg PRIVATE ${LIBJPEG_TURBO_DEFINITIONS})
    target_link_libraries(image-jpeg PRIVATE ${LIBJPEG_TURBO_LIBRARIES})
endif()
