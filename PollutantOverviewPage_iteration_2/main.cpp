#include <QApplication>
#include "PollutantOverviewPage.hpp"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    PollutantOverviewPage window;
    window.show();
    return app.exec();
}