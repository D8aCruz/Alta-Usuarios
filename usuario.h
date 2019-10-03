#ifndef USUARIO_H
#define USUARIO_H

#include <QDialog>
#include <QString>
#include <QDate>

namespace Ui {
	class Usuario;
}

struct UsuarioData
{
	UsuarioData() : calificacion(50), habilitado(true), masculino(true), estado_civil(Soltero) {}

	QString nombre;
	QString apellido;
	//int CUIL;
	QString CUIL;
	QDate fecha_nacimiento;
	int calificacion;
	bool habilitado;
	bool masculino;
	enum ECivil {Soltero, Casado,
		  Divorciado, Viudo,
		  Concubinato} estado_civil;
};

class Usuario : public QDialog
{
    Q_OBJECT

public:
    explicit Usuario(QWidget *parent = 0);
    ~Usuario();

	UsuarioData uUsuario;

	int exec();

private slots:
//	void on_Calif_dial_valueChanged(int value);

	void on_buttonBox_accepted();

public slots:
	void nombreChanged(QString s);

private:
    Ui::Usuario *ui;
};

#endif // USUARIO_H
