
win32: {
    DEFINES+=_CRT_SECURE_NO_WARNINGS
    QMAKE_CXXFLAGS+=/wd"4819"

    # for OpenCV
    INCLUDEPATH += $$PWD/include
    DEPENDPATH += $$PWD/include                     #  不知为何！ 这里不起作用
    LIBS += -L$$PWD/x64/vc15/bin                    # for run
    LIBS += -L$$PWD/x64/vc15/lib                    # for link

    LIBS += -lopencv_world411
}

android: {
    QT += androidextras

    ANDROID_OPENCV = $$PWD/android-sdk-native

    INCLUDEPATH += $$ANDROID_OPENCV/jni/include

    # Only supported abi-v7a for now
    contains(ANDROID_TARGET_ARCH,armeabi-v7a) {
        ANDROID_OPENCV_LIBS = $$ANDROID_OPENCV/libs/armeabi-v7a
        ANDROID_OPENCV_DEPS = $$ANDROID_OPENCV/3rdparty/libs/armeabi-v7a

        ANDROID_EXTRA_LIBS += $$ANDROID_OPENCV_LIBS/libopencv_java3.so
    }

    contains(ANDROID_TARGET_ARCH,x86) {
        message("OPENCV android x86 ...")

        ANDROID_OPENCV_LIBS = $$ANDROID_OPENCV/libs/x86
        ANDROID_OPENCV_DEPS = $$ANDROID_OPENCV/3rdparty/libs/x86

        ANDROID_EXTRA_LIBS += $$ANDROID_OPENCV_LIBS/libopencv_java3.so
    }

    LIBS += -L$$ANDROID_OPENCV_LIBS -L$$ANDROID_OPENCV_DEPS

    LIBS += -lopencv_java3 -lopencv_core -lopencv_imgproc -lopencv_imgcodecs
    LIBS += -lopencv_objdetect -lopencv_dnn

    LIBS += -llibjpeg -ltbb

}

