SOURCES   = adddialog.cpp \
            addresswidget.cpp \
            main.cpp \
            mainwindow.cpp \
            newaddresstab.cpp \
            tablemodel.cpp
HEADERS   = adddialog.h \
            addresswidget.h \
            mainwindow.h \
            newaddresstab.h \
            tablemodel.h

# install
target.path = $$[QT_INSTALL_EXAMPLES]/itemviews/addressbook
sources.files = $$SOURCES $$HEADERS $$RESOURCES addressbook.pro
sources.path = $$[QT_INSTALL_EXAMPLES]/itemviews/addressbook
INSTALLS += target sources
