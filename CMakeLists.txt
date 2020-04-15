#
# CMake configuration for LCDD library.
#
# @author Jeremy McCormick <jeremym@slac.stanford.edu>
#

# minimum cmake version
CMAKE_MINIMUM_REQUIRED( VERSION 2.8 )

# project name
PROJECT( LCDD )

# project version
SET( LCDD_VERSION_MAJOR 5 )
SET( LCDD_VERSION_MINOR 0 )
SET( LCDD_VERSION_PATCH 0 )

# add path containing CMake macros for this project
LIST( APPEND CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake )

# find Xerces C++
FIND_PACKAGE( XercesC REQUIRED )
IF( NOT XercesC_FOUND )
	MESSAGE( FATAL_ERROR "XercesC was not found!  Define XercesC_INCLUDE_DIR and XercesC_LIBRARY when calling cmake." )
ENDIF()

# find Geant4
FIND_PACKAGE(Geant4 REQUIRED)
if ( NOT Geant4_FOUND )
    MESSAGE( FATAL_ERROR "Geant4 was not found!  Define Geant4_DIR when calling cmake." )
ELSE()
    MESSAGE( STATUS "Found Geant4: ${Geant4_DIR}" )
ENDIF()

# find GDML
FIND_PACKAGE(GDML REQUIRED)
if ( NOT GDML_FOUND )
    MESSAGE( FATAL_ERROR "Geant4 was not found!  Define GDML_DIR when calling cmake." )
ELSE()
    MESSAGE( STATUS "Found GDML: ${GDML_DIR}" )
ENDIF()

# local includes
SET( LCDD_INCLUDE_DIR ${PROJECT_SOURCE_DIR}/include )
INCLUDE_DIRECTORIES( ${LCDD_INCLUDE_DIR} )

# get list of LCDD sources
FILE( GLOB_RECURSE library_sources ${PROJECT_SOURCE_DIR}/src/*.cc )

# additional compilation flags
ADD_DEFINITIONS(${Geant4_DEFINITIONS})

# include directories
INCLUDE_DIRECTORIES( ${XercesC_INCLUDE_DIR} ${Geant4_INCLUDE_DIRS} ${GDML_INCLUDE_DIR} )

# add GDML link directory
LINK_DIRECTORIES( ${GDML_LIBRARY_DIR} )

# libraries
LINK_LIBRARIES( ${XercesC_LIBRARY} ${Geant4_LIBRARIES} ${GDML_LIBRARY} )

# output shared library
ADD_LIBRARY( lcdd SHARED ${library_sources} )

# install library
SET( LCDD_LIB_INSTALL_DIR ${CMAKE_INSTALL_PREFIX}/lib )
INSTALL( TARGETS lcdd DESTINATION ${CMAKE_INSTALL_PREFIX}/lib )

# install header files
INSTALL( DIRECTORY ${LCDD_INCLUDE_DIR}/lcdd/ DESTINATION include/lcdd/ )

# install XML schemas to a single directory
INSTALL( DIRECTORY schemas/ DESTINATION ${CMAKE_INSTALL_PREFIX}/share/schemas FILES_MATCHING PATTERN "*.xsd")

# configure and output documentation using doxygen
OPTION( INSTALL_DOC "Set to OFF to skip build/install documentation" ON ) 
IF ( INSTALL_DOC )
    
    # find doxygen
    FIND_PROGRAM( DOXYGEN_EXECUTABLE doxygen ${PATH} )
    IF ( DOXYGEN_EXECUTABLE-NOTFOUND )
        MESSAGE( FATAL_ERROR "The doxygen executable was not found." )
    ENDIF()
    
    # find dot
    FIND_PROGRAM( DOT_EXECUTABLE dot ${PATH} )
    IF ( DOT_EXECUTABLE-NOTFOUND )
        MESSAGE( FATAL_ERROR "The dot executable was not found." )
    ENDIF()
    
    # configure doxygen output
    MESSAGE( STATUS "Configuring doxygen input file" )
    CONFIGURE_FILE( ${PROJECT_SOURCE_DIR}/config/doxygen/lcdd_doxygen.cfg.in ${PROJECT_SOURCE_DIR}/config/doxygen/lcdd_doxygen.cfg )
    
    # add doxygen documentation to install step
    INSTALL( CODE "EXECUTE_PROCESS( COMMAND doxygen ${PROJECT_SOURCE_DIR}/config/doxygen/lcdd_doxygen.cfg)" )
    
ELSE() 
    # message that documentation is off for this build
    MESSAGE( STATUS "INSTALL_DOC is set to OFF.  Documentation will not be created." ) 
ENDIF()                                            
