# Listing from https://cmake.org/cmake/help/v3.0/manual/cmake-variables.7.html?highlight=cmake%20variables

function(DebugBuildEnvShow varName)
    if(DEFINED ${varName})
        message(STATUS "	${varName}: ${${varName}}")
    endif()
endfunction()

message(STATUS "========================================================================================================")
message(STATUS " ")
message(STATUS "Variables that Provide Information:")
message(STATUS " ")
DebugBuildEnvShow(CMAKE_AR)
DebugBuildEnvShow(CMAKE_ARGC)
DebugBuildEnvShow(CMAKE_ARGV0)
DebugBuildEnvShow(CMAKE_BINARY_DIR)
DebugBuildEnvShow(CMAKE_BUILD_TOOL)
DebugBuildEnvShow(CMAKE_CACHEFILE_DIR)
DebugBuildEnvShow(CMAKE_CACHE_MAJOR_VERSION)
DebugBuildEnvShow(CMAKE_CACHE_MINOR_VERSION)
DebugBuildEnvShow(CMAKE_CACHE_PATCH_VERSION)
DebugBuildEnvShow(CMAKE_CFG_INTDIR)
DebugBuildEnvShow(CMAKE_COMMAND)
DebugBuildEnvShow(CMAKE_CPACK_COMMAND)
DebugBuildEnvShow(CMAKE_CROSSCOMPILING)
DebugBuildEnvShow(CMAKE_CROSSCOMPILING_EMULATOR)
DebugBuildEnvShow(CMAKE_CTEST_COMMAND)
DebugBuildEnvShow(CMAKE_CURRENT_BINARY_DIR)
DebugBuildEnvShow(CMAKE_CURRENT_LIST_DIR)
DebugBuildEnvShow(CMAKE_CURRENT_LIST_FILE)
DebugBuildEnvShow(CMAKE_CURRENT_LIST_LINE)
DebugBuildEnvShow(CMAKE_CURRENT_SOURCE_DIR)
DebugBuildEnvShow(CMAKE_DIRECTORY_LABELS)
DebugBuildEnvShow(CMAKE_DL_LIBS)
DebugBuildEnvShow(CMAKE_DOTNET_TARGET_FRAMEWORK_VERSION)
DebugBuildEnvShow(CMAKE_EDIT_COMMAND)
DebugBuildEnvShow(CMAKE_EXECUTABLE_SUFFIX)
DebugBuildEnvShow(CMAKE_EXTRA_GENERATOR)
DebugBuildEnvShow(CMAKE_EXTRA_SHARED_LIBRARY_SUFFIXES)
DebugBuildEnvShow(CMAKE_FIND_PACKAGE_NAME)
DebugBuildEnvShow(CMAKE_FIND_PACKAGE_SORT_DIRECTION)
DebugBuildEnvShow(CMAKE_FIND_PACKAGE_SORT_ORDER)
DebugBuildEnvShow(CMAKE_GENERATOR)
DebugBuildEnvShow(CMAKE_GENERATOR_INSTANCE)
DebugBuildEnvShow(CMAKE_GENERATOR_PLATFORM)
DebugBuildEnvShow(CMAKE_GENERATOR_TOOLSET)
DebugBuildEnvShow(CMAKE_IMPORT_LIBRARY_PREFIX)
DebugBuildEnvShow(CMAKE_IMPORT_LIBRARY_SUFFIX)
DebugBuildEnvShow(CMAKE_JOB_POOL_COMPILE)
DebugBuildEnvShow(CMAKE_JOB_POOL_LINK)
DebugBuildEnvShow(CMAKE_JOB_POOLS)
#DebugBuildEnvShow(CMAKE_<LANG>_COMPILER_AR)
#DebugBuildEnvShow(CMAKE_<LANG>_COMPILER_RANLIB)
DebugBuildEnvShow(CMAKE_LINK_LIBRARY_SUFFIX)
DebugBuildEnvShow(CMAKE_LINK_SEARCH_END_STATIC)
DebugBuildEnvShow(CMAKE_LINK_SEARCH_START_STATIC)
DebugBuildEnvShow(CMAKE_MAJOR_VERSION)
DebugBuildEnvShow(CMAKE_MAKE_PROGRAM)
DebugBuildEnvShow(CMAKE_MATCH_COUNT)
#DebugBuildEnvShow(CMAKE_MATCH_<n>)
DebugBuildEnvShow(CMAKE_MINIMUM_REQUIRED_VERSION)
DebugBuildEnvShow(CMAKE_MINOR_VERSION)
DebugBuildEnvShow(CMAKE_NETRC)
DebugBuildEnvShow(CMAKE_NETRC_FILE)
DebugBuildEnvShow(CMAKE_PARENT_LIST_FILE)
DebugBuildEnvShow(CMAKE_PATCH_VERSION)
DebugBuildEnvShow(CMAKE_PROJECT_DESCRIPTION)
DebugBuildEnvShow(CMAKE_PROJECT_HOMEPAGE_URL)
DebugBuildEnvShow(CMAKE_PROJECT_NAME)
DebugBuildEnvShow(CMAKE_PROJECT_VERSION)
DebugBuildEnvShow(CMAKE_PROJECT_VERSION_MAJOR)
DebugBuildEnvShow(CMAKE_PROJECT_VERSION_MINOR)
DebugBuildEnvShow(CMAKE_PROJECT_VERSION_PATCH)
DebugBuildEnvShow(CMAKE_PROJECT_VERSION_TWEAK)
DebugBuildEnvShow(CMAKE_RANLIB)
DebugBuildEnvShow(CMAKE_ROOT)
DebugBuildEnvShow(CMAKE_RULE_MESSAGES)
DebugBuildEnvShow(CMAKE_SCRIPT_MODE_FILE)
DebugBuildEnvShow(CMAKE_SHARED_LIBRARY_PREFIX)
DebugBuildEnvShow(CMAKE_SHARED_LIBRARY_SUFFIX)
DebugBuildEnvShow(CMAKE_SHARED_MODULE_PREFIX)
DebugBuildEnvShow(CMAKE_SHARED_MODULE_SUFFIX)
DebugBuildEnvShow(CMAKE_SIZEOF_VOID_P)
DebugBuildEnvShow(CMAKE_SKIP_INSTALL_RULES)
DebugBuildEnvShow(CMAKE_SKIP_RPATH)
DebugBuildEnvShow(CMAKE_SOURCE_DIR)
DebugBuildEnvShow(CMAKE_STATIC_LIBRARY_PREFIX)
DebugBuildEnvShow(CMAKE_STATIC_LIBRARY_SUFFIX)
DebugBuildEnvShow(CMAKE_TOOLCHAIN_FILE)
DebugBuildEnvShow(CMAKE_TWEAK_VERSION)
DebugBuildEnvShow(CMAKE_VERBOSE_MAKEFILE)
DebugBuildEnvShow(CMAKE_VERSION)
DebugBuildEnvShow(CMAKE_VS_DEVENV_COMMAND)
DebugBuildEnvShow(CMAKE_VS_MSBUILD_COMMAND)
DebugBuildEnvShow(CMAKE_VS_NsightTegra_VERSION)
DebugBuildEnvShow(CMAKE_VS_PLATFORM_NAME)
DebugBuildEnvShow(CMAKE_VS_PLATFORM_NAME_DEFAULT)
DebugBuildEnvShow(CMAKE_VS_PLATFORM_TOOLSET)
DebugBuildEnvShow(CMAKE_VS_PLATFORM_TOOLSET_CUDA)
DebugBuildEnvShow(CMAKE_VS_PLATFORM_TOOLSET_HOST_ARCHITECTURE)
DebugBuildEnvShow(CMAKE_VS_PLATFORM_TOOLSET_VERSION)
DebugBuildEnvShow(CMAKE_VS_WINDOWS_TARGET_PLATFORM_VERSION)
DebugBuildEnvShow(CMAKE_XCODE_GENERATE_SCHEME)
DebugBuildEnvShow(CMAKE_XCODE_PLATFORM_TOOLSET)
#DebugBuildEnvShow(<PROJECT-NAME>_BINARY_DIR)
#DebugBuildEnvShow(<PROJECT-NAME>_DESCRIPTION)
#DebugBuildEnvShow(<PROJECT-NAME>_HOMEPAGE_URL)
#DebugBuildEnvShow(<PROJECT-NAME>_SOURCE_DIR)
#DebugBuildEnvShow(<PROJECT-NAME>_VERSION)
#DebugBuildEnvShow(<PROJECT-NAME>_VERSION_MAJOR)
#DebugBuildEnvShow(<PROJECT-NAME>_VERSION_MINOR)
#DebugBuildEnvShow(<PROJECT-NAME>_VERSION_PATCH)
#DebugBuildEnvShow(<PROJECT-NAME>_VERSION_TWEAK)
DebugBuildEnvShow(PROJECT_BINARY_DIR)
DebugBuildEnvShow(PROJECT_DESCRIPTION)
DebugBuildEnvShow(PROJECT_HOMEPAGE_URL)
DebugBuildEnvShow(PROJECT_NAME)
DebugBuildEnvShow(PROJECT_SOURCE_DIR)
DebugBuildEnvShow(PROJECT_VERSION)
DebugBuildEnvShow(PROJECT_VERSION_MAJOR)
DebugBuildEnvShow(PROJECT_VERSION_MINOR)
DebugBuildEnvShow(PROJECT_VERSION_PATCH)
DebugBuildEnvShow(PROJECT_VERSION_TWEAK)
message(STATUS " ")
message(STATUS "Variables that Change Behavior}")
message(STATUS " ")
DebugBuildEnvShow(BUILD_SHARED_LIBS)
DebugBuildEnvShow(CMAKE_ABSOLUTE_DESTINATION_FILES)
DebugBuildEnvShow(CMAKE_APPBUNDLE_PATH)
DebugBuildEnvShow(CMAKE_AUTOMOC_RELAXED_MODE)
DebugBuildEnvShow(CMAKE_BACKWARDS_COMPATIBILITY)
DebugBuildEnvShow(CMAKE_BUILD_TYPE)
DebugBuildEnvShow(CMAKE_CODEBLOCKS_COMPILER_ID)
DebugBuildEnvShow(CMAKE_CODEBLOCKS_EXCLUDE_EXTERNAL_FILES)
DebugBuildEnvShow(CMAKE_CODELITE_USE_TARGETS)
DebugBuildEnvShow(CMAKE_COLOR_MAKEFILE)
DebugBuildEnvShow(CMAKE_CONFIGURATION_TYPES)
DebugBuildEnvShow(CMAKE_DEBUG_TARGET_PROPERTIES)
DebugBuildEnvShow(CMAKE_DEPENDS_IN_PROJECT_ONLY)
#DebugBuildEnvShow(CMAKE_DISABLE_FIND_PACKAGE_<PackageName>)
DebugBuildEnvShow(CMAKE_ECLIPSE_GENERATE_LINKED_RESOURCES)
DebugBuildEnvShow(CMAKE_ECLIPSE_GENERATE_SOURCE_PROJECT)
DebugBuildEnvShow(CMAKE_ECLIPSE_MAKE_ARGUMENTS)
DebugBuildEnvShow(CMAKE_ECLIPSE_VERSION)
DebugBuildEnvShow(CMAKE_ERROR_DEPRECATED)
DebugBuildEnvShow(CMAKE_ERROR_ON_ABSOLUTE_INSTALL_DESTINATION)
DebugBuildEnvShow(CMAKE_EXPORT_COMPILE_COMMANDS)
DebugBuildEnvShow(CMAKE_EXPORT_NO_PACKAGE_REGISTRY)
DebugBuildEnvShow(CMAKE_FIND_APPBUNDLE)
DebugBuildEnvShow(CMAKE_FIND_FRAMEWORK)
DebugBuildEnvShow(CMAKE_FIND_LIBRARY_CUSTOM_LIB_SUFFIX)
DebugBuildEnvShow(CMAKE_FIND_LIBRARY_PREFIXES)
DebugBuildEnvShow(CMAKE_FIND_LIBRARY_SUFFIXES)
DebugBuildEnvShow(CMAKE_FIND_NO_INSTALL_PREFIX)
DebugBuildEnvShow(CMAKE_FIND_PACKAGE_NO_PACKAGE_REGISTRY)
DebugBuildEnvShow(CMAKE_FIND_PACKAGE_NO_SYSTEM_PACKAGE_REGISTRY)
DebugBuildEnvShow(CMAKE_FIND_PACKAGE_RESOLVE_SYMLINKS)
DebugBuildEnvShow(CMAKE_FIND_PACKAGE_WARN_NO_MODULE)
DebugBuildEnvShow(CMAKE_FIND_ROOT_PATH)
DebugBuildEnvShow(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE)
DebugBuildEnvShow(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY)
DebugBuildEnvShow(CMAKE_FIND_ROOT_PATH_MODE_PACKAGE)
DebugBuildEnvShow(CMAKE_FIND_ROOT_PATH_MODE_PROGRAM)
DebugBuildEnvShow(CMAKE_FRAMEWORK_PATH)
DebugBuildEnvShow(CMAKE_IGNORE_PATH)
DebugBuildEnvShow(CMAKE_INCLUDE_DIRECTORIES_BEFORE)
DebugBuildEnvShow(CMAKE_INCLUDE_DIRECTORIES_PROJECT_BEFORE)
DebugBuildEnvShow(CMAKE_INCLUDE_PATH)
DebugBuildEnvShow(CMAKE_INSTALL_DEFAULT_COMPONENT_NAME)
DebugBuildEnvShow(CMAKE_INSTALL_DEFAULT_DIRECTORY_PERMISSIONS)
DebugBuildEnvShow(CMAKE_INSTALL_MESSAGE)
DebugBuildEnvShow(CMAKE_INSTALL_PREFIX)
DebugBuildEnvShow(CMAKE_INSTALL_PREFIX_INITIALIZED_TO_DEFAULT)
DebugBuildEnvShow(CMAKE_LIBRARY_PATH)
DebugBuildEnvShow(CMAKE_LINK_DIRECTORIES_BEFORE)
DebugBuildEnvShow(CMAKE_MFC_FLAG)
DebugBuildEnvShow(CMAKE_MAXIMUM_RECURSION_DEPTH)
DebugBuildEnvShow(CMAKE_MODULE_PATH)
#DebugBuildEnvShow(CMAKE_POLICY_DEFAULT_CMP<NNNN>)
#DebugBuildEnvShow(CMAKE_POLICY_WARNING_CMP<NNNN>)
DebugBuildEnvShow(CMAKE_PREFIX_PATH)
DebugBuildEnvShow(CMAKE_PROGRAM_PATH)
#DebugBuildEnvShow(CMAKE_PROJECT_<PROJECT-NAME>_INCLUDE)
DebugBuildEnvShow(CMAKE_SKIP_INSTALL_ALL_DEPENDENCY)
DebugBuildEnvShow(CMAKE_STAGING_PREFIX)
DebugBuildEnvShow(CMAKE_SUBLIME_TEXT_2_ENV_SETTINGS)
DebugBuildEnvShow(CMAKE_SUBLIME_TEXT_2_EXCLUDE_BUILD_TREE)
DebugBuildEnvShow(CMAKE_SUPPRESS_REGENERATION)
DebugBuildEnvShow(CMAKE_SYSROOT)
DebugBuildEnvShow(CMAKE_SYSROOT_COMPILE)
DebugBuildEnvShow(CMAKE_SYSROOT_LINK)
DebugBuildEnvShow(CMAKE_SYSTEM_APPBUNDLE_PATH)
DebugBuildEnvShow(CMAKE_SYSTEM_FRAMEWORK_PATH)
DebugBuildEnvShow(CMAKE_SYSTEM_IGNORE_PATH)
DebugBuildEnvShow(CMAKE_SYSTEM_INCLUDE_PATH)
DebugBuildEnvShow(CMAKE_SYSTEM_LIBRARY_PATH)
DebugBuildEnvShow(CMAKE_SYSTEM_PREFIX_PATH)
DebugBuildEnvShow(CMAKE_SYSTEM_PROGRAM_PATH)
DebugBuildEnvShow(CMAKE_USER_MAKE_RULES_OVERRIDE)
DebugBuildEnvShow(CMAKE_WARN_DEPRECATED)
DebugBuildEnvShow(CMAKE_WARN_ON_ABSOLUTE_INSTALL_DESTINATION)
DebugBuildEnvShow(CMAKE_XCODE_GENERATE_TOP_LEVEL_PROJECT_ONLY)
DebugBuildEnvShow(CMAKE_XCODE_SCHEME_ADDRESS_SANITIZER)
DebugBuildEnvShow(CMAKE_XCODE_SCHEME_ADDRESS_SANITIZER_USE_AFTER_RETURN)
DebugBuildEnvShow(CMAKE_XCODE_SCHEME_DISABLE_MAIN_THREAD_CHECKER)
DebugBuildEnvShow(CMAKE_XCODE_SCHEME_DYNAMIC_LIBRARY_LOADS)
DebugBuildEnvShow(CMAKE_XCODE_SCHEME_DYNAMIC_LINKER_API_USAGE)
DebugBuildEnvShow(CMAKE_XCODE_SCHEME_GUARD_MALLOC)
DebugBuildEnvShow(CMAKE_XCODE_SCHEME_MAIN_THREAD_CHECKER_STOP)
DebugBuildEnvShow(CMAKE_XCODE_SCHEME_MALLOC_GUARD_EDGES)
DebugBuildEnvShow(CMAKE_XCODE_SCHEME_MALLOC_SCRIBBLE)
DebugBuildEnvShow(CMAKE_XCODE_SCHEME_MALLOC_STACK)
DebugBuildEnvShow(CMAKE_XCODE_SCHEME_THREAD_SANITIZER)
DebugBuildEnvShow(CMAKE_XCODE_SCHEME_THREAD_SANITIZER_STOP)
DebugBuildEnvShow(CMAKE_XCODE_SCHEME_UNDEFINED_BEHAVIOUR_SANITIZER)
DebugBuildEnvShow(CMAKE_XCODE_SCHEME_UNDEFINED_BEHAVIOUR_SANITIZER_STOP)
DebugBuildEnvShow(CMAKE_XCODE_SCHEME_ZOMBIE_OBJECTS)
#DebugBuildEnvShow(<PackageName>_ROOT)
message(STATUS " ")
message(STATUS "Variables that Describe the System")
message(STATUS " ")
DebugBuildEnvShow(ANDROID)
DebugBuildEnvShow(APPLE)
DebugBuildEnvShow(BORLAND)
DebugBuildEnvShow(CMAKE_CL_64)
DebugBuildEnvShow(CMAKE_COMPILER_2005)
DebugBuildEnvShow(CMAKE_HOST_APPLE)
DebugBuildEnvShow(CMAKE_HOST_SOLARIS)
DebugBuildEnvShow(CMAKE_HOST_SYSTEM)
DebugBuildEnvShow(CMAKE_HOST_SYSTEM_NAME)
DebugBuildEnvShow(CMAKE_HOST_SYSTEM_PROCESSOR)
DebugBuildEnvShow(CMAKE_HOST_SYSTEM_VERSION)
DebugBuildEnvShow(CMAKE_HOST_UNIX)
DebugBuildEnvShow(CMAKE_HOST_WIN32)
DebugBuildEnvShow(CMAKE_LIBRARY_ARCHITECTURE)
DebugBuildEnvShow(CMAKE_LIBRARY_ARCHITECTURE_REGEX)
DebugBuildEnvShow(CMAKE_OBJECT_PATH_MAX)
DebugBuildEnvShow(CMAKE_SYSTEM)
DebugBuildEnvShow(CMAKE_SYSTEM_NAME)
DebugBuildEnvShow(CMAKE_SYSTEM_PROCESSOR)
DebugBuildEnvShow(CMAKE_SYSTEM_VERSION)
DebugBuildEnvShow(CYGWIN)
DebugBuildEnvShow(GHS-MULTI)
DebugBuildEnvShow(IOS)
DebugBuildEnvShow(MINGW)
DebugBuildEnvShow(MSVC)
DebugBuildEnvShow(MSVC10)
DebugBuildEnvShow(MSVC11)
DebugBuildEnvShow(MSVC12)
DebugBuildEnvShow(MSVC14)
DebugBuildEnvShow(MSVC60)
DebugBuildEnvShow(MSVC70)
DebugBuildEnvShow(MSVC71)
DebugBuildEnvShow(MSVC80)
DebugBuildEnvShow(MSVC90)
DebugBuildEnvShow(MSVC_IDE)
DebugBuildEnvShow(MSVC_TOOLSET_VERSION)
DebugBuildEnvShow(MSVC_VERSION)
DebugBuildEnvShow(MSYS)
DebugBuildEnvShow(UNIX)
DebugBuildEnvShow(WIN32)
DebugBuildEnvShow(WINCE)
DebugBuildEnvShow(WINDOWS_PHONE)
DebugBuildEnvShow(WINDOWS_STORE)
DebugBuildEnvShow(XCODE)
DebugBuildEnvShow(XCODE_VERSION)
message(STATUS " ")
message(STATUS "Variables that Control the Build")
message(STATUS " ")
DebugBuildEnvShow(CMAKE_ANDROID_ANT_ADDITIONAL_OPTIONS)
DebugBuildEnvShow(CMAKE_ANDROID_API)
DebugBuildEnvShow(CMAKE_ANDROID_API_MIN)
DebugBuildEnvShow(CMAKE_ANDROID_ARCH)
DebugBuildEnvShow(CMAKE_ANDROID_ARCH_ABI)
DebugBuildEnvShow(CMAKE_ANDROID_ARM_MODE)
DebugBuildEnvShow(CMAKE_ANDROID_ARM_NEON)
DebugBuildEnvShow(CMAKE_ANDROID_ASSETS_DIRECTORIES)
DebugBuildEnvShow(CMAKE_ANDROID_GUI)
DebugBuildEnvShow(CMAKE_ANDROID_JAR_DEPENDENCIES)
DebugBuildEnvShow(CMAKE_ANDROID_JAR_DIRECTORIES)
DebugBuildEnvShow(CMAKE_ANDROID_JAVA_SOURCE_DIR)
DebugBuildEnvShow(CMAKE_ANDROID_NATIVE_LIB_DEPENDENCIES)
DebugBuildEnvShow(CMAKE_ANDROID_NATIVE_LIB_DIRECTORIES)
DebugBuildEnvShow(CMAKE_ANDROID_NDK)
DebugBuildEnvShow(CMAKE_ANDROID_NDK_DEPRECATED_HEADERS)
DebugBuildEnvShow(CMAKE_ANDROID_NDK_TOOLCHAIN_HOST_TAG)
DebugBuildEnvShow(CMAKE_ANDROID_NDK_TOOLCHAIN_VERSION)
DebugBuildEnvShow(CMAKE_ANDROID_PROCESS_MAX)
DebugBuildEnvShow(CMAKE_ANDROID_PROGUARD)
DebugBuildEnvShow(CMAKE_ANDROID_PROGUARD_CONFIG_PATH)
DebugBuildEnvShow(CMAKE_ANDROID_SECURE_PROPS_PATH)
DebugBuildEnvShow(CMAKE_ANDROID_SKIP_ANT_STEP)
DebugBuildEnvShow(CMAKE_ANDROID_STANDALONE_TOOLCHAIN)
DebugBuildEnvShow(CMAKE_ANDROID_STL_TYPE)
DebugBuildEnvShow(CMAKE_ARCHIVE_OUTPUT_DIRECTORY)
#DebugBuildEnvShow(CMAKE_ARCHIVE_OUTPUT_DIRECTORY_<CONFIG>)
DebugBuildEnvShow(CMAKE_AUTOGEN_ORIGIN_DEPENDS)
DebugBuildEnvShow(CMAKE_AUTOGEN_PARALLEL)
DebugBuildEnvShow(CMAKE_AUTOGEN_VERBOSE)
DebugBuildEnvShow(CMAKE_AUTOMOC)
DebugBuildEnvShow(CMAKE_AUTOMOC_COMPILER_PREDEFINES)
DebugBuildEnvShow(CMAKE_AUTOMOC_DEPEND_FILTERS)
DebugBuildEnvShow(CMAKE_AUTOMOC_MACRO_NAMES)
DebugBuildEnvShow(CMAKE_AUTOMOC_MOC_OPTIONS)
DebugBuildEnvShow(CMAKE_AUTORCC)
DebugBuildEnvShow(CMAKE_AUTORCC_OPTIONS)
DebugBuildEnvShow(CMAKE_AUTOUIC)
DebugBuildEnvShow(CMAKE_AUTOUIC_OPTIONS)
DebugBuildEnvShow(CMAKE_AUTOUIC_SEARCH_PATHS)
DebugBuildEnvShow(CMAKE_BUILD_RPATH)
DebugBuildEnvShow(CMAKE_BUILD_RPATH_USE_ORIGIN)
DebugBuildEnvShow(CMAKE_BUILD_WITH_INSTALL_NAME_DIR)
DebugBuildEnvShow(CMAKE_BUILD_WITH_INSTALL_RPATH)
DebugBuildEnvShow(CMAKE_COMPILE_PDB_OUTPUT_DIRECTORY)
#DebugBuildEnvShow(CMAKE_COMPILE_PDB_OUTPUT_DIRECTORY_<CONFIG>)
#DebugBuildEnvShow(CMAKE_<CONFIG>_POSTFIX)
DebugBuildEnvShow(CMAKE_CUDA_SEPARABLE_COMPILATION)
DebugBuildEnvShow(CMAKE_DEBUG_POSTFIX)
DebugBuildEnvShow(CMAKE_ENABLE_EXPORTS)
DebugBuildEnvShow(CMAKE_EXE_LINKER_FLAGS)
#DebugBuildEnvShow(CMAKE_EXE_LINKER_FLAGS_<CONFIG>)
#DebugBuildEnvShow(CMAKE_EXE_LINKER_FLAGS_<CONFIG>_INIT)
DebugBuildEnvShow(CMAKE_EXE_LINKER_FLAGS_INIT)
DebugBuildEnvShow(CMAKE_FOLDER)
DebugBuildEnvShow(CMAKE_Fortran_FORMAT)
DebugBuildEnvShow(CMAKE_Fortran_MODULE_DIRECTORY)
DebugBuildEnvShow(CMAKE_GHS_NO_SOURCE_GROUP_FILE)
DebugBuildEnvShow(CMAKE_GLOBAL_AUTOGEN_TARGET)
DebugBuildEnvShow(CMAKE_GLOBAL_AUTOGEN_TARGET_NAME)
DebugBuildEnvShow(CMAKE_GLOBAL_AUTORCC_TARGET)
DebugBuildEnvShow(CMAKE_GLOBAL_AUTORCC_TARGET_NAME)
DebugBuildEnvShow(CMAKE_GNUtoMS)
DebugBuildEnvShow(CMAKE_INCLUDE_CURRENT_DIR)
DebugBuildEnvShow(CMAKE_INCLUDE_CURRENT_DIR_IN_INTERFACE)
DebugBuildEnvShow(CMAKE_INSTALL_NAME_DIR)
DebugBuildEnvShow(CMAKE_INSTALL_RPATH)
DebugBuildEnvShow(CMAKE_INSTALL_RPATH_USE_LINK_PATH)
DebugBuildEnvShow(CMAKE_INTERPROCEDURAL_OPTIMIZATION)
#DebugBuildEnvShow(CMAKE_INTERPROCEDURAL_OPTIMIZATION_<CONFIG>)
DebugBuildEnvShow(CMAKE_IOS_INSTALL_COMBINED)
#DebugBuildEnvShow(CMAKE_<LANG>_CLANG_TIDY)
#DebugBuildEnvShow(CMAKE_<LANG>_COMPILER_LAUNCHER)
#DebugBuildEnvShow(CMAKE_<LANG>_CPPCHECK)
#DebugBuildEnvShow(CMAKE_<LANG>_CPPLINT)
#DebugBuildEnvShow(CMAKE_<LANG>_INCLUDE_WHAT_YOU_USE)
#DebugBuildEnvShow(CMAKE_<LANG>_VISIBILITY_PRESET)
DebugBuildEnvShow(CMAKE_LIBRARY_OUTPUT_DIRECTORY)
#DebugBuildEnvShow(CMAKE_LIBRARY_OUTPUT_DIRECTORY_<CONFIG>)
DebugBuildEnvShow(CMAKE_LIBRARY_PATH_FLAG)
DebugBuildEnvShow(CMAKE_LINK_DEF_FILE_FLAG)
DebugBuildEnvShow(CMAKE_LINK_DEPENDS_NO_SHARED)
DebugBuildEnvShow(CMAKE_LINK_INTERFACE_LIBRARIES)
DebugBuildEnvShow(CMAKE_LINK_LIBRARY_FILE_FLAG)
DebugBuildEnvShow(CMAKE_LINK_LIBRARY_FLAG)
DebugBuildEnvShow(CMAKE_LINK_WHAT_YOU_USE)
DebugBuildEnvShow(CMAKE_MACOSX_BUNDLE)
DebugBuildEnvShow(CMAKE_MACOSX_RPATH)
#DebugBuildEnvShow(CMAKE_MAP_IMPORTED_CONFIG_<CONFIG>)
DebugBuildEnvShow(CMAKE_MODULE_LINKER_FLAGS)
#DebugBuildEnvShow(CMAKE_MODULE_LINKER_FLAGS_<CONFIG>)
#DebugBuildEnvShow(CMAKE_MODULE_LINKER_FLAGS_<CONFIG>_INIT)
DebugBuildEnvShow(CMAKE_MODULE_LINKER_FLAGS_INIT)
DebugBuildEnvShow(CMAKE_MSVCIDE_RUN_PATH)
DebugBuildEnvShow(CMAKE_NINJA_OUTPUT_PATH_PREFIX)
DebugBuildEnvShow(CMAKE_NO_BUILTIN_CHRPATH)
DebugBuildEnvShow(CMAKE_NO_SYSTEM_FROM_IMPORTED)
DebugBuildEnvShow(CMAKE_OSX_ARCHITECTURES)
DebugBuildEnvShow(CMAKE_OSX_DEPLOYMENT_TARGET)
DebugBuildEnvShow(CMAKE_OSX_SYSROOT)
DebugBuildEnvShow(CMAKE_PDB_OUTPUT_DIRECTORY)
#DebugBuildEnvShow(CMAKE_PDB_OUTPUT_DIRECTORY_<CONFIG>)
DebugBuildEnvShow(CMAKE_POSITION_INDEPENDENT_CODE)
DebugBuildEnvShow(CMAKE_RUNTIME_OUTPUT_DIRECTORY)
#DebugBuildEnvShow(CMAKE_RUNTIME_OUTPUT_DIRECTORY_<CONFIG>)
DebugBuildEnvShow(CMAKE_SHARED_LINKER_FLAGS)
#DebugBuildEnvShow(CMAKE_SHARED_LINKER_FLAGS_<CONFIG>)
#DebugBuildEnvShow(CMAKE_SHARED_LINKER_FLAGS_<CONFIG>_INIT)
DebugBuildEnvShow(CMAKE_SHARED_LINKER_FLAGS_INIT)
DebugBuildEnvShow(CMAKE_SKIP_BUILD_RPATH)
DebugBuildEnvShow(CMAKE_SKIP_INSTALL_RPATH)
DebugBuildEnvShow(CMAKE_STATIC_LINKER_FLAGS)
#DebugBuildEnvShow(CMAKE_STATIC_LINKER_FLAGS_<CONFIG>)
#DebugBuildEnvShow(CMAKE_STATIC_LINKER_FLAGS_<CONFIG>_INIT)
DebugBuildEnvShow(CMAKE_STATIC_LINKER_FLAGS_INIT)
DebugBuildEnvShow(CMAKE_TRY_COMPILE_CONFIGURATION)
DebugBuildEnvShow(CMAKE_TRY_COMPILE_PLATFORM_VARIABLES)
DebugBuildEnvShow(CMAKE_TRY_COMPILE_TARGET_TYPE)
DebugBuildEnvShow(CMAKE_USE_RELATIVE_PATHS)
DebugBuildEnvShow(CMAKE_VISIBILITY_INLINES_HIDDEN)
DebugBuildEnvShow(CMAKE_VS_GLOBALS)
DebugBuildEnvShow(CMAKE_VS_INCLUDE_INSTALL_TO_DEFAULT_BUILD)
DebugBuildEnvShow(CMAKE_VS_INCLUDE_PACKAGE_TO_DEFAULT_BUILD)
DebugBuildEnvShow(CMAKE_VS_SDK_EXCLUDE_DIRECTORIES)
DebugBuildEnvShow(CMAKE_VS_SDK_EXECUTABLE_DIRECTORIES)
DebugBuildEnvShow(CMAKE_VS_SDK_INCLUDE_DIRECTORIES)
DebugBuildEnvShow(CMAKE_VS_SDK_LIBRARY_DIRECTORIES)
DebugBuildEnvShow(CMAKE_VS_SDK_LIBRARY_WINRT_DIRECTORIES)
DebugBuildEnvShow(CMAKE_VS_SDK_REFERENCE_DIRECTORIES)
DebugBuildEnvShow(CMAKE_VS_SDK_SOURCE_DIRECTORIES)
DebugBuildEnvShow(CMAKE_VS_WINRT_BY_DEFAULT)
DebugBuildEnvShow(CMAKE_WIN32_EXECUTABLE)
DebugBuildEnvShow(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS)
#DebugBuildEnvShow(CMAKE_XCODE_ATTRIBUTE_<an-attribute>)
DebugBuildEnvShow(EXECUTABLE_OUTPUT_PATH)
DebugBuildEnvShow(LIBRARY_OUTPUT_PATH)
message(STATUS " ")
message(STATUS "Variables for Languages:")
message(STATUS " ")
DebugBuildEnvShow(CMAKE_COMPILER_IS_GNUCC)
DebugBuildEnvShow(CMAKE_COMPILER_IS_GNUCXX)
DebugBuildEnvShow(CMAKE_COMPILER_IS_GNUG77)
DebugBuildEnvShow(CMAKE_CUDA_HOST_COMPILER)
DebugBuildEnvShow(CMAKE_CUDA_EXTENSIONS)
DebugBuildEnvShow(CMAKE_CUDA_STANDARD)
DebugBuildEnvShow(CMAKE_CUDA_STANDARD_REQUIRED)
DebugBuildEnvShow(CMAKE_CUDA_TOOLKIT_INCLUDE_DIRECTORIES)
DebugBuildEnvShow(CMAKE_CXX_COMPILE_FEATURES)
DebugBuildEnvShow(CMAKE_CXX_EXTENSIONS)
DebugBuildEnvShow(CMAKE_CXX_STANDARD)
DebugBuildEnvShow(CMAKE_CXX_STANDARD_REQUIRED)
DebugBuildEnvShow(CMAKE_C_COMPILE_FEATURES)
DebugBuildEnvShow(CMAKE_C_EXTENSIONS)
DebugBuildEnvShow(CMAKE_C_STANDARD)
DebugBuildEnvShow(CMAKE_C_STANDARD_REQUIRED)
DebugBuildEnvShow(CMAKE_Fortran_MODDIR_DEFAULT)
DebugBuildEnvShow(CMAKE_Fortran_MODDIR_FLAG)
DebugBuildEnvShow(CMAKE_Fortran_MODOUT_FLAG)
#DebugBuildEnvShow(CMAKE_<LANG>_ANDROID_TOOLCHAIN_MACHINE)
#DebugBuildEnvShow(CMAKE_<LANG>_ANDROID_TOOLCHAIN_PREFIX)
#DebugBuildEnvShow(CMAKE_<LANG>_ANDROID_TOOLCHAIN_SUFFIX)
#DebugBuildEnvShow(CMAKE_<LANG>_ARCHIVE_APPEND)
#DebugBuildEnvShow(CMAKE_<LANG>_ARCHIVE_CREATE)
#DebugBuildEnvShow(CMAKE_<LANG>_ARCHIVE_FINISH)
#DebugBuildEnvShow(CMAKE_<LANG>_COMPILER)
#DebugBuildEnvShow(CMAKE_<LANG>_COMPILER_EXTERNAL_TOOLCHAIN)
#DebugBuildEnvShow(CMAKE_<LANG>_COMPILER_ID)
#DebugBuildEnvShow(CMAKE_<LANG>_COMPILER_LOADED)
#DebugBuildEnvShow(CMAKE_<LANG>_COMPILER_PREDEFINES_COMMAND)
#DebugBuildEnvShow(CMAKE_<LANG>_COMPILER_TARGET)
#DebugBuildEnvShow(CMAKE_<LANG>_COMPILER_VERSION)
#DebugBuildEnvShow(CMAKE_<LANG>_COMPILE_OBJECT)
#DebugBuildEnvShow(CMAKE_<LANG>_CREATE_SHARED_LIBRARY)
#DebugBuildEnvShow(CMAKE_<LANG>_CREATE_SHARED_MODULE)
#DebugBuildEnvShow(CMAKE_<LANG>_CREATE_STATIC_LIBRARY)
#DebugBuildEnvShow(CMAKE_<LANG>_FLAGS)
#DebugBuildEnvShow(CMAKE_<LANG>_FLAGS_<CONFIG>)
#DebugBuildEnvShow(CMAKE_<LANG>_FLAGS_<CONFIG>_INIT)
#DebugBuildEnvShow(CMAKE_<LANG>_FLAGS_DEBUG)
#DebugBuildEnvShow(CMAKE_<LANG>_FLAGS_DEBUG_INIT)
#DebugBuildEnvShow(CMAKE_<LANG>_FLAGS_INIT)
#DebugBuildEnvShow(CMAKE_<LANG>_FLAGS_MINSIZEREL)
#DebugBuildEnvShow(CMAKE_<LANG>_FLAGS_MINSIZEREL_INIT)
#DebugBuildEnvShow(CMAKE_<LANG>_FLAGS_RELEASE)
#DebugBuildEnvShow(CMAKE_<LANG>_FLAGS_RELEASE_INIT)
#DebugBuildEnvShow(CMAKE_<LANG>_FLAGS_RELWITHDEBINFO)
#DebugBuildEnvShow(CMAKE_<LANG>_FLAGS_RELWITHDEBINFO_INIT)
#DebugBuildEnvShow(CMAKE_<LANG>_IGNORE_EXTENSIONS)
#DebugBuildEnvShow(CMAKE_<LANG>_IMPLICIT_INCLUDE_DIRECTORIES)
#DebugBuildEnvShow(CMAKE_<LANG>_IMPLICIT_LINK_DIRECTORIES)
#DebugBuildEnvShow(CMAKE_<LANG>_IMPLICIT_LINK_FRAMEWORK_DIRECTORIES)
#DebugBuildEnvShow(CMAKE_<LANG>_IMPLICIT_LINK_LIBRARIES)
#DebugBuildEnvShow(CMAKE_<LANG>_LIBRARY_ARCHITECTURE)
#DebugBuildEnvShow(CMAKE_<LANG>_LINKER_PREFERENCE)
#DebugBuildEnvShow(CMAKE_<LANG>_LINKER_PREFERENCE_PROPAGATES)
#DebugBuildEnvShow(CMAKE_<LANG>_LINKER_WRAPPER_FLAG)
#DebugBuildEnvShow(CMAKE_<LANG>_LINKER_WRAPPER_FLAG_SEP)
#DebugBuildEnvShow(CMAKE_<LANG>_LINK_EXECUTABLE)
#DebugBuildEnvShow(CMAKE_<LANG>_OUTPUT_EXTENSION)
#DebugBuildEnvShow(CMAKE_<LANG>_SIMULATE_ID)
#DebugBuildEnvShow(CMAKE_<LANG>_SIMULATE_VERSION)
#DebugBuildEnvShow(CMAKE_<LANG>_SIZEOF_DATA_PTR)
#DebugBuildEnvShow(CMAKE_<LANG>_SOURCE_FILE_EXTENSIONS)
#DebugBuildEnvShow(CMAKE_<LANG>_STANDARD_INCLUDE_DIRECTORIES)
#DebugBuildEnvShow(CMAKE_<LANG>_STANDARD_LIBRARIES)
DebugBuildEnvShow(CMAKE_Swift_LANGUAGE_VERSION)
#DebugBuildEnvShow(CMAKE_USER_MAKE_RULES_OVERRIDE_<LANG>)
message(STATUS " ")
message(STATUS "Variables for CTest:")
message(STATUS " ")
DebugBuildEnvShow(CTEST_BINARY_DIRECTORY)
DebugBuildEnvShow(CTEST_BUILD_COMMAND)
DebugBuildEnvShow(CTEST_BUILD_NAME)
DebugBuildEnvShow(CTEST_BZR_COMMAND)
DebugBuildEnvShow(CTEST_BZR_UPDATE_OPTIONS)
DebugBuildEnvShow(CTEST_CHANGE_ID)
DebugBuildEnvShow(CTEST_CHECKOUT_COMMAND)
DebugBuildEnvShow(CTEST_CONFIGURATION_TYPE)
DebugBuildEnvShow(CTEST_CONFIGURE_COMMAND)
DebugBuildEnvShow(CTEST_COVERAGE_COMMAND)
DebugBuildEnvShow(CTEST_COVERAGE_EXTRA_FLAGS)
DebugBuildEnvShow(CTEST_CURL_OPTIONS)
DebugBuildEnvShow(CTEST_CUSTOM_COVERAGE_EXCLUDE)
DebugBuildEnvShow(CTEST_CUSTOM_ERROR_EXCEPTION)
DebugBuildEnvShow(CTEST_CUSTOM_ERROR_MATCH)
DebugBuildEnvShow(CTEST_CUSTOM_ERROR_POST_CONTEXT)
DebugBuildEnvShow(CTEST_CUSTOM_ERROR_PRE_CONTEXT)
DebugBuildEnvShow(CTEST_CUSTOM_MAXIMUM_FAILED_TEST_OUTPUT_SIZE)
DebugBuildEnvShow(CTEST_CUSTOM_MAXIMUM_NUMBER_OF_ERRORS)
DebugBuildEnvShow(CTEST_CUSTOM_MAXIMUM_NUMBER_OF_WARNINGS)
DebugBuildEnvShow(CTEST_CUSTOM_MAXIMUM_PASSED_TEST_OUTPUT_SIZE)
DebugBuildEnvShow(CTEST_CUSTOM_MEMCHECK_IGNORE)
DebugBuildEnvShow(CTEST_CUSTOM_POST_MEMCHECK)
DebugBuildEnvShow(CTEST_CUSTOM_POST_TEST)
DebugBuildEnvShow(CTEST_CUSTOM_PRE_MEMCHECK)
DebugBuildEnvShow(CTEST_CUSTOM_PRE_TEST)
DebugBuildEnvShow(CTEST_CUSTOM_TESTS_IGNORE)
DebugBuildEnvShow(CTEST_CUSTOM_WARNING_EXCEPTION)
DebugBuildEnvShow(CTEST_CUSTOM_WARNING_MATCH)
DebugBuildEnvShow(CTEST_CVS_CHECKOUT)
DebugBuildEnvShow(CTEST_CVS_COMMAND)
DebugBuildEnvShow(CTEST_CVS_UPDATE_OPTIONS)
DebugBuildEnvShow(CTEST_DROP_LOCATION)
DebugBuildEnvShow(CTEST_DROP_METHOD)
DebugBuildEnvShow(CTEST_DROP_SITE)
DebugBuildEnvShow(CTEST_DROP_SITE_CDASH)
DebugBuildEnvShow(CTEST_DROP_SITE_PASSWORD)
DebugBuildEnvShow(CTEST_DROP_SITE_USER)
DebugBuildEnvShow(CTEST_EXTRA_COVERAGE_GLOB)
DebugBuildEnvShow(CTEST_GIT_COMMAND)
DebugBuildEnvShow(CTEST_GIT_INIT_SUBMODULES)
DebugBuildEnvShow(CTEST_GIT_UPDATE_CUSTOM)
DebugBuildEnvShow(CTEST_GIT_UPDATE_OPTIONS)
DebugBuildEnvShow(CTEST_HG_COMMAND)
DebugBuildEnvShow(CTEST_HG_UPDATE_OPTIONS)
DebugBuildEnvShow(CTEST_LABELS_FOR_SUBPROJECTS)
DebugBuildEnvShow(CTEST_MEMORYCHECK_COMMAND)
DebugBuildEnvShow(CTEST_MEMORYCHECK_COMMAND_OPTIONS)
DebugBuildEnvShow(CTEST_MEMORYCHECK_SANITIZER_OPTIONS)
DebugBuildEnvShow(CTEST_MEMORYCHECK_SUPPRESSIONS_FILE)
DebugBuildEnvShow(CTEST_MEMORYCHECK_TYPE)
DebugBuildEnvShow(CTEST_NIGHTLY_START_TIME)
DebugBuildEnvShow(CTEST_P4_CLIENT)
DebugBuildEnvShow(CTEST_P4_COMMAND)
DebugBuildEnvShow(CTEST_P4_OPTIONS)
DebugBuildEnvShow(CTEST_P4_UPDATE_OPTIONS)
DebugBuildEnvShow(CTEST_RUN_CURRENT_SCRIPT)
DebugBuildEnvShow(CTEST_SCP_COMMAND)
DebugBuildEnvShow(CTEST_SITE)
DebugBuildEnvShow(CTEST_SUBMIT_URL)
DebugBuildEnvShow(CTEST_SOURCE_DIRECTORY)
DebugBuildEnvShow(CTEST_SVN_COMMAND)
DebugBuildEnvShow(CTEST_SVN_OPTIONS)
DebugBuildEnvShow(CTEST_SVN_UPDATE_OPTIONS)
DebugBuildEnvShow(CTEST_TEST_LOAD)
DebugBuildEnvShow(CTEST_TEST_TIMEOUT)
DebugBuildEnvShow(CTEST_TRIGGER_SITE)
DebugBuildEnvShow(CTEST_UPDATE_COMMAND)
DebugBuildEnvShow(CTEST_UPDATE_OPTIONS)
DebugBuildEnvShow(CTEST_UPDATE_VERSION_ONLY)
DebugBuildEnvShow(CTEST_USE_LAUNCHERS)
message(STATUS " ")
message(STATUS "Variables for CPack:")
message(STATUS " ")
DebugBuildEnvShow(CPACK_ABSOLUTE_DESTINATION_FILES)
DebugBuildEnvShow(CPACK_COMPONENT_INCLUDE_TOPLEVEL_DIRECTORY)
DebugBuildEnvShow(CPACK_ERROR_ON_ABSOLUTE_INSTALL_DESTINATION)
DebugBuildEnvShow(CPACK_INCLUDE_TOPLEVEL_DIRECTORY)
DebugBuildEnvShow(CPACK_INSTALL_DEFAULT_DIRECTORY_PERMISSIONS)
DebugBuildEnvShow(CPACK_INSTALL_SCRIPT)
DebugBuildEnvShow(CPACK_PACKAGING_INSTALL_PREFIX)
DebugBuildEnvShow(CPACK_SET_DESTDIR)
DebugBuildEnvShow(CPACK_WARN_ON_ABSOLUTE_INSTALL_DESTINATION)
message(STATUS " ")
message(STATUS "Variable Expansion Operators:")
message(STATUS " ")
DebugBuildEnvShow(CACHE)
DebugBuildEnvShow(ENV)
message(STATUS " ")
message(STATUS "========================================================================================================")