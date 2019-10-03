#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "usuario.h"
#include <QVector>

namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

	void RefrescarLista();
private:
	//Agrego manualmente la redefinición de esta función (definida en QDialog)
	void closeEvent(QCloseEvent * event);

	//Vector en el que vamos a guardar los datos de los usuarios cargados
	QVector<UsuarioData> vUsuarios;

private slots:
	void on_pushButtonAceptar_clicked();

	void on_pushButtonEditar_clicked();

	void on_pushButtonEliminar_clicked();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
