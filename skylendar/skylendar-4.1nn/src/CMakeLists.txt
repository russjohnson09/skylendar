#
# Skylendar 4.1nn
#
# Copyright Christophe Gros skylendar@yahoo.com 2000-2016
#
# This software has been released under the terms of the GPL
# license.
#

macro(Compile_rc OBJ SRC SRCS)
	if(MINGW)
    # This gets us DLL resource information when compiling on MinGW.
    add_custom_command(OUTPUT ${CMAKE_CURRENT_BINARY_DIR}/${OBJ}
                       COMMAND windres.exe
                            -D GCC_WINDRES
                            -I ${CMAKE_CURRENT_SOURCE_DIR}
                            -I ${CMAKE_CURRENT_BINARY_DIR}
                           -o ${CMAKE_CURRENT_BINARY_DIR}/${OBJ}
                           -i ${CMAKE_CURRENT_SOURCE_DIR}/${SRC})
   set(${SRCS} ${${SRCS}} ${CMAKE_CURRENT_BINARY_DIR}/${OBJ})
 endif()
endmacro()

set(CPACK_PACKAGE_VERSION "4.1nn")

find_package(Perl)
if(Perl_FOUND)
	find_package(PerlLibs)
endif()

if(NOT WIN32)
	if(CMAKE_SIZEOF_VOID_P EQUAL 8)
		set(LIB_INSTALL_DIR "${CMAKE_INSTALL_PREFIX}/lib64")
	else()
		set(LIB_INSTALL_DIR "${CMAKE_INSTALL_PREFIX}/lib")
	endif()
	set(BIN_INSTALL_DIR "${CMAKE_INSTALL_PREFIX}/bin")
	set(APPS_INSTALL_DIR "${CMAKE_INSTALL_PREFIX}/share/applications")
	set(DATA_INSTALL_DIR "${CMAKE_INSTALL_PREFIX}/share/skylendar" CACHE PATH "Data path")
	set(ICON_INSTALL_DIR "${CMAKE_INSTALL_PREFIX}/share/icons")
	set(MIME_INSTALL_DIR "${CMAKE_INSTALL_PREFIX}/share/mime/packages")
	set(CPACK_PACKAGE_NAME "skylendar")
	set(CPACK_RPM_PACKAGE_GROUP "Science")
	set(CPACK_RPM_PACKAGE_LICENSE "GPL")
	set(CPACK_RPM_PACKAGE_URL "${SKYSITE}")
	set(CPACK_RPM_PACKAGE_REQUIRES "postgresql >= 9.3.0, libqt5-sql-postgresql >= 4.8.5, perl >= 5.16, perl(XML::DOM) >= 1.44, perl(DBD::Pg)")
	if(CMAKE_SIZEOF_VOID_P EQUAL 8)
		set(CPACK_RPM_PACKAGE_ARCHITECTURE "x86_64")
	else()
		set(CPACK_RPM_PACKAGE_ARCHITECTURE "x86")
	endif()
	set(CPACK_PACKAGE_FILE_NAME "${CPACK_PACKAGE_NAME}-${CPACK_PACKAGE_VERSION}-${CPACK_RPM_PACKAGE_ARCHITECTURE}")
	set(CPACK_RPM_POST_INSTALL_SCRIPT_FILE "${CMAKE_SOURCE_DIR}/src/if.sh\ncp skylendar-${CPACK_PACKAGE_VERSION}-win32\\\\data\\\\skif.pm \"${PLIB}\"")

