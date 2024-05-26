#include <QApplication>
#include "app/window.h" // Заголовковий файл розробленого застосунку

int main(int argc, char *argv[]) {
    // Об'єкт QApplication, який керує потоком виконання програми
    QApplication app(argc, argv);
    // Створення вікна програми
    Window window;
    // Відображення вікна програми
    window.show();
    // Запуск обробки подій програми
    return app.exec();
}