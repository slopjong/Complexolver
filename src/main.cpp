#include <QtGui/QApplication>
#include "mainwindow.h"
#include <QDebug>
#include "tinyxml.h"
#include "tinystr.h"
#include <QtGui/QMessageBox>
#include <qmath.h>

double compute(TiXmlNode *node)
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
		return compute(child);
	}

	/********************************************************/

	if("power" == type){
		double base = compute(child->NextSibling());
		double exp = compute(child->NextSibling()->NextSibling());
		return qPow(base, exp);
	}

	// can process as many arguments as possible
	if("plus" == type){
		double sum = 0;
		for(TiXmlNode *summand=child->NextSibling();
			summand; summand=summand->NextSibling())
		{
			sum += compute(summand);
		}

		return sum;
	}

	// can process as many arguments as possible
	if("times" == type){
		double multiplication = 1;
		for(TiXmlNode *multarg=child->NextSibling();
			multarg; multarg=multarg->NextSibling())
		{
			multiplication *= compute(multarg);
		}

		return multiplication;
	}

	return 0;
}

int main(int argc, char *argv[])
{
	/*
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
	//*/

	QString _mathml0 =	"<math xmlns=\"http://www.w3.org/1998/Math/MathML\">"
						"  <cn>2</cn>"
						"</math>";

	QString _mathml1 =	"<math xmlns=\"http://www.w3.org/1998/Math/MathML\">"
						"  <apply>"
						"    <power/>"
						"      <cn>2.1</cn>"
						"      <cn>3.3</cn>"
						"  </apply>"
						"</math>";

	QString _mathml2 =	"<math xmlns=\"http://www.w3.org/1998/Math/MathML\">"
						"  <apply>"
						"    <plus/>"
						"    <apply>"
						"      <power/>"
						"      <cn>2</cn>"
						"      <cn>3</cn>"
						"    </apply>"
						"    <cn>5</cn>"
						"    <cn>1</cn>"
						"  </apply>"
						"</math>";

	QString _mathml3 =	"<math xmlns=\"http://www.w3.org/1998/Math/MathML\">"
						"  <apply>"
						"    <plus/>"
						"    <apply>"
						"      <power/>"
						"      <cn>2</cn>"
						"      <cn>3</cn>"
						"    </apply>"
						"    <apply>"
						"      <times/>"
						"      <cn>5</cn>"
						"      <cn>2</cn>"
						"      <cn>3</cn>"
						"    </apply>"
						"  </apply>"
						"</math>";

	QByteArray mathml = _mathml3.toLocal8Bit();

	TiXmlDocument doc;
	doc.Parse(mathml.constData());

	if(doc.Error()){
		//QMessageBox msgBox;
		//msgBox.setText("The service file could not be loaded.");
		//msgBox.exec();
		qDebug() << "Error message:" << QString::fromLocal8Bit(doc.ErrorDesc());
		return 1;
	}

	TiXmlHandle docHandle( &doc );

	TiXmlNode *math = docHandle.FirstChild("math").ToNode();
	if(!math){
		qDebug() << "There is no mathematics";
	}
	else{
		qDebug() << compute(math);
	}
}
