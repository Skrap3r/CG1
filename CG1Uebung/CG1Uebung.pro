QT       += core gui opengl widgets
TEMPLATE = app
TARGET = CgViewer
QMAKE_CXXFLAGS += -std=c++11
CONFIG += c++11

SOURCES += main.cpp \
    CgEvents/CgColorChangeEvent.cpp \
    CgEvents/CgRotationskoerperErstellenEvent.cpp \
    CgEvents/CgRotationskoerperNormalenEvent.cpp \
    CgEvents/CgSchritteAusfuehrenEvent.cpp \
    CgEvents/CgSchritteResetEvent.cpp \
    CgQtViewer/CGQtGLRenderWidget.cpp \
    CgQtViewer/CgQtGui.cpp \
    CgBase/CgObservable.cpp \
    CgEvents/CgMouseEvent.cpp \
    CgQtViewer/CgQtMainApplication.cpp \
    CgSceneGraph/CgDice.cpp \
    CgSceneGraph/CgPolyline.cpp \
    CgSceneGraph/CgRotation.cpp \
    CgSceneGraph/CgSceneControl.cpp \
    CgEvents/CgKeyEvent.cpp \
    CgSceneGraph/CgExampleTriangle.cpp \
    CgQtViewer/CgQtGlBufferObject.cpp \
    CgQtViewer/CgTrackball.cpp \
    CgEvents/CgWindowResizeEvent.cpp \
    CgEvents/CgLoadObjFileEvent.cpp \
    CgUtils/Calc.cpp \
    CgUtils/ObjLoader.cpp \
    CgEvents/CgTrackballEvent.cpp

HEADERS += \
    CgEvents/CgColorChangeEvent.h \
    CgEvents/CgRotationskoerperErstellenEvent.h \
    CgEvents/CgRotationskoerperNormalenEvent.h \
    CgEvents/CgSchritteAusfuehrenEvent.h \
    CgEvents/CgSchritteResetEvent.h \
    CgQtViewer/CgQtGLRenderWidget.h \
    CgQtViewer/CgQtGui.h \
    CgBase/CgObserver.h \
    CgBase/CgObservable.h \
    CgBase/CgBaseEvent.h \
    CgBase/CgEnums.h \
    CgEvents/CgMouseEvent.h \
    CgQtViewer/CgQtMainApplication.h \
    CgSceneGraph/CgDice.h \
    CgSceneGraph/CgPolyline.h \
    CgSceneGraph/CgRotation.h \
    CgSceneGraph/CgSceneControl.h \
    CgEvents/CgKeyEvent.h \
    CgBase/CgBaseRenderer.h \
    CgBase/CgBaseRenderableObject.h \
    CgSceneGraph/CgExampleTriangle.h \
    CgBase/CgBasePointCloud.h \
    CgBase/CgBaseTriangleMesh.h \
    CgBase/CgBasePolygonMesh.h \
    CgBase/CgBasePolyline.h \
    CgBase/CgBaseSceneControl.h \
    CgQtViewer/CgQtGlBufferObject.h \
    CgQtViewer/CgTrackball.h \
    CgEvents/CgWindowResizeEvent.h \
    CgEvents/CgLoadObjFileEvent.h \
    CgUtils/ObjLoader.h \
    CgBase/CgBaseImage.h \
    CgEvents/CgTrackballEvent.h