else()
	#set( CPACK_NSIS_EXTRA_PREINSTALL_COMMANDS "!include FontReg.nsh")
	set(CPACK_NSIS_INSTALL_ROOT "C:\\\\Program Files")
	set(LIB_INSTALL_DIR "bin")
	set(BIN_INSTALL_DIR "bin")
	set(SKYICON "${CMAKE_SOURCE_DIR}\\\\src\\\\skylendar.bmp")
	set(CPACK_PACKAGE_ICON ${SKYICON})
	set(DATA_INSTALL_DIR "data" CACHE PATH "Data path")
	set(CPACK_NSIS_MUI_ICON "${CMAKE_SOURCE_DIR}/src/skylendar.ico")
	set(CPACK_NSIS_MENU_LINKS "bin/skylendar.exe" "Skylendar" "bin/skydmin.exe" "Skydmin")
	set(CPACK_NSIS_DISPLAY_NAME "${CPACK_PACKAGE_INSTALL_DIRECTORY} Skylendar")
	set(CPACK_NSIS_URL_INFO_ABOUT "${SKYSITE}")
	SET(CPACK_NSIS_HELP_LINK "skylendar.sourceforge.io")
	set(CPACK_NSIS_INSTALLER_ICON_NAME "bin/skylendar.exe")
	set(CPACK_NSIS_MODIFY_PATH ON)
	set(CPACK_NSIS_CREATE_ICONS_EXTRA "CreateShortCut '\$DESKTOP\\\\${PROJECT_NAME}.lnk' '\$INSTDIR\\\\bin\\\\${PROJECT_NAME}.exe'")
	string(REPLACE "/" "\\" P1LIB ${PLIB})
	set(CPACK_NSIS_CREATE_ICONS_EXTRA "StrCpy $FONT_DIR $FONTS\n !insertmacro InstallTTFFont skylendar-${CPACK_PACKAGE_VERSION}-win32\\\\data\\\\skylendar.ttf\nSetOutPath ${PLIB}\nFile skylendar-${CPACK_PACKAGE_VERSION}-win32\\\\data\\\\skif.pm") 
endif()
set(CPACK_PACKAGE_DESCRIPTION_SUMMARY "A powerful astrology software")
set(CPACK_PACKAGE_VENDOR "Skylendar")
set(CPACK_NSIS_CONTACT "skylendar@yahoo.com")
set(CPACK_RESOURCE_FILE_LICENSE "${CMAKE_SOURCE_DIR}/COPYING")
include(CPack)
include(CPackComponent)
CPACK_ADD_COMPONENT(postgreSQL DISPLAY_NAME PostgreSQL DESCRIPTION "Relational Database" DISABLED DOWNLOADED ARCHIVE_FILE "http://postgresql.org/download/")
CPACK_ADD_COMPONENT(Perl DISPLAY_NAME Perl DESCRIPTION "Perl language" DISABLED DOWNLOADED ARCHIVE_FILE "http://dplus.en.softonic.com/ud-client/2000/2072/SoftonicDownloader_for_activeperl.exe")
#set(CPACK_PACKAGE_FILE_NAME "${CPACK_PACKAGE_NAME}-${CPACK_PACKAGE_VERSION}-${CPACK_RPM_PACKAGE_ARCHITECTURE}")
# ajouter find_package(SharedMimeInfo REQUIRED)
set(CMAKE_VERBOSE_MAKEFILE ON)
include_directories(${CMAKE_BINARY_DIR}/src ${CMAKE_SOURCE_DIR}/src ${CMAKE_SOURCE_DIR}/src/pics  ${CMAKE_SOURCE_DIR}/src/swe)
add_subdirectory(swe)

add_definitions(-std=c++11 -frtti -fopenmp -fexceptions -Wno-unused-parameter -Wno-unused-but-set-variable -Wno-overloaded-virtual -DSKYPATH="${DATA_INSTALL_DIR}")

if(SHARED_CODE)
	add_definitions(-DSHARED)
endif()

if(NATIVE)
 add_definitions(-DNATIVE -I${PostgreSQL_INCLUDE_DIRS})
 link_directories(${PostgreSQL_LIBRARY_DIRS})
endif()


add_subdirectory( pics )

########### next target ###############

set(skylendar_LIB_SRCS 
   aspconflist.cpp 
   asprestr.cpp 
   aspscanlist.cpp 
   astroaspects.cpp 
   astroaspectsarray.cpp 
   astrochart.cpp 
   astrochartbase.cpp 
   astrodata.cpp 
   astrodate.cpp 
   astrodirections.cpp 
   astroephemeris.cpp 
   astrograph.cpp 
   astrographics.cpp 
   astrohm.cpp 
   astrointerface.cpp 
   astromainwindow.cpp 
   astromidpoints.cpp 
   astroobjectslist.cpp 
   astroobjs.cpp 
   astroparams.cpp 
   astroresources.cpp 
   astrorestrictions.cpp 
   astrorings.cpp 
   astrosigns.cpp  
   astrosplash.cpp 
   astrosql.cpp 
   astrotarotspreads.cpp 
   astroutils.cpp 
   astrowindow.cpp 
   editaddmul.cpp 
   editastrodata.cpp 
   editchartparms.cpp
   editdefparms.cpp 
   editdirections.cpp 
   editplace.cpp 
   editrestrictions.cpp 
   graphiclistbase.cpp 
   localhorizonchart.cpp 
   objrestr.cpp 
   astroenter.cpp 
   scanspan.cpp 
   searchchart.cpp 
   searchdata.cpp 
   searchrest.cpp 
   solarsyschart.cpp 
   spreads.cpp 
   squared.cpp 
   stdgraphiclist.cpp 
   stdwheelchart.cpp 
   stopscan.cpp 
   tz.cpp 
   tzlist.cpp 
   validskif.cpp
   astroheader.cpp
   astroprocess.cpp
   astroapp.cpp
   astrogauquelinchart.cpp
    direngine.cpp
    astrohousepos.cpp
    astrobatch.cpp
    astroconstellations.cpp
    astrospot.cpp
)

