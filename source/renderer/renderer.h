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

#include "object.h"
#include "material.h"
#include <list>

namespace zifanur
{
    class renderer
    {
    public:
        renderer();

        renderer(const renderer &a) = delete;
        renderer &operator =(const renderer &a) = delete;

        ~renderer();

        void set_buf_size(unsigned a_width, unsigned a_height);
        unsigned buf_width() const { return m_buf_width; }
        unsigned buf_height() const { return m_buf_height; }
        f_rgb *buf() const { return m_buf; }

        void set_fov(float a_h_ratio, float a_v_ratio);

        void set_cam(const matrix4 &a) { m_cam = a; }
        matrix4 cam() const { return m_cam; }

        void set_rpp(unsigned a) { m_rpp = a; }
        void set_depth(unsigned a) { m_depth = a; }

        void add(object *a) { m_objects.push_back(a); }
        void add(material *a) { m_materials.push_back(a); }

        void do_it();
        void do_it(unsigned a_thread_num);

    private:
        void calc_buf_to_cam();

        trace_var &ray(trace_var &a);
        trace_var &trace(trace_var &a);
        trace_var &cam_ray(trace_var &a);
        trace_var &process_pixel(trace_var &a);

        std::random_device m_rand_dev;

        unsigned m_buf_width = 0, m_buf_height = 0;
        f_rgb *m_buf = nullptr;

        float m_h_ratio = 1, m_v_ratio = 1;
        matrix4 m_buf_to_cam;

        matrix4 m_cam;

        unsigned m_rpp = 6000, m_depth = 15;

        std::list<object *> m_objects;
        std::list<material *> m_materials;
    };
}

#endif //__RENDERER_RENDERER_H
