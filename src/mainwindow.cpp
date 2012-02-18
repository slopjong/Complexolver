#include <QDebug>
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "libreformath.h"
#include <QRegExp>
#include <QMessageBox>

void showWarning(const QString &msg)
{
	QMessageBox::warning(0, "Warning", msg,
							QMessageBox::Ok,
							QMessageBox::NoButton,
							QMessageBox::NoButton);
}

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
	ui(new Ui::MainWindow),
	mmlWidget(new QtMmlWidget(parent))
{
    ui->setupUi(this);

	// add the rendering widget
	QVBoxLayout *layout = new QVBoxLayout;
	layout->addWidget(mmlWidget);
	ui->formulaWidget->setLayout(layout);

	// attach a click event handler
	connect(ui->solveButton, SIGNAL(clicked()), this, SLOT(solveButtonClicked()));
	// attach a rendering handler
	connect(ui->tabWidget, SIGNAL(currentChanged(int)), this, SLOT(renderML()));

	// render initially the function since there will be no initial
	// currentChanged event
	renderML();
}

MainWindow::~MainWindow()
{
	delete ui;
}

/**
 * Get the MathML code from the provider text field. A provider is passed as a
 * string, no good programming style. Better to use an enum.
 */
QString MainWindow::getMathML(QString provider)
{
	QWidget *tab = ui->tabWidget->currentWidget();
	const QString pattern = "mlpresentation.*";
	const QRegExp re(pattern);
	QList<QPlainTextEdit*> list = tab->findChildren<QPlainTextEdit *>(re);

	// this only happens if there is no textfield with
	// mlpresentation.* as the object name
	if(list.empty()){
		showWarning("Could not read from the text field");
		return "";
	}

	QPlainTextEdit *edit = list.first();
	return edit->toPlainText();
}

/**
 * Solve the function
 */
void MainWindow::solveButtonClicked()
{

}

/**
 * Render the function.
 */
void MainWindow::renderML()
{
	QString mathml = getMathML("presentation");

	QString error_msg;
	int error_line, error_column;
	bool result = mmlWidget->setContent(mathml, &error_msg, &error_line,
						&error_column);
	if (!result) {
		showWarning("Parse error: line " + QString::number(error_line)
					+ ", col " + QString::number(error_column)
			+ ": " + error_msg);
	}
}
