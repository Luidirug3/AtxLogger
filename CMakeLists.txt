cmake_minimum_required(VERSION 3.15)

set(atx-logger_VERSION 1.0.0)

project(AtxLogger
	VERSION ${AtxLogger_VERSION}
	DESCRIPTION "A simple spdlog wrapper"
	HOMEPAGE_URL "https://dev.azure.com/AritexSoftware/AtxLogger"
	LANGUAGES CXX)
	
find_package(spdlog CONFIG REQUIRED)
	
include(CMakePackageConfigHelpers)
include(GNUInstallDirs)


set(CMAKE_CXX_STANDARD 14)

add_library(AtxLogger SHARED 
	src/AtxLogger.cpp 
	src/AtxLoggerConf.cpp
	include/AtxLogger.h
	include/AtxLoggerConf.h)

	
target_include_directories(AtxLogger
	PUBLIC
		$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
		$<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>)
		
target_link_libraries(AtxLogger PRIVATE spdlog::spdlog)

configure_package_config_file(cmake/config.cmake.in
	${CMAKE_CURRENT_BINARY_DIR}/AtxLogger-config.cmake
	INSTALL_DESTINATION ${CMAKE_INSTALL_DATADIR}/AtxLogger
	NO_SET_AND_CHECK_MACRO)
write_basic_package_version_file(
	${CMAKE_CURRENT_BINARY_DIR}/AtxLogger-config-version.cmake
	VERSION ${AtxLogger_VERSION}
	COMPATIBILITY SameMajorVersion)
install(
	FILES
		${CMAKE_CURRENT_BINARY_DIR}/AtxLogger-config.cmake
		${CMAKE_CURRENT_BINARY_DIR}/AtxLogger-config-version.cmake
	DESTINATION
		${CMAKE_INSTALL_DATADIR}/AtxLogger)
		
install(TARGETS AtxLogger EXPORT AtxLogger-targets)
install(DIRECTORY include/ DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})
install(EXPORT AtxLogger-targets
	DESTINATION ${CMAKE_INSTALL_DATADIR}/AtxLogger)
	
add_subdirectory(AtxLoggerTest)


