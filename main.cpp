#include <QApplication>
#include "mainguiwindow.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    MainGUIWindow window;
    window.show();

    return app.exec();
}
