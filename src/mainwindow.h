#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtMmlWidget>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    
private:
    Ui::MainWindow *ui;
	QtMmlWidget *mmlWidget;

	QString getMathML(QString provider);

private slots:
	void solveButtonClicked();
	void renderML();
};

void showWarning(const QString &msg);
void showInfo(const QString &msg);

#endif // MAINWINDOW_H
