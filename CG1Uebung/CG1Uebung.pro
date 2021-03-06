QT       += core gui opengl widgets
TEMPLATE = app
TARGET = CgViewer
QMAKE_CXXFLAGS += -std=c++11
CONFIG += c++11

SOURCES += main.cpp \
    CgBase/CgBaseRenderableObject.cpp \
    CgEvents/CgColorChangeEvent.cpp \
    CgEvents/CgLokKoordZeichnenEvent.cpp \
    CgEvents/CgRotationskoerperErstellenEvent.cpp \
    CgEvents/CgRotationskoerperNormalenEvent.cpp \
    CgEvents/CgSchritteAusfuehrenEvent.cpp \
    CgEvents/CgSchritteResetEvent.cpp \
    CgEvents/CgTransaltionAusfuerenEvent.cpp \
    CgQtViewer/CGQtGLRenderWidget.cpp \
    CgQtViewer/CgQtGui.cpp \
    CgBase/CgObservable.cpp \
    CgEvents/CgMouseEvent.cpp \
    CgQtViewer/CgQtMainApplication.cpp \
    CgSceneGraph/CgAppearance.cpp \
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
    CgSceneGraph/CgSceneGraphEntity.cpp \
    CgSceneGraph/CgScenegraph.cpp \
    CgUtils/ObjLoader.cpp \
    CgEvents/CgTrackballEvent.cpp

HEADERS += \
    CgEvents/CgColorChangeEvent.h \
    CgEvents/CgLokKoordZeichnenEvent.h \
    CgEvents/CgRotationskoerperErstellenEvent.h \
    CgEvents/CgRotationskoerperNormalenEvent.h \
    CgEvents/CgSchritteAusfuehrenEvent.h \
    CgEvents/CgSchritteResetEvent.h \
    CgEvents/CgTransaltionAusfuerenEvent.h \
    CgQtViewer/CgQtGLRenderWidget.h \
    CgQtViewer/CgQtGui.h \
    CgBase/CgObserver.h \
    CgBase/CgObservable.h \
    CgBase/CgBaseEvent.h \
    CgBase/CgEnums.h \
    CgEvents/CgMouseEvent.h \
    CgQtViewer/CgQtMainApplication.h \
    CgSceneGraph/CgAppearance.h \
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
    CgSceneGraph/CgSceneGraphEntity.h \
    CgSceneGraph/CgScenegraph.h \
    CgUtils/ObjLoader.h \
    CgBase/CgBaseImage.h \
    CgEvents/CgTrackballEvent.h

