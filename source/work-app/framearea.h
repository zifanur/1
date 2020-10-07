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

#ifndef __FRAMEAREA_H
#define __FRAMEAREA_H

#include <QWidget>

class QImage;

class FrameArea: public QWidget
{
    Q_OBJECT

public:
    FrameArea(QWidget *a = nullptr);
    void setImage(QImage &&a);
    const QImage &image() const;

signals:
    void sResize(QSize a);

protected:
    void paintEvent(QPaintEvent *a) override;
    void resizeEvent(QResizeEvent *a) override;

private:
    QImage m_i;
};

#endif // __FRAMEAREA_H
