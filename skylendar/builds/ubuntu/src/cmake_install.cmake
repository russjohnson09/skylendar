# Install script for directory: /skylendar/skylendar-4.1nn/src

# Set the install prefix
if(NOT DEFINED CMAKE_INSTALL_PREFIX)
  set(CMAKE_INSTALL_PREFIX "/usr/local")
endif()
string(REGEX REPLACE "/$" "" CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")

# Set the install configuration name.
if(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)
  if(BUILD_TYPE)
    string(REGEX REPLACE "^[^A-Za-z0-9_]+" ""
           CMAKE_INSTALL_CONFIG_NAME "${BUILD_TYPE}")
  else()
    set(CMAKE_INSTALL_CONFIG_NAME "")
  endif()
  message(STATUS "Install configuration: \"${CMAKE_INSTALL_CONFIG_NAME}\"")
endif()

# Set the component getting installed.
if(NOT CMAKE_INSTALL_COMPONENT)
  if(COMPONENT)
    message(STATUS "Install component: \"${COMPONENT}\"")
    set(CMAKE_INSTALL_COMPONENT "${COMPONENT}")
  else()
    set(CMAKE_INSTALL_COMPONENT)
  endif()
endif()

# Install shared libraries without execute permission?
if(NOT DEFINED CMAKE_INSTALL_SO_NO_EXE)
  set(CMAKE_INSTALL_SO_NO_EXE "1")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  foreach(file
      "$ENV{DESTDIR}/usr/local/lib64/libskyldr.so.4.1nn"
      "$ENV{DESTDIR}/usr/local/lib64/libskyldr.so.4"
      "$ENV{DESTDIR}/usr/local/lib64/libskyldr.so"
      )
    if(EXISTS "${file}" AND
       NOT IS_SYMLINK "${file}")
      file(RPATH_CHECK
           FILE "${file}"
           RPATH "")
    endif()
  endforeach()
  list(APPEND CMAKE_ABSOLUTE_DESTINATION_FILES
   "/usr/local/lib64/libskyldr.so.4.1nn;/usr/local/lib64/libskyldr.so.4;/usr/local/lib64/libskyldr.so")
  if(CMAKE_WARN_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(WARNING "ABSOLUTE path INSTALL DESTINATION : ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
  if(CMAKE_ERROR_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(FATAL_ERROR "ABSOLUTE path INSTALL DESTINATION forbidden (by caller): ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
file(INSTALL DESTINATION "/usr/local/lib64" TYPE SHARED_LIBRARY FILES
    "/skylendar/builds/ubuntu/src/libskyldr.so.4.1nn"
    "/skylendar/builds/ubuntu/src/libskyldr.so.4"
    "/skylendar/builds/ubuntu/src/libskyldr.so"
    )
  foreach(file
      "$ENV{DESTDIR}/usr/local/lib64/libskyldr.so.4.1nn"
      "$ENV{DESTDIR}/usr/local/lib64/libskyldr.so.4"
      "$ENV{DESTDIR}/usr/local/lib64/libskyldr.so"
      )
    if(EXISTS "${file}" AND
       NOT IS_SYMLINK "${file}")
      if(CMAKE_INSTALL_DO_STRIP)
        execute_process(COMMAND "/usr/bin/strip" "${file}")
      endif()
    endif()
  endforeach()
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  if(EXISTS "$ENV{DESTDIR}/usr/local/bin/skylendar" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}/usr/local/bin/skylendar")
    file(RPATH_CHECK
         FILE "$ENV{DESTDIR}/usr/local/bin/skylendar"
         RPATH "")
  endif()
  list(APPEND CMAKE_ABSOLUTE_DESTINATION_FILES
   "/usr/local/bin/skylendar")
  if(CMAKE_WARN_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(WARNING "ABSOLUTE path INSTALL DESTINATION : ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
  if(CMAKE_ERROR_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(FATAL_ERROR "ABSOLUTE path INSTALL DESTINATION forbidden (by caller): ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
file(INSTALL DESTINATION "/usr/local/bin" TYPE EXECUTABLE FILES "/skylendar/builds/ubuntu/src/skylendar")
  if(EXISTS "$ENV{DESTDIR}/usr/local/bin/skylendar" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}/usr/local/bin/skylendar")
    file(RPATH_CHANGE
         FILE "$ENV{DESTDIR}/usr/local/bin/skylendar"
         OLD_RPATH "/skylendar/skylendar-4.1nn/lib:/skylendar/builds/ubuntu/src:"
         NEW_RPATH "")
    if(CMAKE_INSTALL_DO_STRIP)
      execute_process(COMMAND "/usr/bin/strip" "$ENV{DESTDIR}/usr/local/bin/skylendar")
    endif()
  endif()
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  if(EXISTS "$ENV{DESTDIR}/usr/local/bin/skyservice" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}/usr/local/bin/skyservice")
    file(RPATH_CHECK
         FILE "$ENV{DESTDIR}/usr/local/bin/skyservice"
         RPATH "")
  endif()
  list(APPEND CMAKE_ABSOLUTE_DESTINATION_FILES
   "/usr/local/bin/skyservice")
  if(CMAKE_WARN_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(WARNING "ABSOLUTE path INSTALL DESTINATION : ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
  if(CMAKE_ERROR_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(FATAL_ERROR "ABSOLUTE path INSTALL DESTINATION forbidden (by caller): ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
file(INSTALL DESTINATION "/usr/local/bin" TYPE EXECUTABLE FILES "/skylendar/builds/ubuntu/src/skyservice")
  if(EXISTS "$ENV{DESTDIR}/usr/local/bin/skyservice" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}/usr/local/bin/skyservice")
    file(RPATH_CHANGE
         FILE "$ENV{DESTDIR}/usr/local/bin/skyservice"
         OLD_RPATH "/skylendar/skylendar-4.1nn/lib:/skylendar/builds/ubuntu/src:"
         NEW_RPATH "")
    if(CMAKE_INSTALL_DO_STRIP)
      execute_process(COMMAND "/usr/bin/strip" "$ENV{DESTDIR}/usr/local/bin/skyservice")
    endif()
  endif()
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  if(EXISTS "$ENV{DESTDIR}/usr/local/bin/skydmin" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}/usr/local/bin/skydmin")
    file(RPATH_CHECK
         FILE "$ENV{DESTDIR}/usr/local/bin/skydmin"
         RPATH "")
  endif()
  list(APPEND CMAKE_ABSOLUTE_DESTINATION_FILES
   "/usr/local/bin/skydmin")
  if(CMAKE_WARN_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(WARNING "ABSOLUTE path INSTALL DESTINATION : ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
  if(CMAKE_ERROR_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(FATAL_ERROR "ABSOLUTE path INSTALL DESTINATION forbidden (by caller): ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
file(INSTALL DESTINATION "/usr/local/bin" TYPE EXECUTABLE FILES "/skylendar/builds/ubuntu/src/skydmin")
  if(EXISTS "$ENV{DESTDIR}/usr/local/bin/skydmin" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}/usr/local/bin/skydmin")
    file(RPATH_CHANGE
         FILE "$ENV{DESTDIR}/usr/local/bin/skydmin"
         OLD_RPATH "/skylendar/skylendar-4.1nn/lib:"
         NEW_RPATH "")
    if(CMAKE_INSTALL_DO_STRIP)
      execute_process(COMMAND "/usr/bin/strip" "$ENV{DESTDIR}/usr/local/bin/skydmin")
    endif()
  endif()
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  list(APPEND CMAKE_ABSOLUTE_DESTINATION_FILES
   "/usr/local/share/applications/skylendar.desktop")
  if(CMAKE_WARN_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(WARNING "ABSOLUTE path INSTALL DESTINATION : ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
  if(CMAKE_ERROR_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(FATAL_ERROR "ABSOLUTE path INSTALL DESTINATION forbidden (by caller): ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
file(INSTALL DESTINATION "/usr/local/share/applications" TYPE FILE FILES "/skylendar/skylendar-4.1nn/src/skylendar.desktop")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  list(APPEND CMAKE_ABSOLUTE_DESTINATION_FILES
   "/usr/local/share/applications/skydmin.desktop")
  if(CMAKE_WARN_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(WARNING "ABSOLUTE path INSTALL DESTINATION : ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
  if(CMAKE_ERROR_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(FATAL_ERROR "ABSOLUTE path INSTALL DESTINATION forbidden (by caller): ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
file(INSTALL DESTINATION "/usr/local/share/applications" TYPE FILE FILES "/skylendar/skylendar-4.1nn/src/skydmin.desktop")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  list(APPEND CMAKE_ABSOLUTE_DESTINATION_FILES
   "/usr/local/share/icons/skylendar.png")
  if(CMAKE_WARN_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(WARNING "ABSOLUTE path INSTALL DESTINATION : ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
  if(CMAKE_ERROR_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(FATAL_ERROR "ABSOLUTE path INSTALL DESTINATION forbidden (by caller): ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
file(INSTALL DESTINATION "/usr/local/share/icons" TYPE FILE FILES "/skylendar/skylendar-4.1nn/src/skylendar.png")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  list(APPEND CMAKE_ABSOLUTE_DESTINATION_FILES
   "/usr/local/share/icons/skydmin.png")
  if(CMAKE_WARN_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(WARNING "ABSOLUTE path INSTALL DESTINATION : ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
  if(CMAKE_ERROR_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(FATAL_ERROR "ABSOLUTE path INSTALL DESTINATION forbidden (by caller): ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
file(INSTALL DESTINATION "/usr/local/share/icons" TYPE FILE FILES "/skylendar/skylendar-4.1nn/src/skydmin.png")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  list(APPEND CMAKE_ABSOLUTE_DESTINATION_FILES
   "/usr/local/share/icons/skif.png")
  if(CMAKE_WARN_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(WARNING "ABSOLUTE path INSTALL DESTINATION : ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
  if(CMAKE_ERROR_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(FATAL_ERROR "ABSOLUTE path INSTALL DESTINATION forbidden (by caller): ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
file(INSTALL DESTINATION "/usr/local/share/icons" TYPE FILE FILES "/skylendar/skylendar-4.1nn/src/skif.png")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  list(APPEND CMAKE_ABSOLUTE_DESTINATION_FILES
   "/usr/local/share/mime/packages/skif.desktop")
  if(CMAKE_WARN_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(WARNING "ABSOLUTE path INSTALL DESTINATION : ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
  if(CMAKE_ERROR_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(FATAL_ERROR "ABSOLUTE path INSTALL DESTINATION forbidden (by caller): ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
file(INSTALL DESTINATION "/usr/local/share/mime/packages" TYPE FILE FILES "/skylendar/skylendar-4.1nn/src/skif.desktop")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  list(APPEND CMAKE_ABSOLUTE_DESTINATION_FILES
   "/usr/share/fonts/truetype/skylendar.ttf")
  if(CMAKE_WARN_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(WARNING "ABSOLUTE path INSTALL DESTINATION : ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
  if(CMAKE_ERROR_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(FATAL_ERROR "ABSOLUTE path INSTALL DESTINATION forbidden (by caller): ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
file(INSTALL DESTINATION "/usr/share/fonts/truetype" TYPE FILE FILES "/skylendar/skylendar-4.1nn/src/skylendar.ttf")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  list(APPEND CMAKE_ABSOLUTE_DESTINATION_FILES
   "/usr/local/share/skylendar/CIA_WDB2.jpd.gz;/usr/local/share/skylendar/skif.dtd;/usr/local/share/skylendar/skylendar.pfb;/usr/local/share/skylendar/sefstars.txt;/usr/local/share/skylendar/sedeltat.txt.inactive;/usr/local/share/skylendar/seas_18.se1;/usr/local/share/skylendar/semo_18.se1;/usr/local/share/skylendar/seorbel.txt;/usr/local/share/skylendar/sepl_18.se1;/usr/local/share/skylendar/seleapsec.txt;/usr/local/share/skylendar/README;/usr/local/share/skylendar/COPYING;/usr/local/share/skylendar/HISTORY.txt")
  if(CMAKE_WARN_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(WARNING "ABSOLUTE path INSTALL DESTINATION : ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
  if(CMAKE_ERROR_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(FATAL_ERROR "ABSOLUTE path INSTALL DESTINATION forbidden (by caller): ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
file(INSTALL DESTINATION "/usr/local/share/skylendar" TYPE FILE FILES
    "/skylendar/skylendar-4.1nn/src/CIA_WDB2.jpd.gz"
    "/skylendar/skylendar-4.1nn/src/skif.dtd"
    "/skylendar/skylendar-4.1nn/src/skylendar.pfb"
    "/skylendar/skylendar-4.1nn/src/sefstars.txt"
    "/skylendar/skylendar-4.1nn/src/sedeltat.txt.inactive"
    "/skylendar/skylendar-4.1nn/src/seas_18.se1"
    "/skylendar/skylendar-4.1nn/src/semo_18.se1"
    "/skylendar/skylendar-4.1nn/src/seorbel.txt"
    "/skylendar/skylendar-4.1nn/src/sepl_18.se1"
    "/skylendar/skylendar-4.1nn/src/seleapsec.txt"
    "/skylendar/skylendar-4.1nn/src/../README"
    "/skylendar/skylendar-4.1nn/src/../COPYING"
    "/skylendar/skylendar-4.1nn/src/../HISTORY.txt"
    )
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  list(APPEND CMAKE_ABSOLUTE_DESTINATION_FILES
   "/usr/local/share/skylendar/installskydb.sql;/usr/local/share/skylendar/skif.pm;/usr/local/share/skylendar/Country.txt;/usr/local/share/skylendar/D1901.txt;/usr/local/share/skylendar/Degrees.txt;/usr/local/share/skylendar/ExtraObjs.txt;/usr/local/share/skylendar/Place.txt;/usr/local/share/skylendar/Tarots.txt;/usr/local/share/skylendar/Parts.txt;/usr/local/share/skylendar/Interpret.txt;/usr/local/share/skylendar/Intertarots.txt;/usr/local/share/skylendar/ConsNames.txt;/usr/local/share/skylendar/Boundaries.txt;/usr/local/share/skylendar/Stars.txt")
  if(CMAKE_WARN_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(WARNING "ABSOLUTE path INSTALL DESTINATION : ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
  if(CMAKE_ERROR_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(FATAL_ERROR "ABSOLUTE path INSTALL DESTINATION forbidden (by caller): ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
file(INSTALL DESTINATION "/usr/local/share/skylendar" TYPE FILE FILES
    "/skylendar/skylendar-4.1nn/src/installskydb.sql"
    "/skylendar/skylendar-4.1nn/src/skif.pm"
    "/skylendar/skylendar-4.1nn/src/Country.txt"
    "/skylendar/skylendar-4.1nn/src/D1901.txt"
    "/skylendar/skylendar-4.1nn/src/Degrees.txt"
    "/skylendar/skylendar-4.1nn/src/ExtraObjs.txt"
    "/skylendar/skylendar-4.1nn/src/Place.txt"
    "/skylendar/skylendar-4.1nn/src/Tarots.txt"
    "/skylendar/skylendar-4.1nn/src/Parts.txt"
    "/skylendar/skylendar-4.1nn/src/Interpret.txt"
    "/skylendar/skylendar-4.1nn/src/Intertarots.txt"
    "/skylendar/skylendar-4.1nn/src/ConsNames.txt"
    "/skylendar/skylendar-4.1nn/src/Boundaries.txt"
    "/skylendar/skylendar-4.1nn/src/Stars.txt"
    )
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  list(APPEND CMAKE_ABSOLUTE_DESTINATION_FILES
   "/usr/local/share/skylendar/skylendar_fr_FR.qm;/usr/local/share/skylendar/skydmin_fr_FR.qm")
  if(CMAKE_WARN_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(WARNING "ABSOLUTE path INSTALL DESTINATION : ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
  if(CMAKE_ERROR_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(FATAL_ERROR "ABSOLUTE path INSTALL DESTINATION forbidden (by caller): ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
file(INSTALL DESTINATION "/usr/local/share/skylendar" TYPE FILE FILES
    "/skylendar/builds/ubuntu/src/skylendar_fr_FR.qm"
    "/skylendar/builds/ubuntu/src/skydmin_fr_FR.qm"
    )
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for each subdirectory.
  include("/skylendar/builds/ubuntu/src/swe/cmake_install.cmake")
  include("/skylendar/builds/ubuntu/src/pics/cmake_install.cmake")

endif()

