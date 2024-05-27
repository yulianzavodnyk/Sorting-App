#include <QApplication>
#include "app/window.h"     // Header file of the developed application

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);    // QApplication object, which manages the application's execution flow
    Window window;                      // Creating the application object
    window.show();                      // Displaying the application window
    return app.exec();                  // Starting the event processing loop of the application
}