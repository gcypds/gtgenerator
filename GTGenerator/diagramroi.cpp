#include "diagramroi.h"

DiagramROI::DiagramROI()
{
    label = "--NO LABEL--";
    labeled = false;
    removed = false;
	automatic = true;
    color = Qt::white;
}

void DiagramROI::setFrameId(const int &f) {
    frameId = f;
}

void DiagramROI::setIndex(const int &i) {
    index = i;
}

void DiagramROI::setWidth(const int &w) {
    width = w;
}

void DiagramROI::setHeight(const int &h) {
    height = h;
}

void DiagramROI::setTpx(const int &t) {
    tpx = t;
}

void DiagramROI::setTpy(const int &t) {
    tpy = t;
}

void DiagramROI::setBrx(const int &b) {
    brx = b;
}

void DiagramROI::setBry(const int &b) {
    bry = b;
}

void DiagramROI::setColor(const QColor &c) {
    color = c;
}

void DiagramROI::setLabel(const QString &l) {
    label = l;
}

void DiagramROI::setLabelId(const int &l) {
    labelId = l;
}

void DiagramROI::setLabeled(const bool &l) {
    labeled = l;
}

void DiagramROI::setRemoved(const bool &r) {
    removed = r;
}

void DiagramROI::setAutomatic(const bool &a) {
	automatic = a;
}



