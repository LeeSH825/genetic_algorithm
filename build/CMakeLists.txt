# Project Environment
PROJECT( "GENE_ALGO" )
SET( PROJECT_VERSION_MAJOR 0 )
SET( PROJECT_VERSION_MINOR 1 )

# CMake Requirement
CMAKE_MINIMUM_REQUIRED( VERSION 3.22 )



# Project Configuration
SET( CMAKE_VERBOSE_MAKEFILE true )

# Build Files
SET( SRCS_DIR ../srcs )
SET( SRC_FILES
	${SRCS_DIR}/Chromosome.cpp
	${SRCS_DIR}/Gene_Pod.cpp
	${SRCS_DIR}/utils.cpp
	../new_main.cpp)

# Common Compiler Environment
SET( CMAKE_CXX_COMPILER "g++" )
SET( CMAKE_CXX_STANDARD 17 )
# ADD_COMPILE_OPTIONS( -std=c++17 )

# Common Header Files
INCLUDE_DIRECTORIES( include ../includes )

# Build Output Directory
SET( CMAKE_RUNTIME_OUTPUT_DIRECTORY output/bin )

# Build Target Binary
ADD_EXeCUTABLE( GENE_ALGO ${SRC_FILES} )