#include <QDebug>
#include <QStringList>
#include "mathsolver.h"

int main(int argc, char *argv[])
{
	QStringList list;

	list	<<	"<math xmlns=\"http://www.w3.org/1998/Math/MathML\">"
				"  <cn>2</cn>"
				"</math>"

			<<	"<math xmlns=\"http://www.w3.org/1998/Math/MathML\">"
				"  <apply>"
				"    <power/>"
				"      <cn>2.1</cn>"
				"      <cn>3.3</cn>"
				"  </apply>"
				"</math>"

			<<	"<math xmlns=\"http://www.w3.org/1998/Math/MathML\">"
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
				"</math>"

			<<	"<math xmlns=\"http://www.w3.org/1998/Math/MathML\">"
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
				"</math>"
		;

	QString example;
	foreach(example, list){
		qDebug() << MathSolver::compute(example);
		qDebug() << "============================";
	}

	return 0;
}
