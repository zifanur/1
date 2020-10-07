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

#include "framearea.h"
#include <QImage>
#include <QPainter>
#include <QResizeEvent>

FrameArea::FrameArea(QWidget *a):
    QWidget(a)
{}

void FrameArea::setImage(QImage &&a)
{
    m_i = std::move(a);
}

const QImage &FrameArea::image() const
{
    return m_i;
}

void FrameArea::paintEvent(QPaintEvent *a)
{
    QPainter l_p(this);
    l_p.drawImage(rect(), m_i);
}

void FrameArea::resizeEvent(QResizeEvent *a)
{
    emit sResize(a->size());
}
