#include "gtglobalwidgets.h"

GTGlobalWidgets* GTGlobalWidgets::_instance = 0;

GTGlobalWidgets::GTGlobalWidgets() {
}

GTGlobalWidgets* GTGlobalWidgets::Instance() {
    if(!_instance)
        _instance = new GTGlobalWidgets;

    return _instance;
}