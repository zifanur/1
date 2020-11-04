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
#include <renderer/renderer.h>
#include <renderer/mesh.h>
#include <QFileDialog>

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
    std::unique_ptr<zifanur::triangle []> l_td(new zifanur::triangle [1]);
    auto l_mesh(std::make_unique<zifanur::mesh>(1, l_td.get()));
    l_td[0] = zifanur::triangle(zifanur::vector3(-4, 0, 1), zifanur::vector3(2, 0, -4), zifanur::vector3(3, 0, 4));
    l_td.release();
    zifanur::renderer l_r;
    l_r.add(l_mesh.get());
    l_mesh.release();

    l_r.set_buf_size(m_fa->width(), m_fa->height());
    l_r.set_fov(1, 1);
    l_r.set_cam(transf(zifanur::vector3(0, -10, 0), zifanur::vector3(0, 10, 0), zifanur::vector3(0, 0, 1)));
    l_r.doIt();

    QImage l_img(l_r.buf_width(), l_r.buf_height(), QImage::Format_ARGB32);
    for (unsigned i = 0; i < l_r.buf_height(); i++)
        for (unsigned j = 0; j < l_r.buf_width(); j++)
        {
            const auto l_rgb(l_r.buf()[j + i * l_r.buf_width()]);
            l_img.setPixelColor(j, i, QColor(255 * l_rgb.r, 255 * l_rgb.g, 255 * l_rgb.b));
        }
    m_fa->setImage(std::move(l_img));
}

void MainWindow::on_pushButton_save_clicked()
{
    const auto l_fp(QFileDialog::getSaveFileName(this, windowTitle() + " - Save", "image1.png", "Images (*.png)"));
    if (l_fp.isEmpty()) return;
    m_fa->image().save(l_fp, "PNG");
}

void MainWindow::onResize(QSize a)
{
    m_ui->lineEdit_res->setText(QString("%1x%2").arg(a.width()).arg(a.height()));
}
