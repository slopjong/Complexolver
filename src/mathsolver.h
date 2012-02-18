#ifndef MATHSOLVER_H
#define MATHSOLVER_H

#include <QtCore/QString>
#include "tinyxml.h"
#include "tinystr.h"

class MathSolver
{
public:
	MathSolver();
	static double compute(QString mathml);

private:
	static double _compute(TiXmlNode *node);
};

#endif // MATHSOLVER_H
