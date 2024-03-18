cmake_minimum_required(VERSION 3.16.0)

project(aseprite_thumbnails)

include(FeatureSummary)
include(WriteBasicConfigVersionFile)

# Qt version
set(QT_MIN_VERSION 5.15.2)
set(KF_DEP_VERSION 5.92.0)

find_package(ECM ${KF_DEP_VERSION} REQUIRED NO_MODULE)
set(CMAKE_MODULE_PATH ${ECM_MODULE_PATH} ${ECM_KDE_MODULE_DIR})

# Select the Qt version we want to use
# Qt6 is the prefered one, Qt5 the fallback
find_package(Qt6 COMPONENTS Core QUIET)

if (NOT DEFINED QT_MAJOR_VERSION)
    if (TARGET Qt6::Core)
        set(QT_MAJOR_VERSION 6)
    else()
        find_package(Qt5 COMPONENTS Core QUIET)
        if (TARGET Qt5::Core)
          set(QT_MAJOR_VERSION 5)
        endif()
    endif()
    if(NOT QT_MAJOR_VERSION)
        option(BUILD_WITH_QT6 "Build against Qt 6" ON)
        if (BUILD_WITH_QT6)
            set(QT_MAJOR_VERSION 6)
        else()
            set(QT_MAJOR_VERSION 5)
        endif()
    endif()
endif()

# include ECM Modules
include(KDECompilerSettings NO_POLICY_SCOPE)
include(KDEInstallDirs)
include(KDECMakeSettings)

# KDE Frameworks
if (NOT DEFINED KF_MAJOR)
    set(KF_MAJOR ${QT_MAJOR_VERSION})
endif()

if (KF_MAJOR STREQUAL "6")
    set(KF_DEP_VERSION 5.240.0)
endif()

find_package(KF${KF_MAJOR} ${KF_DEP_VERSION} REQUIRED COMPONENTS KIO)

set(KDE_INSTALL_USE_QT_SYS_PATHS)

kcoreaddons_add_plugin(aseprite_thumbnails INSTALL_NAMESPACE "kf${QT_MAJOR_VERSION}/thumbcreator")

target_sources(aseprite_thumbnails PRIVATE aseprite_thumbnails.cpp)

target_link_libraries(aseprite_thumbnails
    Qt${QT_MAJOR_VERSION}::Core
    Qt${QT_MAJOR_VERSION}::Gui
    KF${KF_MAJOR}::KIOCore
    KF${KF_MAJOR}::KIOGui
)
