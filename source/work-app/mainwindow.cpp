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

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "framearea.h"

MainWindow::MainWindow(QWidget *a):
    QMainWindow(a), m_ui(new Ui::MainWindow), m_fa(new FrameArea(this))
{
    m_ui->setupUi(this);
    m_fa->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    connect(m_fa, SIGNAL(sResize(QSize)), SLOT(onResize(QSize)));
    m_ui->verticalLayout_left->insertWidget(0, m_fa);
}

MainWindow::~MainWindow()
{
    delete m_ui;
}

void MainWindow::on_pushButton_doIt_clicked()
{
    m_r.set_buf_size(10, 10);
    m_r.set_fov(1, 1);
    m_r.doIt();
}

void MainWindow::onResize(QSize a)
{
    m_ui->lineEdit_res->setText(QString("%1x%2").arg(a.width()).arg(a.height()));
}
