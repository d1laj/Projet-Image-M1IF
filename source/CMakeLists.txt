PROJECT(Helloworld)
#Required in DGtal

CMAKE_MINIMUM_REQUIRED(VERSION 2.6)

### We need Boost Program Options library
SET(Boost_USE_STATIC_LIBS   ON)
SET(Boost_USE_MULTITHREADED ON)
SET(Boost_USE_STATIC_RUNTIME OFF)
SET(Boost_FOUND FALSE)
set(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR})
FIND_PACKAGE(Armadillo REQUIRED)
FIND_PACKAGE(Mlpack REQUIRED)
FIND_PACKAGE(Boost 1.46.0 REQUIRED COMPONENTS program_options)
if ( Boost_FOUND )
  message(STATUS "Boost and boost_program_options found.")
  include_directories( ${Boost_INCLUDE_DIRS} )
 endif( Boost_FOUND )

include_directories(${MLPACK_INCLUDE_DIR}) 


FIND_PACKAGE(DGtal REQUIRED)
INCLUDE_DIRECTORIES(${DGTAL_INCLUDE_DIRS})
LINK_DIRECTORIES(${DGTAL_LIBRARY_DIRS})

file(GLOB SOURCES "*.cpp")

SET(SRCs
  ProjetImage)


#FOREACH(FILE ${SRCs})
##  add_executable(${FILE} ${FILE} ${SOURCES})
#  target_link_libraries (${FILE} ${DGTAL_LIBRARIES}  ${Boost_LIBRAIRIES}  ${Boost_PROGRAM_OPTIONS_LIBRARY})
#ENDFOREACH(FILE)

add_executable(projet_image ${SOURCES})
target_link_libraries (projet_image ${DGTAL_LIBRARIES}  ${Boost_LIBRAIRIES}  ${Boost_PROGRAM_OPTIONS_LIBRARY} ${Mlpack_LIBRARIES} ${Armadillo_LIBRARIES})
