cmake_minimum_required(VERSION 3.20)
project(autod_ext)

include("${CMAKE_CURRENT_LIST_DIR}/sdk.cmake")

file(GLOB_RECURSE srcs LIST_DIRECTORIES false CONFIGURE_DEPENDS
	"${CMAKE_CURRENT_LIST_DIR}/cpp/*.cpp"
)
add_library(autod_ext SHARED ${srcs})
make_arx(autod_ext)