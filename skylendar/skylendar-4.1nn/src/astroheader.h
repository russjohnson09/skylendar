#ifndef ASTROHEADER_H
#define ASTROHEADER_H

#include <QWidget>
class QGridLayout;
class QString;

class AstroHeader: public QWidget
{
public:

    AstroHeader(QWidget* parent);

    void Add(const QString& qs, int length, bool textlength = false);
private:

    //QGridLayout* Qgl;
    int Xi;

};

#endif
