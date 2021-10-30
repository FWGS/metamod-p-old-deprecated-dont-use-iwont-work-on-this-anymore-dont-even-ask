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

LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

include $(MM_CONFIG)

LOCAL_MODULE := metamod

LOCAL_C_INCLUDES += \
	$(LOCAL_PATH)/../hlsdk/dlls \
	$(LOCAL_PATH)/../hlsdk/public \
	$(LOCAL_PATH)/../hlsdk/common \
	$(LOCAL_PATH)/../hlsdk/engine \
	$(LOCAL_PATH)/../hlsdk/pm_shared \
	$(LOCAL_PATH)/

LOCAL_CFLAGS += -DXASH_DLSYM_META -DOPT_TYPE="\"optimized+meta_debug-disabled\"" -D__INTERNALS_USE_REGPARAMS__ -D__METAMOD_BUILD__ -Dlinux

LOCAL_SRC_FILES := \
	api_hook.cpp api_info.cpp commands_meta.cpp conf_meta.cpp \
        dllapi.cpp engine_api.cpp engineinfo.cpp game_support.cpp \
        game_autodetect.cpp h_export.cpp linkgame.cpp linkplug.cpp \
        log_meta.cpp meta_eiface.cpp metamod.cpp mlist.cpp mplayer.cpp \
        mplugin.cpp mqueue.cpp mreg.cpp mutil.cpp osdep.cpp \
        osdep_p.cpp reg_support.cpp sdk_util.cpp studioapi.cpp \
        support_meta.cpp thread_logparse.cpp vdate.cpp osdep_linkent_xash.cpp

LOCAL_LDLIBS += -llog
        
include $(BUILD_SHARED_LIBRARY)