if(SHARED_CODE)
	set(MOC_H scanclient.h astrogetvalues.h astrospinbox.h astroaccess.h astrochoosecol.h)
else()
	list(APPEND skylendar_LIB_SRCS editcountry.cpp)
	set(MOC_H scanclient.h astrogetvalues.h astrospinbox.h astrochoosecol.h astrochartbase.h astrowindow.h objrestr.h searchchart.h astroenter.h searchdata.h asprestr.h editplace.h validskif.h editdirections.h scanspan.h editaddmul.h editchartparms.h astroprocess.h editrestrictions.h searchrest.h astromainwindow.h editdefparms.h astrosplash.h editcountry.h editastrodata.h stopscan.h astrodata.h astrospot.h)
endif()


set(SKYLENDAR_UI
	 asprestr.ui
   editaddmul.ui 
   editchartparms.ui 
   editcountry.ui 
   editdirections.ui
   objrestr.ui 
   scanspan.ui 
   searchchart.ui 
   searchdata.ui 
   searchrest.ui 
   spreads.ui 
   stopscan.ui 
   validskif.ui
   batch.ui
   about.ui
)

if(SHARED_CODE)
	list(APPEND SKYLENDAR_UI editastrodata_shared.ui
		editrestrictions_shared.ui astroentershared.ui editplace_shared.ui
		 editdefparms_shared.ui access.ui astrosplash_shared.ui)
else()
	 list(APPEND SKYLENDAR_UI editastrodata.ui
		editrestrictions.ui editplace.ui  editdefparms.ui astroenter.ui astrosplash.ui)
endif()

qt5_wrap_ui(skylendar_LIB_SRCS ${SKYLENDAR_UI})

qt5_generate_dbus_interface(scanclient.h ${CMAKE_CURRENT_BINARY_DIR}/scanclient.xml)

qt5_add_dbus_adaptor(SRC ${CMAKE_CURRENT_BINARY_DIR}/scanclient.xml scanclient.h ScanClient)

qt5_generate_dbus_interface(astrogetvalues.h ${CMAKE_CURRENT_BINARY_DIR}/astrogetvalues.xml)

qt5_add_dbus_adaptor(SRC1 ${CMAKE_CURRENT_BINARY_DIR}/astrogetvalues.xml astrogetvalues.h AstroGetValues)

qt5_generate_dbus_interface(astroprocess.h ${CMAKE_CURRENT_BINARY_DIR}/astroprocess.xml)

qt5_add_dbus_interface(SRC2 ${CMAKE_CURRENT_BINARY_DIR}/astroprocess.xml astroprocessinterface)

qt5_add_dbus_adaptor(SRC3 ${CMAKE_CURRENT_BINARY_DIR}/astroprocess.xml astroprocess.h AstroComputing)

qt5_add_dbus_interface(SRC4 ${CMAKE_CURRENT_BINARY_DIR}/scanclient.xml scanclientinterface)

qt5_wrap_cpp(MOC_FILES ${MOC_H})

qt5_add_resources(RES skylendar.qrc)

