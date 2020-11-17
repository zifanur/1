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
#include <renderer/solid_color.h>
#include <renderer/solid_color_light.h>
#include <renderer/mesh_from_obj.h>
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
    zifanur::renderer l_r;

    std::unique_ptr<zifanur::triangle []> l_td1(new zifanur::triangle [2]);
    l_td1[0] = zifanur::triangle(zifanur::vector3(5, -5, 5), zifanur::vector3(5, 5, 5), zifanur::vector3(5, -5, -5));
    l_td1[1] = zifanur::triangle(zifanur::vector3(5, -5, -5), zifanur::vector3(5, 5, 5), zifanur::vector3(5, 5, -5));
    auto l_material1(std::make_unique<zifanur::solid_color>(zifanur::f_rgb(0.4f, 0.6f, 0.4f)));
    auto l_mesh1(std::make_unique<zifanur::mesh>(2, l_td1.get(), l_material1.get()));
    l_td1.release();
    l_r.add(l_material1.get());
    l_material1.release();
    l_r.add(l_mesh1.get());
    l_mesh1.release();

    std::unique_ptr<zifanur::triangle []> l_td2(new zifanur::triangle [2]);
    l_td2[0] = zifanur::triangle(zifanur::vector3(5, -5, 5), zifanur::vector3(-5, -5, 5), zifanur::vector3(-5, 5, 5));
    l_td2[1] = zifanur::triangle(zifanur::vector3(5, -5, 5), zifanur::vector3(-5, 5, 5), zifanur::vector3(5, 5, 5));
    auto l_material2(std::make_unique<zifanur::solid_color_light>(zifanur::f_rgb(0.5f, 0.5f, 0.5f), zifanur::f_rgb(1.05f, 1.05f, 0.9f)));
    auto l_mesh2(std::make_unique<zifanur::mesh>(2, l_td2.get(), l_material2.get()));
    l_td2.release();
    l_r.add(l_material2.get());
    l_material2.release();
    l_r.add(l_mesh2.get());
    l_mesh2.release();

    std::unique_ptr<zifanur::triangle []> l_td3(new zifanur::triangle [2]);
    l_td3[0] = zifanur::triangle(zifanur::vector3(-5, -5, 5), zifanur::vector3(-5, -5, -5), zifanur::vector3(-5, 5, -5));
    l_td3[1] = zifanur::triangle(zifanur::vector3(-5, -5, 5), zifanur::vector3(-5, 5, -5), zifanur::vector3(-5, 5, 5));
    auto l_material3(std::make_unique<zifanur::solid_color>(zifanur::f_rgb(0.4f, 0.6f, 0.4f)));
    auto l_mesh3(std::make_unique<zifanur::mesh>(2, l_td3.get(), l_material3.get()));
    l_td3.release();
    l_r.add(l_material3.get());
    l_material3.release();
    l_r.add(l_mesh3.get());
    l_mesh3.release();

    std::unique_ptr<zifanur::triangle []> l_td4(new zifanur::triangle [2]);
    l_td4[0] = zifanur::triangle(zifanur::vector3(5, -5, -5), zifanur::vector3(5, 5, -5), zifanur::vector3(-5, -5, -5));
    l_td4[1] = zifanur::triangle(zifanur::vector3(-5, -5, -5), zifanur::vector3(5, 5, -5), zifanur::vector3(-5, 5, -5));
    auto l_material4(std::make_unique<zifanur::solid_color>(zifanur::f_rgb(0.6f, 0.4f, 0.4f)));
    auto l_mesh4(std::make_unique<zifanur::mesh>(2, l_td4.get(), l_material4.get()));
    l_td4.release();
    l_r.add(l_material4.get());
    l_material4.release();
    l_r.add(l_mesh4.get());
    l_mesh4.release();

    auto l_material5(std::make_unique<zifanur::solid_color>(zifanur::f_rgb(0.4f, 0.4f, 0.6f)));
    auto l_mesh5(zifanur::from_obj("polyhedronisme-I.obj", l_material5.get()));
    if (l_mesh5 != nullptr)
    {
        l_mesh5->transform(zifanur::scale_and_move(zifanur::vector3(2.5, 2.5, 2.5), zifanur::vector3(2, 0, 0)));
        l_r.add(l_material5.get());
        l_material5.release();
        l_r.add(l_mesh5.get());
        l_mesh5.release();
    }

    l_r.set_buf_size(m_fa->width(), m_fa->height());
    l_r.set_fov(1, 1);
    l_r.set_cam(transf(zifanur::vector3(0, -15.5, 0), zifanur::vector3(0, 0, 0), zifanur::vector3(0, 0, 1)));
    l_r.do_it(14);

    QImage l_img(l_r.buf_width(), l_r.buf_height(), QImage::Format_ARGB32);
    for (unsigned i = 0; i < l_r.buf_height(); i++)
        for (unsigned j = 0; j < l_r.buf_width(); j++)
        {
            const auto l_rgb(l_r.buf()[j + i * l_r.buf_width()]);
            l_img.setPixelColor(j, i, QColor(255 * (l_rgb.r > 1? 1: l_rgb.r), 255 * (l_rgb.g > 1? 1: l_rgb.g), 255 * (l_rgb.b > 1? 1: l_rgb.b)));
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
