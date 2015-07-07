#include "diagramroilabel.h"

DiagramROILabel::DiagramROILabel()
{
	id = 0;
	name = "--NO LABEL--";
    color = Qt::white;
}

void DiagramROILabel::setId(const int &i) {
    id = i;
}

void DiagramROILabel::setName(const QString &n) {
    name = n;
}

void DiagramROILabel::setColor(const QColor &c) {
    color = c;
}

void DiagramROILabel::setRemoved(const bool &r) {
	removed = r;
}