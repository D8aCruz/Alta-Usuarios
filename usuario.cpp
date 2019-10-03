#include "usuario.h"
#include "ui_usuario.h"
#include <QMessageBox>

Usuario::Usuario(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Usuario)
{
    ui->setupUi(this);
}

Usuario::~Usuario()
{
    delete ui;
}

int Usuario::exec()
{
	ui->lineEdit_Nombre->setText(uUsuario.nombre);
	ui->lineEdit_Apellido->setText(uUsuario.apellido);
	//ui->lineEdit_CUIL->setText(QString::number(usuario.CUIL).replace(QRegExp("(\\d\\d)(\\d\\d\\d\\d\\d\\d\\d\\d)(\\d\\d)"), "\\1-\\2-\\3"));
	ui->lineEdit_CUIL->setText(uUsuario.CUIL);
	ui->dateEdit_Nacim->setDate(uUsuario.fecha_nacimiento);
	ui->Calif_dial->setValue(uUsuario.calificacion);
	ui->checkBox_Habilitado->setChecked(uUsuario.habilitado);

	ui->radioButton_M->setChecked(uUsuario.masculino);
	ui->radioButton_F->setChecked(!uUsuario.masculino);

	ui->comboBox_ECivil->setCurrentIndex(uUsuario.estado_civil);

	return QDialog::exec();
}

//void Usuario::on_Calif_dial_valueChanged(int value)
//{
//	ui->Calif_lcdNumber->display(value);
//	ui->Calif_progressBar->setValue(value);
//}

void Usuario::on_buttonBox_accepted()
{
	uUsuario.nombre = ui->lineEdit_Nombre->text();
	uUsuario.apellido = ui->lineEdit_Apellido->text();
	//usuario.CUIL = ui->lineEdit_CUIL->text().replace("-", "").toInt();
	uUsuario.CUIL = ui->lineEdit_CUIL->text();
	uUsuario.fecha_nacimiento = ui->dateEdit_Nacim->date();
	uUsuario.calificacion = ui->Calif_dial->value();
	uUsuario.habilitado = ui->checkBox_Habilitado->isChecked();
	uUsuario.masculino = ui->radioButton_M->isChecked();
	uUsuario.estado_civil = (UsuarioData::ECivil)ui->comboBox_ECivil->currentIndex();
}

void Usuario::nombreChanged(QString)
{
	ui->lineEdit_NombComp->setText(ui->lineEdit_Apellido->text().length()?ui->lineEdit_Apellido->text() + ", " + ui->lineEdit_Nombre->text():ui->lineEdit_Nombre->text());
}
