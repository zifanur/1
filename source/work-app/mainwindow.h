/* Zifanur -- the scene rendering library
   Copyright 2020 Rasim Valiullin

   This file is part of Zifanur.

   Zifanur is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   Zifanur is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with Zifanur.  If not, see <https://www.gnu.org/licenses/>.
*/

// zifanur@hotmail.com

#ifndef __WORK_APP_MAINWINDOW_H
#define __WORK_APP_MAINWINDOW_H

#include <QMainWindow>
#include <renderer/renderer.h>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class FrameArea;

class MainWindow: public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *a = nullptr);
    ~MainWindow();

public slots:
    void on_pushButton_doIt_clicked();

protected slots:
    void onResize(QSize a);

private:
    Ui::MainWindow *m_ui = nullptr;
    FrameArea *m_fa = nullptr;

    zifanur::renderer m_r;
};

#endif // __WORK_APP_MAINWINDOW_H
