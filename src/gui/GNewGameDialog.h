/** *************************************************************************
 *
 *  Copyright (c) 2015
 *  @author Peter Gazdik, xgazdi03@stud.fit.vutbr.cz
 *  @author Klara Mihalikova, xmihal05@stud.fit.vutbr.cz
 *
 *  @file GNewGameDialog.h
 *
 *  @note Subor nebol vygenerovany automaticky
 *
 *
 ************************************************************************** */

#ifndef GNEWGAMEDIALOG_H
#define GNEWGAMEDIALOG_H

#include <QDialog>

namespace Ui {
  class GNewGameDialog;
}

/**
 * @brief The GNewGameDialog class dialog vytvorenia novej hry
 */
class GNewGameDialog : public QDialog
{
  Q_OBJECT

public:
  explicit GNewGameDialog(QWidget *parent = 0);
  ~GNewGameDialog();

  int m_size;
  int m_treasures;
  int m_players;

private slots:

  void on_size5_toggled(bool checked);

  void on_treasures24_toggled(bool checked);

  void on_size7_toggled(bool checked);

  void on_size9_toggled(bool checked);

  void on_size11_toggled(bool checked);

  void on_players2_toggled(bool checked);

  void on_players3_toggled(bool checked);

  void on_players4_toggled(bool checked);

  void on_treasures12_toggled(bool checked);

private:
  Ui::GNewGameDialog *ui;
};

#endif // GNEWGAMEDIALOG_H
