#pragma once

#include <QDialog>
#include "servermaster.h"
#include "ui_choicerceivingmethod.h"

class ChoiceRceivingMethod : public QDialog, public Ui::ChoiceRceivingMethod
{
	Q_OBJECT;
	ServerRepMaster::ReceivingMethod _method;
private slots:
	void setMethod();
public:
	explicit ChoiceRceivingMethod(QWidget *parent = nullptr);
	virtual  ~ChoiceRceivingMethod();
	ServerRepMaster::ReceivingMethod getMethod() const;
	 
};
