cmake_minimum_required(VERSION 3.15)

set(atx-logger_VERSION 1.0.0)

project(atx-logger
	VERSION ${atx-logger_VERSION}
	DESCRIPTION "A simple spdlog wrapper"
	HOMEPAGE_URL "https://dev.azure.com/AritexSoftware/AtxLogger"
	LANGUAGES CXX)
	
find_package(spdlog CONFIG REQUIRED)
	
include(CMakePackageConfigHelpers)
include(GNUInstallDirs)


set(CMAKE_CXX_STANDARD 14)

add_library(atx-logger SHARED 
	src/AtxLogger.cpp 
	src/AtxLoggerConf.cpp
	include/AtxLogger.h
	include/AtxLoggerConf.h)

	
target_include_directories(atx-logger
	PUBLIC
		$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
		$<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>)
		
target_link_libraries(atx-logger PRIVATE spdlog::spdlog)

configure_package_config_file(cmake/config.cmake.in
	${CMAKE_CURRENT_BINARY_DIR}/atx-logger-config.cmake
	INSTALL_DESTINATION ${CMAKE_INSTALL_DATADIR}/atx-logger
	NO_SET_AND_CHECK_MACRO)
write_basic_package_version_file(
	${CMAKE_CURRENT_BINARY_DIR}/atx-logger-config-version.cmake
	VERSION ${atx-logger_VERSION}
	COMPATIBILITY SameMajorVersion)
install(
	FILES
		${CMAKE_CURRENT_BINARY_DIR}/atx-logger-config.cmake
		${CMAKE_CURRENT_BINARY_DIR}/atx-logger-config-version.cmake
	DESTINATION
		${CMAKE_INSTALL_DATADIR}/atx-logger)
		
install(TARGETS atx-logger EXPORT atx-logger-targets)
install(DIRECTORY include/ DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})
install(EXPORT atx-logger-targets
	DESTINATION ${CMAKE_INSTALL_DATADIR}/atx-logger)
	
add_subdirectory(AtxLoggerTest)