add_library(skyldr SHARED ${skylendar_LIB_SRCS} ${SRC} ${SRC1} ${SRC2} ${SRC3} ${SRC4} ${SRC5} ${MOC_FILES} ${RES})
#string(REPLACE "/cmake/Qt5" "/libQt5" L1 ${Qt5_DIR})
#set_target_properties(Qt5::Core PROPERTIES LOCATION  ${L1}Core.a)
#set_target_properties(Qt5::Xml PROPERTIES LOCATION  ${L1}Xml.a)
#set_target_properties(Qt5::Svg PROPERTIES LOCATION  ${L1}Svg.a)
#set_target_properties(Qt5::Widgets PROPERTIES LOCATION  ${L1}Widgets.a)
#set_target_properties(Qt5::Network PROPERTIES LOCATION  ${L1}Network.a)
#set_target_properties(Qt5::DBus PROPERTIES LOCATION  ${L1}DBus.a)

set(skyldr_LIBS 
Qt5::PrintSupport
Qt5::Xml
Qt5::Sql
Qt5::DBus
Qt5::Svg
Qt5::Network
z
swe
gomp
)

if(WIN32)
	list(APPEND skyldr_LIBS wsock32)
	add_definitions(-IC:/qt/include/QtZlib)
else()
	list(APPEND skyldr_LIBS)
endif()
if(NATIVE)
	list(APPEND skyldr_LIBS ${PostgreSQL_LIBRARIES})
endif()

add_dependencies(skyldr swe)
#add_dependencies(skyldr KXmlRpcClient)

target_link_libraries(skyldr ${skyldr_LIBS})

set_target_properties(skyldr PROPERTIES VERSION ${CPACK_PACKAGE_VERSION} SOVERSION 4 )

install(TARGETS skyldr DESTINATION ${LIB_INSTALL_DIR})

########### next target ###############

set(skylendar_SRCS skylendar.cpp)

if(MINGW)
    # This gets us DLL resource information when compiling on MinGW.
    add_custom_command(OUTPUT ${CMAKE_CURRENT_BINARY_DIR}/skyres.obj
                       COMMAND windres.exe
                            -D GCC_WINDRES
                            -I ${CMAKE_CURRENT_SOURCE_DIR}
                            -I ${CMAKE_CURRENT_BINARY_DIR}
                           -o ${CMAKE_CURRENT_BINARY_DIR}/skyres.obj
                           -i ${CMAKE_CURRENT_SOURCE_DIR}/skylendar.rc)
   list(APPEND skylendar_SRCS ${CMAKE_CURRENT_BINARY_DIR}/skyres.obj)
endif()
link_directories(${skylendar_SOURCE_DIR}/lib)

add_executable(skylendar WIN32 ${skylendar_SRCS})

target_link_libraries(skylendar skyldr)

install(TARGETS skylendar DESTINATION ${BIN_INSTALL_DIR})

########### next target ###############

set(skyservice_SRCS skyservice.cpp)
if(MINGW)
    # This gets us DLL resource information when compiling on MinGW.
    add_custom_command(OUTPUT ${CMAKE_CURRENT_BINARY_DIR}/skysvres.obj
                       COMMAND windres.exe
                            -D GCC_WINDRES
                            -I ${CMAKE_CURRENT_SOURCE_DIR}
                            -I ${CMAKE_CURRENT_BINARY_DIR}
                           -o ${CMAKE_CURRENT_BINARY_DIR}/skysvres.obj
                           -i ${CMAKE_CURRENT_SOURCE_DIR}/skyservice.rc)
   list(APPEND skyservice_SRCS ${CMAKE_CURRENT_BINARY_DIR}/skysvres.obj)
endif()
add_executable(skyservice WIN32 ${skyservice_SRCS})

link_directories(${skylendar_SOURCE_DIR}/lib)

target_link_libraries(skyservice skyldr)

install(TARGETS skyservice DESTINATION ${BIN_INSTALL_DIR})

########### next target ###############
if(NOT SHARED)

	set(skydmin_SRCS skydmin.cpp)
	if(MINGW)
    # This gets us DLL resource information when compiling on MinGW.
    add_custom_command(OUTPUT ${CMAKE_CURRENT_BINARY_DIR}/skydmres.obj
                       COMMAND windres.exe
                            -D GCC_WINDRES
                            -I ${CMAKE_CURRENT_SOURCE_DIR}
                            -I ${CMAKE_CURRENT_BINARY_DIR}
                           -o ${CMAKE_CURRENT_BINARY_DIR}/skydmres.obj
                           -i ${CMAKE_CURRENT_SOURCE_DIR}/skydmin.rc)
   list(APPEND skydmin_SRCS ${CMAKE_CURRENT_BINARY_DIR}/skydmres.obj)
