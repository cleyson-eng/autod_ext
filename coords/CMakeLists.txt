file(GLOB_RECURSE srcs LIST_DIRECTORIES false CONFIGURE_DEPENDS
	"${CMAKE_CURRENT_LIST_DIR}/cpp/*.cpp"
)
add_library(coords SHARED ${srcs})
make_arx(coords)