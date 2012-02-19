#include <QDebug>
#include "mathsolver.h"

int main(int argc, char *argv[])
{
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

	qDebug() << MathSolver::compute(_mathml0);
	qDebug() << "============================";
	qDebug() << MathSolver::compute(_mathml1);
	qDebug() << "============================";
	qDebug() << MathSolver::compute(_mathml2);
	qDebug() << "============================";
	qDebug() << MathSolver::compute(_mathml3);

	return 0;
}
