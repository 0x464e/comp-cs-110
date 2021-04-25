#include "find_dialog.hh"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    find_dialog w;
    w.show();
    return a.exec();
}
