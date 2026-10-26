cmake_minimum_required(VERSION 3.25)

# This tells cmake we have goodies in the /cmake folder
list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")
include (PamplejuceVersion)

# Modern concise way to add dependencies to your project
include (CPM)

# Configures universal binaries and decides which version of macOS to support
include(PamplejuceMacOS)

# Couple tweaks that IMO should be JUCE defaults
include(JUCEDefaults)

# Internal name of the project
set(PROJECT_NAME "VoxAnchor")

# What DAWs will display
set(PRODUCT_NAME "VoxAnchor")

# Used for the MacOS bundle name and Installers
set(COMPANY_NAME "VoxAnchor")

# Used for the MacOS bundle identifier (and signing)
set(BUNDLE_ID "com.voxanchor.plugin")

# Set the plugin formats you want built
set(FORMATS Standalone AU VST3 AUv3)

# Force JUCE to work with sccache
set(CMAKE_POLICY_DEFAULT_CMP0141        NEW      CACHE STRING "" FORCE)
set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT Embedded CACHE STRING "" FORCE)

project(${PROJECT_NAME} VERSION ${CURRENT_VERSION})

# Log build environment info
include(PamplejuceLog)

# Defines the pamplejuce_* functions we call below
include(PamplejuceFunctions)

# JUCE is setup as a submodule in the /JUCE folder
add_subdirectory(JUCE)

# Add CLAP format
add_subdirectory(modules/clap-juce-extensions EXCLUDE_FROM_ALL)

# This adds the melatonin inspector module
add_subdirectory (modules/melatonin_inspector)

juce_add_plugin("${PROJECT_NAME}"
    ICON_BIG "${CMAKE_CURRENT_SOURCE_DIR}/packaging/icon.png"
    COMPANY_NAME "${COMPANY_NAME}"
    BUNDLE_ID "${BUNDLE_ID}"
    COPY_PLUGIN_AFTER_BUILD TRUE
    PLUGIN_MANUFACTURER_CODE VoxA
    PLUGIN_CODE VxAn
    FORMATS "${FORMATS}"
    PRODUCT_NAME "${PRODUCT_NAME}")
    
juce_generate_juce_header("${PROJECT_NAME}")

add_library(SharedCode INTERFACE)

clap_juce_extensions_plugin(TARGET "${PROJECT_NAME}"
    CLAP_ID "${BUNDLE_ID}"
    CLAP_FEATURES audio-effect)

pamplejuce_shared_code_defaults()

# --- THIS IS THE FIX ---
# We removed the auto-search and explicitly told it to ONLY build your 4 files
target_sources(SharedCode INTERFACE
    Source/PluginEditor.cpp
    Source/PluginEditor.h
    Source/PluginProcessor.cpp
    Source/PluginProcessor.h
)

pamplejuce_add_assets()
pamplejuce_xcode_prettify()

target_compile_definitions(SharedCode
    INTERFACE
    JUCE_WEB_BROWSER=0
    JUCE_USE_CURL=0
    JUCE_VST3_CAN_REPLACE_VST2=0
    CMAKE_BUILD_TYPE="${CMAKE_BUILD_TYPE}"
    VERSION="${CURRENT_VERSION}"
    PRODUCT_NAME_WITHOUT_VERSION="VoxAnchor"
)

target_link_libraries(SharedCode
    INTERFACE
    Assets
    melatonin_inspector
    juce_audio_utils
    juce_audio_processors
    juce_dsp
    juce_gui_basics
    juce_gui_extra
    juce::juce_recommended_config_flags
    juce::juce_recommended_lto_flags
    juce::juce_recommended_warning_flags)

target_link_libraries("${PROJECT_NAME}" PRIVATE SharedCode)

include(PamplejuceIPP)
pamplejuce_add_tests()
pamplejuce_add_benchmarks()
include(GitHubENV)
