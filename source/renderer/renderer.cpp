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

#include "renderer.h"

namespace zifanur
{
    renderer::renderer() {}

    renderer::~renderer() { delete []m_acc; }

    void renderer::set_buf_size(unsigned a_width, unsigned a_height)
    {
        delete []m_acc; m_acc = nullptr;
        m_buf_width = m_buf_height = 0;
        m_acc = new f_rgb[size_t(a_width) * a_height];
        m_buf_width = a_width;  m_buf_height = a_height;
        calc_buf_to_cam();
    }

    void renderer::set_fov(float a_h_ratio, float a_v_ratio)
    {
        m_h_ratio = a_h_ratio, m_v_ratio = a_v_ratio;
        calc_buf_to_cam();
    }

    void renderer::calc_buf_to_cam()
    {
        m_buf_to_cam = matrix4(m_h_ratio / m_buf_width, 0, 0, m_h_ratio / 2 * (1.0f / m_buf_width - 1),
                                0, -m_v_ratio / m_buf_height, 0, m_v_ratio / 2 * (1 - 1.0f / m_buf_height));
    }
}
