#include <QDir>
#include "settings.h"

QString Settings::customOutputFolder = "";
bool Settings::useCustomOutputFolder = false;
QString Settings::defaultCustomOutputFolder = QDir::home().absolutePath();
