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
project(image-png C)

if(NOT TARGET cpufeatures)
add_subdirectory(../cpufeatures ./cpufeatures)
endif()

set(LIBPNG_SOURCES
    image_png.c
    libpng/png.c
    libpng/pngerror.c
    libpng/pngget.c
    libpng/pngmem.c
    libpng/pngpread.c
    libpng/pngread.c
    libpng/pngrio.c
    libpng/pngrtran.c
    libpng/pngrutil.c
    libpng/pngset.c
    libpng/pngtrans.c
    ../image/static_image.c
    ../image/stream/stream.c
    ../image/image_utils.c
    ../image/image_convert.c
    ../image/delegate_image.c
)
set(LIBPNG_INCLUDES
    .
    libpng
    ../image
    ../image/javah
    ../image/stream
)
set(LIBPNG_DEFINITIONS
)
set(LIBPNG_LIBRARIES
    z
    log
)

if (${ANDROID_ABI} STREQUAL "armeabi-v7a")

  enable_language(ASM)

  set(LIBPNG_SOURCES
      ${LIBPNG_SOURCES}
      libpng/arm/arm_init.c
      libpng/arm/filter_neon.S
  )
  set(LIBPNG_INCLUDES
      ${LIBPNG_INCLUDES}
      .
      ${ANDROID_NDK}/sources/android/cpufeatures
  )
  set(LIBPNG_DEFINITIONS
      ${LIBPNG_DEFINITIONS}
      -DPNG_ARM_NEON_OPT=1
      -DPNG_ARM_NEON_IMPLEMENTATION=2
  )
  set(LIBPNG_LIBRARIES
      ${LIBPNG_LIBRARIES}
      cpufeatures
  )

elseif (${ANDROID_ABI} STREQUAL "arm64-v8a")

  enable_language(ASM)

  set(LIBPNG_SOURCES
      ${LIBPNG_SOURCES}
      libpng/arm/arm_init.c
      libpng/arm/filter_neon_intrinsics.c
  )
  set(LIBPNG_INCLUDES
      ${LIBPNG_INCLUDES}
      .
      ${ANDROID_NDK}/sources/android/cpufeatures
  )
  set(LIBPNG_DEFINITIONS
      ${LIBPNG_DEFINITIONS}
      -DPNG_ARM_NEON_OPT=1
      -DPNG_ARM_NEON_IMPLEMENTATION=1
  )
  set(LIBPNG_LIBRARIES
      ${LIBPNG_LIBRARIES}
      cpufeatures
  )

endif ()

if(IMAGE_SINGLE_SHARED_LIB)
    set(LIBPNG_EXPORT_LIBRARIES ${LIBPNG_LIBRARIES} PARENT_SCOPE)
endif()

if(IMAGE_SINGLE_SHARED_LIB)
    # Compile a static library for image-singlelib
    add_library(image-png-static STATIC ${LIBPNG_SOURCES})
    target_include_directories(image-png-static PRIVATE ${LIBPNG_INCLUDES})
    target_compile_definitions(image-png-static PRIVATE ${LIBPNG_DEFINITIONS})
else()
    # Compile a shared library for image-dynamic
    add_library(image-png SHARED ${LIBPNG_SOURCES})
    target_include_directories(image-png PRIVATE ${LIBPNG_INCLUDES})
    target_compile_definitions(image-png PRIVATE ${LIBPNG_DEFINITIONS})
    target_link_libraries(image-png PRIVATE ${LIBPNG_LIBRARIES})
endif()