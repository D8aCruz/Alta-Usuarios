#include "mainwindow.h"

//En este archivo está el código generado por Qt Creator para crear el diálogo y sus widgets
#include "ui_mainwindow.h"

#include <QMessageBox>
#include <QDesktopWidget>
#include <QCloseEvent>

QTreeWidgetItem* ConvertirUsuarioATreeItem(const UsuarioData& usuario, int nIndex);

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

	//Defino anchos default de columnas. Luego se reemplazan al agregar items.
	ui->treeWidget->setColumnWidth(0, 150);
	ui->treeWidget->setColumnWidth(1, 75);
	ui->treeWidget->setColumnWidth(2, 150);

	//Centro la aplicación en el escritorio
	this->move(QApplication::desktop()->screen()->rect().center() - this->rect().center());
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButtonAceptar_clicked()
{
	//Creo un diálogo de usuario y me pongo a MainWindow (this) como su padre. Esto último es optativo.
	Usuario dlg(this);

	//Lo ejecuto en forma modal (es decir, deshabilitando al padre mientras el diálogo esté vivo)
	//Hay otras funciones con diferentes metodologías: show() y open()
	//Esta función (exec) va a retornar un int indicando una "respuesta". Cuando el usuario presione "Aceptar", retornará QDialog::Accepted, que es un enum que vale 1.
	if (dlg.exec() == QDialog::Accepted)
	{
		//Agregamos el usuario cargado (UsuarioData Usuario::uUsuario) al vector QVector<UsuarioData> MainWindow::vUsuarios
		vUsuarios.append(dlg.uUsuario);

		RefrescarLista();

		//Muestro un mensaje informativo
		QMessageBox::information(this, "Prueba", "Usuario agregado satisfactoriamente!");
	}
}

void MainWindow::RefrescarLista()
{
	ui->treeWidget->clear();

	for (int i = 0; i < vUsuarios.size(); i++)
	{
		UsuarioData& u = vUsuarios[i];

		ui->treeWidget->addTopLevelItem(new QTreeWidgetItem(QStringList() << u.apellido + ", " + u.nombre << (u.habilitado?"Si":"No") << QString::number(u.calificacion)));

		//Esto se podría hacer en varios pasos, armando primero la QStringList, luego el QTreeWidgetItem y finalmente pasándoselo a addTopLevelItem:
		//
		//QStringList columnas;	//Declaro una lista de strings para almacenar las columnas
		//
		//columnas.append(u.apellido + ", " + u.nombre);	//Guardo el nombre
		//columnas.append(QString(u.habilitado?QString::fromUtf8("Sí"):"No"));	//Guardo la habilitación
		//columnas.append(QString::number(u.calificacion));	//Guardo la calificación
		//
		//QTreeWidgetItem* tmpitem = new QTreeWidgetItem(columnas);	//Retorno el puntero a un nuevo objeto "item" creado en el heap
		//
		//ui->treeWidget->addTopLevelItem(tmpitem);	//Al pasarle el puntero a addTopLevelItem, y ano necesitamos liberarlo nosotros, ya que lo hará el destructor de ui->treeWidget.
	}

	//Ajusto el tamaño de todas las columnas para que se muestre la mayor cantidad de datos posibles
	for (int i = 0; i < 3; i++)
		ui->treeWidget->resizeColumnToContents(i);
}

//Escribo el código del manejador del EVENTO (ni señal ni slot, es algo de más bajo nivel) Close
void MainWindow::closeEvent(QCloseEvent * event)
{
	if (QMessageBox::question(this, "Salir", QString::fromUtf8("¿Está seguro de que desea salir?"), QMessageBox::Yes | QMessageBox::No) != QMessageBox::Yes)
		event->ignore();	//Si me contestan que no, descarto el evento, si no dejo que siga su curso
}

void MainWindow::on_pushButtonEditar_clicked()
{
	int index = ui->treeWidget->currentIndex().row();

	if (index == -1)
	{
		QMessageBox::information(this, "Editar", "No hay item seleccionado");
		return;
	}

	UsuarioData old = vUsuarios[index];

	Usuario dlg;
	dlg.uUsuario = old;

	if (dlg.exec() == QDialog::Accepted)
	{
		vUsuarios[index] = dlg.uUsuario;

		RefrescarLista();
	}
}

void MainWindow::on_pushButtonEliminar_clicked()
{
	int index = ui->treeWidget->currentIndex().row();

	if (index == -1)
	{
		QMessageBox::information(this, "Editar", "No hay item seleccionado");
		return;
	}

	if (QMessageBox::question(this, "Eliminar", QString::fromUtf8("¿Está seguro de que desea eliminar el elemento seleccionado?"), QMessageBox::Yes | QMessageBox::No) == QMessageBox::Yes)
	{
		vUsuarios.remove(index);

		RefrescarLista();
	}
}
