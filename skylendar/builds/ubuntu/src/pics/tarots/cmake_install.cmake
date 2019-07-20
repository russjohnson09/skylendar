# Install script for directory: /skylendar/skylendar-4.1nn/src/pics/tarots

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
  list(APPEND CMAKE_ABSOLUTE_DESTINATION_FILES
   "/usr/local/share/skylendar/pics/tarots/r10.jpg;/usr/local/share/skylendar/pics/tarots/r18.jpg;/usr/local/share/skylendar/pics/tarots/r25.jpg;/usr/local/share/skylendar/pics/tarots/r32.jpg;/usr/local/share/skylendar/pics/tarots/r3.jpg;/usr/local/share/skylendar/pics/tarots/r47.jpg;/usr/local/share/skylendar/pics/tarots/r54.jpg;/usr/local/share/skylendar/pics/tarots/r61.jpg;/usr/local/share/skylendar/pics/tarots/r69.jpg;/usr/local/share/skylendar/pics/tarots/r76.jpg;/usr/local/share/skylendar/pics/tarots/r11.jpg;/usr/local/share/skylendar/pics/tarots/r19.jpg;/usr/local/share/skylendar/pics/tarots/r26.jpg;/usr/local/share/skylendar/pics/tarots/r33.jpg;/usr/local/share/skylendar/pics/tarots/r40.jpg;/usr/local/share/skylendar/pics/tarots/r48.jpg;/usr/local/share/skylendar/pics/tarots/r55.jpg;/usr/local/share/skylendar/pics/tarots/r62.jpg;/usr/local/share/skylendar/pics/tarots/r6.jpg;/usr/local/share/skylendar/pics/tarots/r77.jpg;/usr/local/share/skylendar/pics/tarots/r12.jpg;/usr/local/share/skylendar/pics/tarots/r1.jpg;/usr/local/share/skylendar/pics/tarots/r27.jpg;/usr/local/share/skylendar/pics/tarots/r34.jpg;/usr/local/share/skylendar/pics/tarots/r41.jpg;/usr/local/share/skylendar/pics/tarots/r49.jpg;/usr/local/share/skylendar/pics/tarots/r56.jpg;/usr/local/share/skylendar/pics/tarots/r63.jpg;/usr/local/share/skylendar/pics/tarots/r70.jpg;/usr/local/share/skylendar/pics/tarots/r78.jpg;/usr/local/share/skylendar/pics/tarots/r13.jpg;/usr/local/share/skylendar/pics/tarots/r20.jpg;/usr/local/share/skylendar/pics/tarots/r28.jpg;/usr/local/share/skylendar/pics/tarots/r35.jpg;/usr/local/share/skylendar/pics/tarots/r42.jpg;/usr/local/share/skylendar/pics/tarots/r4.jpg;/usr/local/share/skylendar/pics/tarots/r57.jpg;/usr/local/share/skylendar/pics/tarots/r64.jpg;/usr/local/share/skylendar/pics/tarots/r71.jpg;/usr/local/share/skylendar/pics/tarots/r7.jpg;/usr/local/share/skylendar/pics/tarots/r14.jpg;/usr/local/share/skylendar/pics/tarots/r21.jpg;/usr/local/share/skylendar/pics/tarots/r29.jpg;/usr/local/share/skylendar/pics/tarots/r36.jpg;/usr/local/share/skylendar/pics/tarots/r43.jpg;/usr/local/share/skylendar/pics/tarots/r50.jpg;/usr/local/share/skylendar/pics/tarots/r58.jpg;/usr/local/share/skylendar/pics/tarots/r65.jpg;/usr/local/share/skylendar/pics/tarots/r72.jpg;/usr/local/share/skylendar/pics/tarots/r8.jpg;/usr/local/share/skylendar/pics/tarots/r15.jpg;/usr/local/share/skylendar/pics/tarots/r22.jpg;/usr/local/share/skylendar/pics/tarots/r2.jpg;/usr/local/share/skylendar/pics/tarots/r37.jpg;/usr/local/share/skylendar/pics/tarots/r44.jpg;/usr/local/share/skylendar/pics/tarots/r51.jpg;/usr/local/share/skylendar/pics/tarots/r59.jpg;/usr/local/share/skylendar/pics/tarots/r66.jpg;/usr/local/share/skylendar/pics/tarots/r73.jpg;/usr/local/share/skylendar/pics/tarots/r9.jpg;/usr/local/share/skylendar/pics/tarots/r16.jpg;/usr/local/share/skylendar/pics/tarots/r23.jpg;/usr/local/share/skylendar/pics/tarots/r30.jpg;/usr/local/share/skylendar/pics/tarots/r38.jpg;/usr/local/share/skylendar/pics/tarots/r45.jpg;/usr/local/share/skylendar/pics/tarots/r52.jpg;/usr/local/share/skylendar/pics/tarots/r5.jpg;/usr/local/share/skylendar/pics/tarots/r67.jpg;/usr/local/share/skylendar/pics/tarots/r74.jpg;/usr/local/share/skylendar/pics/tarots/r17.jpg;/usr/local/share/skylendar/pics/tarots/r24.jpg;/usr/local/share/skylendar/pics/tarots/r31.jpg;/usr/local/share/skylendar/pics/tarots/r39.jpg;/usr/local/share/skylendar/pics/tarots/r46.jpg;/usr/local/share/skylendar/pics/tarots/r53.jpg;/usr/local/share/skylendar/pics/tarots/r60.jpg;/usr/local/share/skylendar/pics/tarots/r68.jpg;/usr/local/share/skylendar/pics/tarots/r75.jpg")
  if(CMAKE_WARN_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(WARNING "ABSOLUTE path INSTALL DESTINATION : ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
  if(CMAKE_ERROR_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(FATAL_ERROR "ABSOLUTE path INSTALL DESTINATION forbidden (by caller): ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
file(INSTALL DESTINATION "/usr/local/share/skylendar/pics/tarots" TYPE FILE FILES
    "/skylendar/skylendar-4.1nn/src/pics/tarots/r10.jpg"
    "/skylendar/skylendar-4.1nn/src/pics/tarots/r18.jpg"
    "/skylendar/skylendar-4.1nn/src/pics/tarots/r25.jpg"
    "/skylendar/skylendar-4.1nn/src/pics/tarots/r32.jpg"
    "/skylendar/skylendar-4.1nn/src/pics/tarots/r3.jpg"
    "/skylendar/skylendar-4.1nn/src/pics/tarots/r47.jpg"
    "/skylendar/skylendar-4.1nn/src/pics/tarots/r54.jpg"
    "/skylendar/skylendar-4.1nn/src/pics/tarots/r61.jpg"
    "/skylendar/skylendar-4.1nn/src/pics/tarots/r69.jpg"
    "/skylendar/skylendar-4.1nn/src/pics/tarots/r76.jpg"
    "/skylendar/skylendar-4.1nn/src/pics/tarots/r11.jpg"
    "/skylendar/skylendar-4.1nn/src/pics/tarots/r19.jpg"
    "/skylendar/skylendar-4.1nn/src/pics/tarots/r26.jpg"
    "/skylendar/skylendar-4.1nn/src/pics/tarots/r33.jpg"
    "/skylendar/skylendar-4.1nn/src/pics/tarots/r40.jpg"
    "/skylendar/skylendar-4.1nn/src/pics/tarots/r48.jpg"
    "/skylendar/skylendar-4.1nn/src/pics/tarots/r55.jpg"
    "/skylendar/skylendar-4.1nn/src/pics/tarots/r62.jpg"
    "/skylendar/skylendar-4.1nn/src/pics/tarots/r6.jpg"
    "/skylendar/skylendar-4.1nn/src/pics/tarots/r77.jpg"
    "/skylendar/skylendar-4.1nn/src/pics/tarots/r12.jpg"
    "/skylendar/skylendar-4.1nn/src/pics/tarots/r1.jpg"
    "/skylendar/skylendar-4.1nn/src/pics/tarots/r27.jpg"
    "/skylendar/skylendar-4.1nn/src/pics/tarots/r34.jpg"
    "/skylendar/skylendar-4.1nn/src/pics/tarots/r41.jpg"
    "/skylendar/skylendar-4.1nn/src/pics/tarots/r49.jpg"
    "/skylendar/skylendar-4.1nn/src/pics/tarots/r56.jpg"
    "/skylendar/skylendar-4.1nn/src/pics/tarots/r63.jpg"
    "/skylendar/skylendar-4.1nn/src/pics/tarots/r70.jpg"
    "/skylendar/skylendar-4.1nn/src/pics/tarots/r78.jpg"
    "/skylendar/skylendar-4.1nn/src/pics/tarots/r13.jpg"
    "/skylendar/skylendar-4.1nn/src/pics/tarots/r20.jpg"
    "/skylendar/skylendar-4.1nn/src/pics/tarots/r28.jpg"
    "/skylendar/skylendar-4.1nn/src/pics/tarots/r35.jpg"
    "/skylendar/skylendar-4.1nn/src/pics/tarots/r42.jpg"
    "/skylendar/skylendar-4.1nn/src/pics/tarots/r4.jpg"
    "/skylendar/skylendar-4.1nn/src/pics/tarots/r57.jpg"
    "/skylendar/skylendar-4.1nn/src/pics/tarots/r64.jpg"
    "/skylendar/skylendar-4.1nn/src/pics/tarots/r71.jpg"
    "/skylendar/skylendar-4.1nn/src/pics/tarots/r7.jpg"
    "/skylendar/skylendar-4.1nn/src/pics/tarots/r14.jpg"
    "/skylendar/skylendar-4.1nn/src/pics/tarots/r21.jpg"
    "/skylendar/skylendar-4.1nn/src/pics/tarots/r29.jpg"
    "/skylendar/skylendar-4.1nn/src/pics/tarots/r36.jpg"
    "/skylendar/skylendar-4.1nn/src/pics/tarots/r43.jpg"
    "/skylendar/skylendar-4.1nn/src/pics/tarots/r50.jpg"
    "/skylendar/skylendar-4.1nn/src/pics/tarots/r58.jpg"
    "/skylendar/skylendar-4.1nn/src/pics/tarots/r65.jpg"
    "/skylendar/skylendar-4.1nn/src/pics/tarots/r72.jpg"
    "/skylendar/skylendar-4.1nn/src/pics/tarots/r8.jpg"
    "/skylendar/skylendar-4.1nn/src/pics/tarots/r15.jpg"
    "/skylendar/skylendar-4.1nn/src/pics/tarots/r22.jpg"
    "/skylendar/skylendar-4.1nn/src/pics/tarots/r2.jpg"
    "/skylendar/skylendar-4.1nn/src/pics/tarots/r37.jpg"
    "/skylendar/skylendar-4.1nn/src/pics/tarots/r44.jpg"
    "/skylendar/skylendar-4.1nn/src/pics/tarots/r51.jpg"
    "/skylendar/skylendar-4.1nn/src/pics/tarots/r59.jpg"
    "/skylendar/skylendar-4.1nn/src/pics/tarots/r66.jpg"
    "/skylendar/skylendar-4.1nn/src/pics/tarots/r73.jpg"
    "/skylendar/skylendar-4.1nn/src/pics/tarots/r9.jpg"
    "/skylendar/skylendar-4.1nn/src/pics/tarots/r16.jpg"
    "/skylendar/skylendar-4.1nn/src/pics/tarots/r23.jpg"
    "/skylendar/skylendar-4.1nn/src/pics/tarots/r30.jpg"
    "/skylendar/skylendar-4.1nn/src/pics/tarots/r38.jpg"
    "/skylendar/skylendar-4.1nn/src/pics/tarots/r45.jpg"
    "/skylendar/skylendar-4.1nn/src/pics/tarots/r52.jpg"
    "/skylendar/skylendar-4.1nn/src/pics/tarots/r5.jpg"
    "/skylendar/skylendar-4.1nn/src/pics/tarots/r67.jpg"
    "/skylendar/skylendar-4.1nn/src/pics/tarots/r74.jpg"
    "/skylendar/skylendar-4.1nn/src/pics/tarots/r17.jpg"
    "/skylendar/skylendar-4.1nn/src/pics/tarots/r24.jpg"
    "/skylendar/skylendar-4.1nn/src/pics/tarots/r31.jpg"
    "/skylendar/skylendar-4.1nn/src/pics/tarots/r39.jpg"
    "/skylendar/skylendar-4.1nn/src/pics/tarots/r46.jpg"
    "/skylendar/skylendar-4.1nn/src/pics/tarots/r53.jpg"
    "/skylendar/skylendar-4.1nn/src/pics/tarots/r60.jpg"
    "/skylendar/skylendar-4.1nn/src/pics/tarots/r68.jpg"
    "/skylendar/skylendar-4.1nn/src/pics/tarots/r75.jpg"
    )
endif()

