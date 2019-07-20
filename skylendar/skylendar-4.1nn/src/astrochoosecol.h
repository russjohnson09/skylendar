#ifndef ASTROCHOOSECOL
#define ASTROCHOOSECOL

#include <QPushButton>
#include <QColor>

class AstroChooseCol : public QPushButton
{
	Q_OBJECT

 public:

	AstroChooseCol(QWidget* parent);

	inline void SetColor(const QColor& c) { Col = c; }

	inline QColor& GetColor() { return Col; }

 signals:

		void ChangeColor(const QColor&);

	public slots:
		
		void Clicked();

 private:

	QColor Col;
};

#endif
