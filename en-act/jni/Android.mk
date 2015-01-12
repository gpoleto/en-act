#LOCAL_PATH := $(call my-dir)
#include $(CLEAR_VARS)

###########################################################################################
#OPENCV_CAMERA_MODULES:=on
#OPENCV_INSTALL_MODULES:=on
#OPENCV_LIB_TYPE:=STATIC
#include /Users/user/Tihomir/OpenCV_gui/OpenCV-2.4-2.8-android-sdk/sdk/native/jni/OpenCV.mk

#LOCAL_SHARED_LIBRARIES := opencv_java

#include $(CLEAR_VARS)
###########################################################################################

### Inclusion of libjpeg-turbo (jpeg) library
#LOCAL_STATIC_LIBRARIES := jpeg
#LOCAL_MODULE := jpeg
#LOCAL_SRC_FILES := ../obj/local/armeabi/libjpeg.a
#LOCAL_SRC_FILES += ../obj/local/armeabi-v7a/libjpeg.a
#include $(PREBUILT_STATIC_LIBRAY)



#include $(CLEAR_VARS)

LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)
#LOCAL_C_INCLUDES := $(LOCAL_PATH)
#$(warning In 'Enact_1 || LOCAL_PATH': $(LOCAL_PATH))

LOCAL_MODULE    := operations
LOCAL_SRC_FILES := operations.cpp					
LOCAL_LDLIBS += -llog -lz -ljnigraphics
#LOCAL_STATIC_LIBRARIES += libjpeg
#-llibjpeg-turbo
#LOCAL_LDFLAGS += -ljpeg
#LOCAL_CFLAGS += "-I/Users/user/Tihomir/CPP_libs/CImg/"
#LOCAL_CFLAGS += "-I/opt/local/include/"
#LOCAL_CFLAGS += "-I/opt/local/include/ImageMagick-6/"
LOCAL_CFLAGS += "-I/Users/user/Tihomir/CPP_libs/boost_1_55_0/"
#LOCAL_CFLAGS += "-I/Users/user/Tihomir/CPP_libs/libjpeg-turbo/"
LOCAL_CFLAGS += "-fomit-frame-pointer"
#LOCAL_CFLAGS += "-march=native"
#LOCAL_CFLAGS += "-mfpmath=sse" 
#LOCAL_CFLAGS += "-msse2"
#LOCAL_CFLAGS += "-fopenmp"
LOCAL_CFLAGS += "-lpthread"
LOCAL_CFLAGS += "-pthread"
#LOCAL_CFLAGS += "-lMagick++"
#LOCAL_CFLAGS += "-lMagickWand"
#LOCAL_CFLAGS += "-lMagickCore"

#LOCAL_CFLAGS += "-D_GNU_SOURCE"
#LOCAL_CPPFLAGS += -std=gnu++11 -O3

#LOCAL_STATIC_LIBRARIES := jpeg

include $(BUILD_SHARED_LIBRARY)
