#include <QApplication>
#include <QString>

#include <QFileDialog>
#include <QPushButton>
#include <QLineEdit>
#include <QIcon>
#include <QHBoxLayout>
#include <QVBoxLayout>

#include <QTableWidget>
#include <QTableWidgetItem>

#include <iostream>

#include "mainguiwindow.h"
#include "fascade.h"
#include "getfilenamevisitor.h"


MainGUIWindow::MainGUIWindow(QWidget *parent, QString name)
  :QWidget(parent)
{
  this->setWindowTitle(name);

  QString iconimage("C:/SourceCode/VS2010/QTGUIBased_CodeParser/Qt-logo.png");
  QIcon windowicon(iconimage);
  this->setWindowIcon(windowicon);
  init();
}


void MainGUIWindow::init()
{

  //Create a vertical container(main) widgets
  mainlayout = new QVBoxLayout(this);

  //Create a horizontal container widgets.
  hlayoutone = new QHBoxLayout(this);
  hlayoutone->setSpacing(1);

  // Intialize all pushbutton widgets.
  QString okname = "OK";
  ok = new QPushButton(okname, this);

  QString clearname = "CLEAR";
  clear = new QPushButton(clearname, this);

  QString cancelname = "QUIT";
  cancel = new QPushButton(cancelname, this);

  QString browsename = "BROWSE";
  browse = new QPushButton(browsename, this);

  //Intialize QLineEdit widget
  editor = new QLineEdit(this);
  editor->setPlaceholderText("Input");

  //now add all child widgets inside parent one
  hlayoutone->addWidget(ok);
  hlayoutone->addWidget(clear);
  hlayoutone->addWidget(cancel);
  hlayoutone->addWidget(browse);

  //Connect the browse button click signal to MainWindow object. I
  //need to show up the pop up messsge/window to select the directory.
  connect(ok,     SIGNAL(clicked(bool)), this, SLOT(MyOkClicked()));
  connect(clear,  SIGNAL(clicked(bool)), this, SLOT(MyClearClicked()));
  connect(cancel, SIGNAL(clicked(bool)), this, SLOT(MyCancelClicked()));
  connect(browse, SIGNAL(clicked(bool)), this, SLOT(MyBrowseClicked()));

  //Initialize the QFileDialog widget
  dialogmessage = new QFileDialog(this);
  dialogmessage->setFileMode(QFileDialog::DirectoryOnly);
  // This connect would actually trigger main widgets when someone selects the
  // directory/files. This indicates that I can fetch the current directory
  // from dialogmessage widget and pass back to editor widgets.
  connect(dialogmessage, SIGNAL(accepted()), this, SLOT(MyDialogSelected()));

  // Initialize the TableWidget with 100(row), 2(column)
  output = new QTableWidget(100, 2, this);
  // Do the sorting enabled for this widgets.
  // output->setSortingEnabled(true);

  summary = new QLineEdit(this);
  summary->setPlaceholderText("Summary");


  // Now add QLineText, QTextEdit and one QHBoxLayout
  mainlayout->addItem(hlayoutone);
  mainlayout->addWidget(editor);
  mainlayout->addWidget(output);
  mainlayout->addWidget(summary);

  this->setLayout(mainlayout);

}


void MainGUIWindow::MyOkClicked()
{
  std::cout<<"MainGUIWindow::MyOkClicked()"<<std::endl;
  // Now I need to first get the stored/selected directory
  // and now from here trigger the actual parsing logic.
  // Do some sanity test here
  if(currentdir.isEmpty()){
      return;
    } else {
      std::vector<std::string> input;
      input.push_back(std::string());
      input.push_back(currentdir.toStdString());
      codeparser parser(input);
      parser.start_execution();

      int row = 0;
      int column = 0;
      output->setRowCount(parser.filesinfo.size());
      QTableWidgetItem* filename = NULL;
      QTableWidgetItem* locoffile = NULL;

      for(std::map<std::string ,long long>::iterator itr = parser.filesinfo.begin();
          itr != parser.filesinfo.end();
          ++itr)
        {
          QString locfile = QString::number((*itr).second);
          std::string tmp((*itr).first);
          //Extract the filename only from complete path
          tmp = filename_from_path(tmp);
          filename = new QTableWidgetItem(QString(tmp.c_str()) );
          locoffile = new QTableWidgetItem(locfile);
          output->setItem(row, column, filename);
          output->setItem(row, ++column, locoffile);
          column = 0;
          ++row;
        }

      // Now set the summary output for all files.
      QString summarymsg("Files:\t"  +
                         QString::number(parser.filesinfo.size()) +
                         "\t" +
                         QString::number(parser.total_valid_line())
                         );
      summary->setText(summarymsg);
    }
}

void MainGUIWindow::MyClearClicked()
{
  std::cout<<"MainGUIWindow::MyClearClicked()"<<std::endl;
  //QString clear("");
  editor->clear();
  output->clear();
  summary->clear();
  output->setRowCount(100);
}

void MainGUIWindow::MyCancelClicked()
{
  std::cout<<"MainGUIWindow::MyCancelClicked()"<<std::endl;
  QApplication::quit();
}


void MainGUIWindow::MyBrowseClicked()
{
  std::cout<<"MainGUIWindow::MyBrowseClicked()"<<std::endl;
  dialogmessage->exec();

}


void MainGUIWindow::MyDialogSelected()
{
  std::cout<<"MainGUIWindow::MyDialogSelected()"<<std::endl;
  //Fetched the current selected directory and store
  currentdir = dialogmessage->getExistingDirectory();
  std::cout<<currentdir.toStdString()<<std::endl;

  // Now set the editor widget with the above currentdir.
  editor->setText(currentdir);
}

