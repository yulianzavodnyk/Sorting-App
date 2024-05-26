#include <QApplication>
#include "app/sorts/sorts.h"
#include "app/window.h"

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    Window window;
    window.show();
    return app.exec();
}