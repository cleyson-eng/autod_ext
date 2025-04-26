#temporary ...
set(ENV{OBJECT_ARX_SDK} "X:/system_windows/etc/autodesk_obj_arx/arx25")

add_library(object_arx INTERFACE EXCLUDE_FROM_ALL)
target_include_directories(object_arx INTERFACE
	"$ENV{OBJECT_ARX_SDK}/inc"
	"$ENV{OBJECT_ARX_SDK}/inc-x64"
)
target_link_directories(object_arx INTERFACE
	"$ENV{OBJECT_ARX_SDK}/lib-x64"
)
file(GLOB object_arx_libs LIST_DIRECTORIES false CONFIGURE_DEPENDS
	RELATIVE "$ENV{OBJECT_ARX_SDK}/lib-x64"
	"$ENV{OBJECT_ARX_SDK}/lib-x64/*.lib"
)
target_link_libraries(object_arx INTERFACE ${object_arx_libs})
target_compile_options(object_arx INTERFACE
    /EHsc
    /Zc:wchar_t
    /W3
	/GR
	/GF
	/Gm-
	/RTCc
	/Gy
	/MD
)
target_compile_definitions(object_arx INTERFACE
	RADPACK
	_ALLOW_RTCc_IN_STL
)
#set(CMAKE_SHARED_LINKER_FLAGS "${CMAKE_SHARED_LINKER_FLAGS} /SUBSYSTEM:WINDOWS")
macro(make_arx lib)
	set_target_properties(${lib} PROPERTIES
		SUFFIX ".arx" PREFIX ""
		LINK_FLAGS "/DEF:\"$ENV{OBJECT_ARX_SDK}/inc/AcRxDefault.def\""
	)
	target_link_libraries(${lib} PUBLIC object_arx)
endmacro()