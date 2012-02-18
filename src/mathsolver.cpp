#include "mathsolver.h"
#include <QDebug>
#include <QtGui/QMessageBox>
#include <qmath.h>

MathSolver::MathSolver()
{
}

double MathSolver::compute(QString mathml)
{
	QByteArray _mathml = mathml.toLocal8Bit();

	TiXmlDocument doc;
	doc.Parse(_mathml.constData());

	if(doc.Error()){
		QMessageBox msgBox;
		msgBox.setText("The service file could not be loaded.");
		msgBox.exec();
		qDebug() << "Error message:" << QString::fromLocal8Bit(doc.ErrorDesc());
		return 1;
	}

	TiXmlHandle docHandle( &doc );

	TiXmlNode *math = docHandle.FirstChild("math").ToNode();
	if(!math){
		qDebug() << "There is no mathematics";
	}
	else{
		qDebug() << MathSolver::_compute(math);
	}
}

double MathSolver::_compute(TiXmlNode *node)
{
	if(!node)
		qDebug() << "The node is null";

	TiXmlNode *child = node->FirstChild();

	QString type = child->Value();
	qDebug() << "The node type is:" << type;

	/********************************************************/
	// if numerical type, return the scalar

	if("cn" == type){
		TiXmlNode *text = child->FirstChild();
		if(!text)
			return 0;

		QString t = child->FirstChild()->Value();
		return t.toDouble();
	}
	// TODO: make the regex available somewhere else to reduce
	// avoid multiple object creation
	QRegExp re("^[0-9]+\.?[0-9]*");
	if(type.contains(re))
		return type.toDouble(); // in this case type is the scalar

	/********************************************************/
	// if function, process it

	if("apply" == type){
		return MathSolver::_compute(child);
	}

	/********************************************************/

	if("power" == type){
		double base = _compute(child->NextSibling());
		double exp = _compute(child->NextSibling()->NextSibling());
		return qPow(base, exp);
	}

	// can process as many arguments as possible
	if("plus" == type){
		double sum = 0;
		for(TiXmlNode *summand=child->NextSibling();
			summand; summand=summand->NextSibling())
		{
			sum += MathSolver::_compute(summand);
		}

		return sum;
	}

	// can process as many arguments as possible
	if("times" == type){
		double multiplication = 1;
		for(TiXmlNode *multarg=child->NextSibling();
			multarg; multarg=multarg->NextSibling())
		{
			multiplication *= MathSolver::_compute(multarg);
		}

		return multiplication;
	}

	return 0;
}
