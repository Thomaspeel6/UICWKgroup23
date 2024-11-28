#include <QtWidgets>
#include "ComplianceDashboardPage.hpp"

int main(int argc, char* argv[])
{
  QApplication app(argc, argv);

  ComplianceDashboardPage window;
  window.show();

  return app.exec();
}
