#ifndef DIAGRAMROILABEL_H
#define DIAGRAMROILABEL_H

#include <QColor>

class DiagramROILabel
{

public:
    DiagramROILabel();

    int getId() const { return id; }
    void setId(const int &i);

	QString getName() const { return name; }
    void setName(const QString &n);
    
    QColor getColor() const { return color; }
    void setColor(const QColor &c);

	bool isRemoved() const { return removed; }
    void setRemoved(const bool &r);

private:
    int id;
    QString name;
    QColor color;
	bool removed;
};

#endif // DIAGRAMROILABEL_H
