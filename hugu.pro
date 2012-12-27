SOURCES += hugu.cxx
HEADERS += usagi/sensors.hxx \
    qml_hugu.hxx

OTHER_FILES += \
  hugu.qml \
  hugu_img.png \
  hugu_img2.png \

resources += \
  hugu.qml \
  hugu_img.png \
  hugu_img2.png \

QMAKE_POST_LINK = @ 
for(t, resources) {
  QMAKE_POST_LINK += ln -sv $$PWD/$$t $$OUT_PWD/$$t ;
}
QMAKE_CLEAN += $$resources

QT += \
  core \
  declarative \

QMAKE_CXXFLAGS += -std=c++11
QMAKE_LIBS += -lsensors
