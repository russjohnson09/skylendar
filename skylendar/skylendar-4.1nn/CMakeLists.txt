#
# Skylendar 4.1nn
#
# Copyright Christophe Gros skylendar@yahoo.com 2000-2018
#
# This software has been released under the terms of the GPL
# license.
#
project(skylendar)
set(SKYSITE "http://")
cmake_minimum_required(VERSION 2.8.12)
configure_file (config.h.cmake ${CMAKE_CURRENT_BINARY_DIR}/config.h )
#option(SHARED_CODE "Set to TRUE if shared database")
option(NATIVE "Set to TRUE for PostgreSQL native driver")
if(NATIVE)
 set(PostgreSQL_ADDITIONAL_VERSIONS "9.3" "9.4" "9.5" "9.6" "10.0" "10.5" "11.1")
 find_package(PostgreSQL REQUIRED)
 set(PostgreSQL_TYPE_INCLUDE_DIR "${PostgreSQL_INCLUDE_DIRS}/postgresql/server")
endif(NATIVE)
#include(FindGettext)

set (QT_MIN_VERSION "5.4.0")
find_package(Qt5 ${QT_MIN_VERSION} CONFIG REQUIRED Core Widgets Network Sql PrintSupport DBus Xml Svg LinguistTools)

#set(CMAKE_AUTOMOC ON)

add_definitions (-DHAVE_CONFIG_H=1)
add_subdirectory(src)
