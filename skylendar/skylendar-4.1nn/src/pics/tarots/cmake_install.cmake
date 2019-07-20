# Install script for directory: /home/cg/cc/skylendar/src/pics/tarots

# Set the install prefix
if(NOT DEFINED CMAKE_INSTALL_PREFIX)
  set(CMAKE_INSTALL_PREFIX "/opt/kde5")
endif()
string(REGEX REPLACE "/$" "" CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")

# Set the install configuration name.
if(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)
  if(BUILD_TYPE)
    string(REGEX REPLACE "^[^A-Za-z0-9_]+" ""
           CMAKE_INSTALL_CONFIG_NAME "${BUILD_TYPE}")
  else()
    set(CMAKE_INSTALL_CONFIG_NAME "Debug")
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
  set(CMAKE_INSTALL_SO_NO_EXE "0")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "skylendar")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/skylendar/pics/tarots" TYPE FILE FILES
    "/home/cg/cc/skylendar/src/pics/tarots/r10.jpg"
    "/home/cg/cc/skylendar/src/pics/tarots/r18.jpg"
    "/home/cg/cc/skylendar/src/pics/tarots/r25.jpg"
    "/home/cg/cc/skylendar/src/pics/tarots/r32.jpg"
    "/home/cg/cc/skylendar/src/pics/tarots/r3.jpg"
    "/home/cg/cc/skylendar/src/pics/tarots/r47.jpg"
    "/home/cg/cc/skylendar/src/pics/tarots/r54.jpg"
    "/home/cg/cc/skylendar/src/pics/tarots/r61.jpg"
    "/home/cg/cc/skylendar/src/pics/tarots/r69.jpg"
    "/home/cg/cc/skylendar/src/pics/tarots/r76.jpg"
    "/home/cg/cc/skylendar/src/pics/tarots/r11.jpg"
    "/home/cg/cc/skylendar/src/pics/tarots/r19.jpg"
    "/home/cg/cc/skylendar/src/pics/tarots/r26.jpg"
    "/home/cg/cc/skylendar/src/pics/tarots/r33.jpg"
    "/home/cg/cc/skylendar/src/pics/tarots/r40.jpg"
    "/home/cg/cc/skylendar/src/pics/tarots/r48.jpg"
    "/home/cg/cc/skylendar/src/pics/tarots/r55.jpg"
    "/home/cg/cc/skylendar/src/pics/tarots/r62.jpg"
    "/home/cg/cc/skylendar/src/pics/tarots/r6.jpg"
    "/home/cg/cc/skylendar/src/pics/tarots/r77.jpg"
    "/home/cg/cc/skylendar/src/pics/tarots/r12.jpg"
    "/home/cg/cc/skylendar/src/pics/tarots/r1.jpg"
    "/home/cg/cc/skylendar/src/pics/tarots/r27.jpg"
    "/home/cg/cc/skylendar/src/pics/tarots/r34.jpg"
    "/home/cg/cc/skylendar/src/pics/tarots/r41.jpg"
    "/home/cg/cc/skylendar/src/pics/tarots/r49.jpg"
    "/home/cg/cc/skylendar/src/pics/tarots/r56.jpg"
    "/home/cg/cc/skylendar/src/pics/tarots/r63.jpg"
    "/home/cg/cc/skylendar/src/pics/tarots/r70.jpg"
    "/home/cg/cc/skylendar/src/pics/tarots/r78.jpg"
    "/home/cg/cc/skylendar/src/pics/tarots/r13.jpg"
    "/home/cg/cc/skylendar/src/pics/tarots/r20.jpg"
    "/home/cg/cc/skylendar/src/pics/tarots/r28.jpg"
    "/home/cg/cc/skylendar/src/pics/tarots/r35.jpg"
    "/home/cg/cc/skylendar/src/pics/tarots/r42.jpg"
    "/home/cg/cc/skylendar/src/pics/tarots/r4.jpg"
    "/home/cg/cc/skylendar/src/pics/tarots/r57.jpg"
    "/home/cg/cc/skylendar/src/pics/tarots/r64.jpg"
    "/home/cg/cc/skylendar/src/pics/tarots/r71.jpg"
    "/home/cg/cc/skylendar/src/pics/tarots/r7.jpg"
    "/home/cg/cc/skylendar/src/pics/tarots/r14.jpg"
    "/home/cg/cc/skylendar/src/pics/tarots/r21.jpg"
    "/home/cg/cc/skylendar/src/pics/tarots/r29.jpg"
    "/home/cg/cc/skylendar/src/pics/tarots/r36.jpg"
    "/home/cg/cc/skylendar/src/pics/tarots/r43.jpg"
    "/home/cg/cc/skylendar/src/pics/tarots/r50.jpg"
    "/home/cg/cc/skylendar/src/pics/tarots/r58.jpg"
    "/home/cg/cc/skylendar/src/pics/tarots/r65.jpg"
    "/home/cg/cc/skylendar/src/pics/tarots/r72.jpg"
    "/home/cg/cc/skylendar/src/pics/tarots/r8.jpg"
    "/home/cg/cc/skylendar/src/pics/tarots/r15.jpg"
    "/home/cg/cc/skylendar/src/pics/tarots/r22.jpg"
    "/home/cg/cc/skylendar/src/pics/tarots/r2.jpg"
    "/home/cg/cc/skylendar/src/pics/tarots/r37.jpg"
    "/home/cg/cc/skylendar/src/pics/tarots/r44.jpg"
    "/home/cg/cc/skylendar/src/pics/tarots/r51.jpg"
    "/home/cg/cc/skylendar/src/pics/tarots/r59.jpg"
    "/home/cg/cc/skylendar/src/pics/tarots/r66.jpg"
    "/home/cg/cc/skylendar/src/pics/tarots/r73.jpg"
    "/home/cg/cc/skylendar/src/pics/tarots/r9.jpg"
    "/home/cg/cc/skylendar/src/pics/tarots/r16.jpg"
    "/home/cg/cc/skylendar/src/pics/tarots/r23.jpg"
    "/home/cg/cc/skylendar/src/pics/tarots/r30.jpg"
    "/home/cg/cc/skylendar/src/pics/tarots/r38.jpg"
    "/home/cg/cc/skylendar/src/pics/tarots/r45.jpg"
    "/home/cg/cc/skylendar/src/pics/tarots/r52.jpg"
    "/home/cg/cc/skylendar/src/pics/tarots/r5.jpg"
    "/home/cg/cc/skylendar/src/pics/tarots/r67.jpg"
    "/home/cg/cc/skylendar/src/pics/tarots/r74.jpg"
    "/home/cg/cc/skylendar/src/pics/tarots/r17.jpg"
    "/home/cg/cc/skylendar/src/pics/tarots/r24.jpg"
    "/home/cg/cc/skylendar/src/pics/tarots/r31.jpg"
    "/home/cg/cc/skylendar/src/pics/tarots/r39.jpg"
    "/home/cg/cc/skylendar/src/pics/tarots/r46.jpg"
    "/home/cg/cc/skylendar/src/pics/tarots/r53.jpg"
    "/home/cg/cc/skylendar/src/pics/tarots/r60.jpg"
    "/home/cg/cc/skylendar/src/pics/tarots/r68.jpg"
    "/home/cg/cc/skylendar/src/pics/tarots/r75.jpg"
    )
endif()

