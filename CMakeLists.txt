################################################################################
#   CMakeLists.txt for Liz's 2018 winter project.                              #
#                                                                              #
#                      - 10. Jan. 2018. Hoyong Jeong (hyjeong@hep.korea.ac.kr) #
################################################################################

#------------------------------------------------------------------------------#
#   Setup the project                                                          #
#------------------------------------------------------------------------------#
cmake_minimum_required(VERSION 2.6 FATAL_ERROR)
project(MUON)

#------------------------------------------------------------------------------#
#   Find Geant4 package, activating all available UI and Vis drivers by        #
# default. You can set WITH_GEANT4_UIVIS to OFF via the command line or        #
# ccmake/cmake-gui to build a batch mode only executable.                      #
#------------------------------------------------------------------------------#
option(WITH_GEANT4_UIVIS "Build muon with Geant4 UI and Vis drivers" ON)
if(WITH_GEANT4_UIVIS)
	find_package(Geant4 REQUIRED ui_all vis_all)
else()
	find_package(Geant4 REQUIRED)
endif()

#------------------------------------------------------------------------------#
#   Find ROOT package.                                                         #
#------------------------------------------------------------------------------#
find_package(ROOT REQUIRED)

#------------------------------------------------------------------------------#
#   Setup Geant4 include directories and compile definitions                   #
#   Setup include directory for this project                                   #
#   Setup ROOT include directories and compile definitions.                    #
#------------------------------------------------------------------------------#
include(${Geant4_USE_FILE})
include_directories(${PROJECT_SOURCE_DIR}/include)
include(${ROOT_USE_FILE})

#------------------------------------------------------------------------------#
#   Locate sources and headers for this project                                #
#   NB: headers are included so they will show up in IDEs                      #
#------------------------------------------------------------------------------#
file(GLOB sources ${PROJECT_SOURCE_DIR}/src/*.cc)
file(GLOB headers ${PROJECT_SOURCE_DIR}/include/*.hh)

#------------------------------------------------------------------------------#
#   Add the executable, and link it to the Geant4 libraries                    #
#------------------------------------------------------------------------------#
add_executable(muon muon.cc ${sources} ${headers})
target_link_libraries(muon ${Geant4_LIBRARIES} ${ROOT_LIBRARIES})
#target_link_libraries(muon ${Geant4_LIBRARIES})

#------------------------------------------------------------------------------#
#   Copy all scripts to the build directory, i.e. the directory in which we    #
# build beamtest2017. This is so that we can run the executable directly       #
# because it relies on these scripts being in the current working directory.   #
#------------------------------------------------------------------------------#
set(MUON_SCRIPTS
	README
	init_vis.mac
	vis.mac
	GetLifetime.C
)

foreach(_script ${MUON_SCRIPTS})
	configure_file(
		${PROJECT_SOURCE_DIR}/${_script}
		${PROJECT_BINARY_DIR}/${_script}
		COPYONLY
	)
endforeach()

#------------------------------------------------------------------------------#
#   For internal Geant4 use - but has no effect if you build this beamtest2017 #
# standalone                                                                   #
#------------------------------------------------------------------------------#
add_custom_target(MUON DEPENDS muon)

#------------------------------------------------------------------------------#
#   Install the executable to 'bin' directory under CMAKE_INSTALL_PREFIX       #
#------------------------------------------------------------------------------#
install(TARGETS muon DESTINATION bin)
