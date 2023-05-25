cmake_minimum_required (VERSION 3.10)

project(
	TDD_Exercise 
	VERSION 1.0
	DESCRIPTION "Some test projects to follow Grening's TDD Book"
	LANGUAGES C CXX
	)
						
include(FetchContent)

FetchContent_Declare(
	CppUTest
	GIT_REPOSITORY https://github.com/cpputest/cpputest
	GIT_TAG master
	)

FetchContent_MakeAvailable(CppUTest)
add_subdirectory(Application)
add_subdirectory(Source)
