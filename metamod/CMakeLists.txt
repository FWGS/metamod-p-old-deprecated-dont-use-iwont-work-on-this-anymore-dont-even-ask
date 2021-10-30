# MetaMod makefile
# Copyright (c) 2001-2003 Will Day <willday@hpgx.net>
#
# based on the Valve SDK 2.1 Makefile as well as the Makefile
# in adminmod by Alfred Reynolds.
#
# From SDK 2.1 dlls/Makefile:
#! Half-Life StandardSDK 2.0 mp_i386.so Makefile for i386 Linux
#! April 2000 by Leon Hartwig (jehannum@planethalflife.com)
# 
# AMXXOnAndroid
# Copyright (C) 2017 a1batross

cmake_minimum_required(VERSION 2.6.0)
project(metamod)

include_directories( ../hlsdk/dlls
	../hlsdk/public
	../hlsdk/common
	../hlsdk/engine
	../hlsdk/pm_shared
	. )

add_definitions( -DXASH_DLSYM_META -DOPT_TYPE="\"\"optimized+meta_debug-disabled\"\"" -D__METAMOD_BUILD__ -Dlinux )

add_library(metamod SHARED
	api_hook.cpp api_info.cpp commands_meta.cpp conf_meta.cpp 
        dllapi.cpp engine_api.cpp engineinfo.cpp game_support.cpp 
        game_autodetect.cpp h_export.cpp linkgame.cpp linkplug.cpp 
        log_meta.cpp meta_eiface.cpp metamod.cpp mlist.cpp mplayer.cpp 
        mplugin.cpp mqueue.cpp mreg.cpp mutil.cpp osdep.cpp 
        osdep_p.cpp reg_support.cpp sdk_util.cpp studioapi.cpp 
        support_meta.cpp thread_logparse.cpp vdate.cpp osdep_linkent_xash.cpp )

target_link_libraries(metamod ${CMAKE_DL_LIBS})
set_target_properties(metamod PROPERTIES
	POSITION_INDEPENDENT_CODE 1
	OUTPUT_NAME "metamod_${TARGET_ARCHITECTURE}" PREFIX "")

install(TARGETS metamod
	DESTINATION /addons/metamod/dlls/
	PERMISSIONS OWNER_READ OWNER_WRITE OWNER_EXECUTE
	    GROUP_READ GROUP_EXECUTE
		WORLD_READ WORLD_EXECUTE)