endif()
	qt5_wrap_ui(skydmin_SRCS skydmin.ui password.ui asteroid.ui)
	qt5_wrap_cpp(MOC1_H skydmin.h)
	qt5_add_resources(skydmin_SRCS  skydmin.qrc)

	add_executable(skydmin WIN32 ${MOC1_H} ${skydmin_SRCS})

	link_directories(${skylendar_SOURCE_DIR}/lib)

	set(skydmin_LIBS
		Qt5::Core
		Qt5::Widgets
		Qt5::DBus
		Qt5::Sql
		Qt5::Network
		)
	if(WIN32)
		target_link_libraries(skydmin  ${skydmin_LIBS} mpr netapi32)
	else()
		target_link_libraries(skydmin ${skydmin_LIBS})
	endif()
	install(TARGETS skydmin DESTINATION ${BIN_INSTALL_DIR})
endif()

########### install files ###############
if(NOT WIN32)
	install(FILES skylendar.desktop DESTINATION ${APPS_INSTALL_DIR} )
	if(NOT SHARED)
		install(FILES skydmin.desktop DESTINATION ${APPS_INSTALL_DIR} )
	endif(NOT SHARED)
	install(FILES skylendar.png DESTINATION ${ICON_INSTALL_DIR})
	install(FILES skydmin.png DESTINATION ${ICON_INSTALL_DIR})
	install(FILES skif.png DESTINATION ${ICON_INSTALL_DIR})
	install(FILES skif.desktop DESTINATION ${MIME_INSTALL_DIR})
	install(FILES skylendar.ttf DESTINATION /usr/share/fonts/truetype)
	exec_program(mkfontdir ARGS /usr/share/fonts/truetype)
else()
	install(FILES windows/dbus-daemon.exe windows/libdbus-1-3.dll windows/libexpat.dll windows/session.conf   DESTINATION ${BIN_INSTALL_DIR})
	install(DIRECTORY "zoneinfo" DESTINATION ${DATA_INSTALL_DIR})
	#install(FILES skylendar.ttf DESTINATION ${DATA_INSTALL_DIR})
endif()
install(FILES CIA_WDB2.jpd.gz skif.dtd skylendar.pfb sefstars.txt sedeltat.txt.inactive seas_18.se1 semo_18.se1 seorbel.txt sepl_18.se1 seleapsec.txt ../README  ../COPYING ../HISTORY.txt DESTINATION ${DATA_INSTALL_DIR} )
if(NOT SHARED)
	install(FILES installskydb.sql skif.pm Country.txt D1901.txt Degrees.txt
		ExtraObjs.txt Place.txt Tarots.txt Parts.txt Interpret.txt Intertarots.txt ConsNames.txt Boundaries.txt Stars.txt DESTINATION ${DATA_INSTALL_DIR})
endif()

#install(FILES skylendarui.rc DESTINATION ${DATA_INSTALL_DIR} )
if(perl_FOUND)
	install(FILES skif.pl DESTINATION ${BIN_INSTALL_DIR} PERMISSIONS OWNER_READ OWNER_WRITE OWNER_EXECUTE GROUP_READ GROUP_EXECUTE WORLD_READ WORLD_EXECUTE)
	install(FILES skif.pm ${PERL_VENDORLIB})
endif()

#update_xdg_mimetypes(${XDG_MIME_INSTALL_DIR})

set(CPACK_STRIP_FILES "bin/libskyldr.dll" "bin/skylendar.exe" "bin/skydmin.exe" "bin/skyservice.exe")

set(sds skydmin.cpp skydmin.ui login.ui password.ui asteroid.ui)

qt5_create_translation(SKYLQM ${skylendar_LIB_SRCS} ${SKYLENDAR_UI} skylendar_fr_FR.ts OPTIONS -tr-function-alias tr+=i18n,tr+=i18n2)

qt5_create_translation(SKYDQM ${sds} skydmin_fr_FR.ts OPTIONS -tr-function-alias tr+=i18n,tr+=i18n2)

ADD_CUSTOM_TARGET (translations ALL DEPENDS ${SKYLQM} ${SKYDQM})

install(FILES  ${CMAKE_CURRENT_BINARY_DIR}/skylendar_fr_FR.qm ${CMAKE_CURRENT_BINARY_DIR}/skydmin_fr_FR.qm DESTINATION ${DATA_INSTALL_DIR})
