cmake_minimum_required(VERSION 3.1)

project(NZServer)

find_package(Boost COMPONENTS system filesystem log_setup log REQUIRED)
find_package(Lua REQUIRED)
find_package(Zlib REQUIRED)
find_package(PkgConfig REQUIRED)
pkg_search_module(SQLITE3 REQUIRED sqlite3)

add_definitions(-DBOOST_LOG_DYN_LINK)

include_directories(${LUA_INCLUDE_DIR})

file(GLOB HTTP_PARSER_SOURCES "http-parser/*.c") 
add_library(http-parser STATIC ${HTTP_PARSER_SOURCES})
target_include_directories(http-parser PUBLIC http-parser)

add_library(lua-intf INTERFACE)
target_include_directories(lua-intf INTERFACE lua-intf/LuaIntf)

file(GLOB_RECURSE NZSERVER_SOURCES "NZServer" "*.cpp" "*.h")

add_executable(nzserver ${NZSERVER_SOURCES})
target_link_libraries(nzserver 
	http-parser 
	lua-intf 
	${LUA_LIBRARY} 
	${Boost_LIBRARIES} 
	${SQLITE3_LIBRARIES} 
	${ZLIB_LIBRARIES})
target_compile_features(nzserver PRIVATE cxx_range_for)

source_group(db REGULAR_EXPRESSION "db/.*(h|cpp)")
source_group(handler REGULAR_EXPRESSION "handler/.*(h|cpp)")
source_group(network REGULAR_EXPRESSION "network/.*(h|cpp)")
source_group(service REGULAR_EXPRESSION "service/.*(h|cpp)")
source_group(template REGULAR_EXPRESSION "template/.*(h|cpp)")