QT       += core gui printsupport

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    ../model_object.cpp \
    ../model.cpp \
    ../controller.cpp \
    ../credit_calc/credit_model.cpp \
    ../credit_calc/credit_controller.cpp \
    credit_calc.cpp \
    main.cpp \
    qcustomplot.cpp \
    s21_plot_print.cpp \
    s21_smart_calc_mw.cpp

HEADERS += \
    ../model_object.h \
    ../model.h \
    ../controller.h \
    ../credit_calc/credit_model.h \
    ../credit_calc/credit_controller.h \
    credit_calc.h \
    qcustomplot.h \
    s21_plot_print.h \
    s21_smart_calc_mw.h


FORMS += \
    credit_calc.ui \
    s21_plot_print.ui \
    s21_smart_calc_mw.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
