#ifndef MAINGUIWINDOW_H
#define MAINGUIWINDOW_H

#include <QWidget>

//Forward Declaration
class QWidget;
class QString;
class QFileDialog;
class QPushButton;
class QLineEdit;
class QHBoxLayout;
class QVBoxLayout;
class QTableWidget;


class MainGUIWindow : public QWidget
{
  Q_OBJECT
public:
  explicit MainGUIWindow(QWidget *parent = 0, QString name = "CPPCodeParser");
signals:

public slots:
  void MyOkClicked();
  void MyClearClicked();
  void MyCancelClicked();
  void MyBrowseClicked();
  void MyDialogSelected();
private:
  void init();

  QPushButton*   ok;
  QPushButton*   clear;
  QPushButton*   cancel;
  QPushButton*   browse;
  QLineEdit*     editor;
  QFileDialog*   dialogmessage;
  QString        currentdir;
  QTableWidget*  output;
  QLineEdit*     summary;

  QHBoxLayout*   hlayoutone;
  QVBoxLayout*   mainlayout;

};


#endif  // MAINGUIWINDOW_H
