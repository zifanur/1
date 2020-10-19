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

#ifndef __RENDERER_RENDERER_H
#define __RENDERER_RENDERER_H

#include "f_rgb.h"
#include "matrix4.h"

namespace zifanur
{
    class renderer
    {
    public:
        renderer();
        ~renderer();

        void set_buf_size(unsigned a_width, unsigned a_height);
        unsigned buf_width() const { return m_buf_width; }
        unsigned buf_height() const { return m_buf_height; }

        void set_fov(float a_h_ratio, float a_v_ratio);

        inline static matrix4 look_at(const vector3 &a_from, const vector3 &a_to, const vector3 &a_up);
        void set_cam(const matrix4 &a) { m_cam = a; }

    private:
        void calc_buf_to_cam();

        unsigned m_buf_width = 0, m_buf_height = 0;
        f_rgb *m_acc = nullptr;

        float m_h_ratio = 1, m_v_ratio = 1;
        matrix4 m_buf_to_cam;

        matrix4 m_cam;
    };
}

#include "renderer-inline.h"

#endif //__RENDERER_RENDERER_H
