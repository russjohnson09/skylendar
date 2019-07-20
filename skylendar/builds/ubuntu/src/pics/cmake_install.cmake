# Install script for directory: /skylendar/skylendar-4.1nn/src/pics

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
   "/usr/local/share/skylendar/pics/1.png;/usr/local/share/skylendar/pics/eclipse.png;/usr/local/share/skylendar/pics/journey.png;/usr/local/share/skylendar/pics/ordeal.png;/usr/local/share/skylendar/pics/square.png;/usr/local/share/skylendar/pics/2.png;/usr/local/share/skylendar/pics/beginning.png;/usr/local/share/skylendar/pics/end.png;/usr/local/share/skylendar/pics/local.png;/usr/local/share/skylendar/pics/previous.png;/usr/local/share/skylendar/pics/stdlist.png;/usr/local/share/skylendar/pics/3.png;/usr/local/share/skylendar/pics/coin.png;/usr/local/share/skylendar/pics/exasp.png;/usr/local/share/skylendar/pics/lunar_rev.png;/usr/local/share/skylendar/pics/publication.png;/usr/local/share/skylendar/pics/stdwheel.png;/usr/local/share/skylendar/pics/4.png;/usr/local/share/skylendar/pics/company.png;/usr/local/share/skylendar/pics/fest.png;/usr/local/share/skylendar/pics/major.png;/usr/local/share/skylendar/pics/restriction.png;/usr/local/share/skylendar/pics/stick.png;/usr/local/share/skylendar/pics/accident.png;/usr/local/share/skylendar/pics/country.png;/usr/local/share/skylendar/pics/first.png;/usr/local/share/skylendar/pics/marriage.png;/usr/local/share/skylendar/pics/rising.png;/usr/local/share/skylendar/pics/subtype.png;/usr/local/share/skylendar/pics/anim2.png;/usr/local/share/skylendar/pics/cup.png;/usr/local/share/skylendar/pics/group.png;/usr/local/share/skylendar/pics/meeting.png;/usr/local/share/skylendar/pics/searchdata.png;/usr/local/share/skylendar/pics/sword.png;/usr/local/share/skylendar/pics/animation.png;/usr/local/share/skylendar/pics/dirch.png;/usr/local/share/skylendar/pics/icon.png;/usr/local/share/skylendar/pics/newdata.png;/usr/local/share/skylendar/pics/signch.png;/usr/local/share/skylendar/pics/tarotspread.png;/usr/local/share/skylendar/pics/asptable.png;/usr/local/share/skylendar/pics/direction.png;/usr/local/share/skylendar/pics/idea.png;/usr/local/share/skylendar/pics/next.png;/usr/local/share/skylendar/pics/skylendar.jpg;/usr/local/share/skylendar/pics/Type.png;/usr/local/share/skylendar/pics/astrograph.png;/usr/local/share/skylendar/pics/divorce.png;/usr/local/share/skylendar/pics/illness.png;/usr/local/share/skylendar/pics/now.png;/usr/local/share/skylendar/pics/solar_rev.png;/usr/local/share/skylendar/pics/up.png;/usr/local/share/skylendar/pics/attention.png;/usr/local/share/skylendar/pics/down.png;/usr/local/share/skylendar/pics/invbg.png;/usr/local/share/skylendar/pics/objlist.png;/usr/local/share/skylendar/pics/solar_sys.png;/usr/local/share/skylendar/pics/ephemeris.png;/usr/local/share/skylendar/pics/pdir.png;/usr/local/share/skylendar/pics/cpdir.png;/usr/local/share/skylendar/pics/occult.png;/usr/local/share/skylendar/pics/tensorflow.png")
  if(CMAKE_WARN_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(WARNING "ABSOLUTE path INSTALL DESTINATION : ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
  if(CMAKE_ERROR_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(FATAL_ERROR "ABSOLUTE path INSTALL DESTINATION forbidden (by caller): ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
file(INSTALL DESTINATION "/usr/local/share/skylendar/pics" TYPE FILE FILES
    "/skylendar/skylendar-4.1nn/src/pics/1.png"
    "/skylendar/skylendar-4.1nn/src/pics/eclipse.png"
    "/skylendar/skylendar-4.1nn/src/pics/journey.png"
    "/skylendar/skylendar-4.1nn/src/pics/ordeal.png"
    "/skylendar/skylendar-4.1nn/src/pics/square.png"
    "/skylendar/skylendar-4.1nn/src/pics/2.png"
    "/skylendar/skylendar-4.1nn/src/pics/beginning.png"
    "/skylendar/skylendar-4.1nn/src/pics/end.png"
    "/skylendar/skylendar-4.1nn/src/pics/local.png"
    "/skylendar/skylendar-4.1nn/src/pics/previous.png"
    "/skylendar/skylendar-4.1nn/src/pics/stdlist.png"
    "/skylendar/skylendar-4.1nn/src/pics/3.png"
    "/skylendar/skylendar-4.1nn/src/pics/coin.png"
    "/skylendar/skylendar-4.1nn/src/pics/exasp.png"
    "/skylendar/skylendar-4.1nn/src/pics/lunar_rev.png"
    "/skylendar/skylendar-4.1nn/src/pics/publication.png"
    "/skylendar/skylendar-4.1nn/src/pics/stdwheel.png"
    "/skylendar/skylendar-4.1nn/src/pics/4.png"
    "/skylendar/skylendar-4.1nn/src/pics/company.png"
    "/skylendar/skylendar-4.1nn/src/pics/fest.png"
    "/skylendar/skylendar-4.1nn/src/pics/major.png"
    "/skylendar/skylendar-4.1nn/src/pics/restriction.png"
    "/skylendar/skylendar-4.1nn/src/pics/stick.png"
    "/skylendar/skylendar-4.1nn/src/pics/accident.png"
    "/skylendar/skylendar-4.1nn/src/pics/country.png"
    "/skylendar/skylendar-4.1nn/src/pics/first.png"
    "/skylendar/skylendar-4.1nn/src/pics/marriage.png"
    "/skylendar/skylendar-4.1nn/src/pics/rising.png"
    "/skylendar/skylendar-4.1nn/src/pics/subtype.png"
    "/skylendar/skylendar-4.1nn/src/pics/anim2.png"
    "/skylendar/skylendar-4.1nn/src/pics/cup.png"
    "/skylendar/skylendar-4.1nn/src/pics/group.png"
    "/skylendar/skylendar-4.1nn/src/pics/meeting.png"
    "/skylendar/skylendar-4.1nn/src/pics/searchdata.png"
    "/skylendar/skylendar-4.1nn/src/pics/sword.png"
    "/skylendar/skylendar-4.1nn/src/pics/animation.png"
    "/skylendar/skylendar-4.1nn/src/pics/dirch.png"
    "/skylendar/skylendar-4.1nn/src/pics/icon.png"
    "/skylendar/skylendar-4.1nn/src/pics/newdata.png"
    "/skylendar/skylendar-4.1nn/src/pics/signch.png"
    "/skylendar/skylendar-4.1nn/src/pics/tarotspread.png"
    "/skylendar/skylendar-4.1nn/src/pics/asptable.png"
    "/skylendar/skylendar-4.1nn/src/pics/direction.png"
    "/skylendar/skylendar-4.1nn/src/pics/idea.png"
    "/skylendar/skylendar-4.1nn/src/pics/next.png"
    "/skylendar/skylendar-4.1nn/src/pics/skylendar.jpg"
    "/skylendar/skylendar-4.1nn/src/pics/Type.png"
    "/skylendar/skylendar-4.1nn/src/pics/astrograph.png"
    "/skylendar/skylendar-4.1nn/src/pics/divorce.png"
    "/skylendar/skylendar-4.1nn/src/pics/illness.png"
    "/skylendar/skylendar-4.1nn/src/pics/now.png"
    "/skylendar/skylendar-4.1nn/src/pics/solar_rev.png"
    "/skylendar/skylendar-4.1nn/src/pics/up.png"
    "/skylendar/skylendar-4.1nn/src/pics/attention.png"
    "/skylendar/skylendar-4.1nn/src/pics/down.png"
    "/skylendar/skylendar-4.1nn/src/pics/invbg.png"
    "/skylendar/skylendar-4.1nn/src/pics/objlist.png"
    "/skylendar/skylendar-4.1nn/src/pics/solar_sys.png"
    "/skylendar/skylendar-4.1nn/src/pics/ephemeris.png"
    "/skylendar/skylendar-4.1nn/src/pics/pdir.png"
    "/skylendar/skylendar-4.1nn/src/pics/cpdir.png"
    "/skylendar/skylendar-4.1nn/src/pics/occult.png"
    "/skylendar/skylendar-4.1nn/src/pics/tensorflow.png"
    )
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for each subdirectory.
  include("/skylendar/builds/ubuntu/src/pics/tarots/cmake_install.cmake")

endif()

