#include <QtWidgets>
#include "DashboardPage.hpp"

int main(int argc, char* argv[])
{
  QApplication app(argc, argv);

  DashboardPage window;
  window.show();

  return app.exec();
}
