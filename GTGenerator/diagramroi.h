#ifndef DIAGRAMROI_H
#define DIAGRAMROI_H

#include <QColor>

class DiagramROI
{

public:
    DiagramROI();

	int getFrameId() const { return frameId; }
    void setFrameId(const int &f);

    int getIndex() const { return index; }
    void setIndex(const int &i);

    int getWidth() const { return width; }
    void setWidth(const int &w);

    int getHeight() const { return height; }
    void setHeight(const int &h);

    int getTpx() const { return tpx; }
    void setTpx(const int &t);

    int getTpy() const { return tpy; }
    void setTpy(const int &t);

    int getBrx() const { return brx; }
    void setBrx(const int &b);

    int getBry() const { return bry; }
    void setBry(const int &b);

    QColor getColor() const { return color; }
    void setColor(const QColor &c);

    QString getLabel() const { return label; }
    void setLabel(const QString &l);

	int getLabelId() const { return labelId; }
    void setLabelId(const int &f);

    bool isLabeled() const { return labeled; }
    void setLabeled(const bool &l);

    bool isRemoved() const { return removed; }
    void setRemoved(const bool &r);

	bool isAutomatic() const { return automatic; }
    void setAutomatic(const bool &a);

private:
	int frameId;
    int index;
    int width;
    int height;
    int tpx;
    int tpy;
    int brx;
    int bry;
    QColor color;
    QString label;
	int labelId;
    bool labeled;
    bool removed;
	bool automatic;
};

#endif // DIAGRAMROI_H
