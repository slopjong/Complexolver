#include <QtGui/QApplication>
#include "mainwindow.h"
#include <QDebug>
#include "tinyxml.h"
#include "tinystr.h"
#include <QtGui/QMessageBox>

bool isAtomarApply(TiXmlElement *node)
{
	for( TiXmlElement *element = node->FirstChildElement();
		 element;
		 element = element->NextSiblingElement() )
	{
		QString node_name = element->Value();
		if("apply"== node_name)
			return false;
	}

	return true;
}

bool isApplyNode(TiXmlNode *node){

	switch(node->Type()){
		case TiXmlNode::TINYXML_ELEMENT:	qDebug() << "Type: Element"; break;
		case TiXmlNode::TINYXML_TEXT:	qDebug() << "Type: Element"; break;
		default:
			qDebug() << "Type is unknown";
	}

	QString node_name = node->Value();
	if("apply"== node_name)
		return true;
	return false;
}

int compute(TiXmlNode *node)
{
	if(!node)
		qDebug() << "The node is null";

	// if the node is no apply node return the value
	if(!isApplyNode(node)){
		TiXmlNode *text = node->FirstChild();
		if(!text)
			return 0;

		QString t = node->FirstChild()->Value();
		return t.toInt();
	}

	if(isAtomarApply(node)){

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
						"      <cn>2</cn>"
						"      <cn>3</cn>"
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
						"  </apply>"
						"</math>";

	QByteArray mathml = _mathml0.toLocal8Bit();

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
		//TiXmlNode * math->FirstChild();// FirstChild("apply");
		//TiXmlElement *formula = math->FirstChild("apply")->ToElement();
		qDebug() << compute(math->FirstChild());
		/*
		if(formula)
			qDebug() << compute(formula);
		else
			// in this case math is a scalar
			qDebug() << compute(math);
		//*/
	}
}
