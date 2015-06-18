/** *************************************************************************
 *
 *  Copyright (c) 2015
 *  @author Peter Gazdik, xgazdi03@stud.fit.vutbr.cz
 *  @author Klara Mihalikova, xmihal05@stud.fit.vutbr.cz
 *
 *  @file GNewGameDialog.cpp
 *
 *  @note Subor nebol vygenerovany automaticky
 *
 *
 ************************************************************************** */

#include "GNewGameDialog.h"
#include "ui_GNewGameDialog.h"

GNewGameDialog::GNewGameDialog(QWidget *parent) :
  QDialog(parent),
  ui(new Ui::GNewGameDialog)
{
  ui->setupUi(this);
  m_treasures = 12;
  m_players = 2;
  m_size = 7;
}

GNewGameDialog::~GNewGameDialog()
{
  delete ui;
}

void GNewGameDialog::on_size5_toggled(bool checked)
{
  if (checked) {
    m_size = 5;
    ui->treasures12->toggle();
  }
}

void GNewGameDialog::on_treasures24_toggled(bool checked)
{
  if (checked) {
    m_treasures = 24;

    if (ui->size5->isChecked())
      ui->size7->toggle();
  }
}

void GNewGameDialog::on_size7_toggled(bool checked)
{
  if (checked)
    m_size = 7;
}

void GNewGameDialog::on_size9_toggled(bool checked)
{
  if (checked)
    m_size = 9;
}

void GNewGameDialog::on_size11_toggled(bool checked)
{
  if (checked)
    m_size = 11;
}

void GNewGameDialog::on_players2_toggled(bool checked)
{
  if (checked)
    m_players = 2;
}

void GNewGameDialog::on_players3_toggled(bool checked)
{
  if (checked)
    m_players = 3;
}

void GNewGameDialog::on_players4_toggled(bool checked)
{
  if (checked)
    m_players = 4;
}

void GNewGameDialog::on_treasures12_toggled(bool checked)
{
  if (checked)
    m_treasures = 12;
}
