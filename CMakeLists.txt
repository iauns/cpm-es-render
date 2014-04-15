cmake_minimum_required(VERSION 2.8.7 FATAL_ERROR)

#-----------------------------------------------------------------------
# CPM configuration
#-----------------------------------------------------------------------
set(CPM_MODULE_NAME "es_render")
set(CPM_LIB_TARGET_NAME ${CPM_MODULE_NAME})

if ((DEFINED CPM_DIR) AND (DEFINED CPM_UNIQUE_ID) AND (DEFINED CPM_TARGET_NAME))
  set(CPM_LIB_TARGET_NAME ${CPM_TARGET_NAME})
  set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${CPM_DIR})
  include(CPM)
else()
  set (CPM_DIR "${CMAKE_CURRENT_BINARY_DIR}/cpm-packages" CACHE TYPE STRING)
  find_package(Git)
  if(NOT GIT_FOUND)
    message(FATAL_ERROR "CPM requires Git.")
  endif()
  if (NOT EXISTS ${CPM_DIR}/CPM.cmake)
    message(STATUS "Cloning repo (https://github.com/iauns/cpm)")
    execute_process(
      COMMAND "${GIT_EXECUTABLE}" clone https://github.com/iauns/cpm ${CPM_DIR}
      RESULT_VARIABLE error_code
      OUTPUT_QUIET ERROR_QUIET)
    if(error_code)
      message(FATAL_ERROR "CPM failed to get the hash for HEAD")
    endif()
  endif()
  include(${CPM_DIR}/CPM.cmake)
endif()

#-----------------------------------------------------------------------
# CPM Modules
#-----------------------------------------------------------------------

# ++ MODULE: Entity System
CPM_AddModule("es"
  GIT_REPOSITORY "https://github.com/iauns/cpm-entity-system"
  GIT_TAG "origin/master"
  USE_EXISTING_VER TRUE
  EXPORT_MODULE TRUE)

# ++ MODULE: ES Cereal
CPM_AddModule("es_cereal"
  GIT_REPOSITORY "https://github.com/iauns/cpm-es-cereal"
  GIT_TAG "origin/master"
  USE_EXISTING_VER TRUE
  EXPORT_MODULE TRUE)

# ++ MODULE: ES Systems
CPM_AddModule("es_systems"
  GIT_REPOSITORY "https://github.com/iauns/cpm-es-systems"
  GIT_TAG "origin/master"
  USE_EXISTING_VER TRUE)

# ++ MODULE: Async filesystem support
CPM_AddModule("es_fs"
  GIT_REPOSITORY "https://github.com/iauns/cpm-es-fs"
  GIT_TAG "origin/master"
  USE_EXISTING_VER TRUE)

# ++ MODULE: General transforms and components
CPM_AddModule("es_general"
  GIT_REPOSITORY "https://github.com/iauns/cpm-es-general"
  GIT_TAG "origin/master"
  USE_EXISTING_VER TRUE)

# ++ MODULE: Cereal support for serializing GLM.
CPM_AddModule("cereal_glm"
  GIT_REPOSITORY "https://github.com/iauns/cpm-cereal-glm"
  GIT_TAG "origin/master"
  USE_EXISTING_VER TRUE)

# ++ MODULE: GLM
CPM_AddModule("glm"
  GIT_REPOSITORY "https://github.com/iauns/cpm-glm"
  GIT_TAG "1.0.2"
  USE_EXISTING_VER TRUE
  EXPORT_MODULE TRUE)

# ++ MODULE: GL shader management
CPM_AddModule("gl_shaders"
  GIT_REPOSITORY "https://github.com/iauns/cpm-gl-shaders"
  GIT_TAG "1.1.0"
  EXPORT_MODULE TRUE)

# ++ MODULE: GL State
CPM_AddModule("gl_state"
  GIT_REPOSITORY "https://github.com/iauns/cpm-gl-state.git"
  GIT_TAG "1.1.1"
  EXPORT_MODULE TRUE)

# ++ MODULE: Lodepng png loading library.
CPM_AddModule("lodepng"
  GIT_REPOSITORY "https://github.com/iauns/cpm-lodepng.git"
  GIT_TAG "1.0.2")

# ++ MODULE: bserialize library (primarily for loading fonts).
CPM_AddModule("bserialize"
  GIT_REPOSITORY "https://github.com/iauns/cpm-bserialize"
  GIT_TAG "origin/master"
  FORWARD_DECLARATION TRUE)

# ++ MODULE: Arc-Look-At (Autoview Camera)
CPM_AddModule("look_at"
  GIT_REPOSITORY "https://github.com/iauns/cpm-arc-look-at"
  GIT_TAG "1.0.0"
  EXPORT_MODULE TRUE)

# ++ MODULE: var buffer - for generating VBO buffers
CPM_AddModule("var_buffer"
  GIT_REPOSITORY "https://github.com/iauns/cpm-var-buffer"
  GIT_TAG "origin/master"
  EXPORT_MODULE TRUE)

# I don't want more than one version of this module running around.
CPM_ForceOnlyOneModuleVersion()

# This call will ensure all include directories and definitions are present
# in the target. These correspond to the modules that we added above.
CPM_InitModule(${CPM_MODULE_NAME})

#-----------------------------------------------------------------------
# Source
#-----------------------------------------------------------------------

# Globbing has some downsides, but the advantages outweigh the
# disadvantages.
file (GLOB Sources
  "es-render/*.cpp"
  "es-render/*.hpp"
  "es-render/comp/*.hpp"
  "es-render/comp/*.cpp"
  "es-render/systems/*.hpp"
  "es-render/systems/*.cpp"
  "es-render/systems/debug/*.hpp"
  "es-render/systems/debug/*.cpp"
  "es-render/util/*.hpp"
  "es-render/util/*.cpp"
  "es-render/util/helper/*.hpp"
  "es-render/util/helper/*.cpp"
  )

#-----------------------------------------------------------------------
# Library setup
#-----------------------------------------------------------------------

# Build the library.
add_library(${CPM_LIB_TARGET_NAME} ${Sources} ${SystemSpecificSources})
if (NOT EMSCRIPTEN AND CPM_LIBRARIES)
  target_link_libraries(${CPM_LIB_TARGET_NAME} ${CPM_LIBRARIES})
endif()
