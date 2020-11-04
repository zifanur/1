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

#ifndef __RENDERER_MESH_H
#define __RENDERER_MESH_H

#include "triangle.h"
#include "object.h"

namespace zifanur
{
    class mesh: public object
    {
    public:
        mesh(unsigned a_count, triangle *a_t) :m_count(a_count), m_t(a_t) {}

        ~mesh() override { delete []m_t; }

        trace_var &hit(trace_var &a) override;
        trace_var &refl(trace_var &a) override;

    private:
        trace_var &hit(trace_var &a_tv, unsigned a_ti);
        trace_var &gen(trace_var &a);

        unsigned m_count = 0;
        triangle *m_t = nullptr;
    };

    inline trace_var &mesh::hit(trace_var &a)
    {
        for (unsigned q = 0; q < m_count; q++) hit(a, q);
        return a;
    }

    inline trace_var &mesh::refl(trace_var &a)
    {
        const vector3 l_xa(normalized(a.m_mtv.m_sides[0])),
                        l_za(normalized(a.m_mtv.m_normal)),
                        l_ya(cross(l_za, l_xa));
        const matrix4 l_ray_to_triangle_rot(vector4(l_xa, 0), vector4(l_ya, 0), vector4(l_za, 0));
        a.m_mtv.m_incident = l_ray_to_triangle_rot * a.m_mtv.m_i_in_r;
        const vector3 l_origin(-dot(l_xa, a.m_mtv.m_in_ray.p1),
                                -dot(l_ya, a.m_mtv.m_in_ray.p1),
                                -dot(l_za, a.m_mtv.m_in_ray.p1));
        const matrix4 l_ray_to_triangle(shifted(l_ray_to_triangle_rot, l_origin));
        a.m_mtv.m_i_in_t = l_ray_to_triangle * a.m_mtv.m_i_in_r;
        gen(a);
        const vector3 l_to(a.m_mtv.m_i_in_t + a.m_mtv.m_refl);
        const matrix4 l_triangle_to_prop(transf(a.m_mtv.m_i_in_t, l_to, perp(a.m_mtv.m_refl)));
        a.m_ray_to_prop = l_triangle_to_prop * l_ray_to_triangle;
        a.m_spectrum.g = -dot(normalized(a.m_mtv.m_incident), normalized(a.m_mtv.m_normal));
        return a;
    }

    inline trace_var &mesh::hit(trace_var &a_tv, unsigned a_ti)
    {
        mesh_tv l_mtv;
        l_mtv.m_in_ray = a_tv.m_world_to_ray * m_t[a_ti];
        if (!inside(vector3(), l_mtv.m_in_ray)) return a_tv;
        l_mtv.m_sides[0] = l_mtv.m_in_ray.p2 - l_mtv.m_in_ray.p1;
        l_mtv.m_sides[1] = l_mtv.m_in_ray.p3 - l_mtv.m_in_ray.p1;
        l_mtv.m_normal = cross(l_mtv.m_sides[0], l_mtv.m_sides[1]);
        l_mtv.m_i_in_r.z = dot(l_mtv.m_normal, l_mtv.m_in_ray.p2) / l_mtv.m_normal.z;
        if (!std::isfinite(l_mtv.m_i_in_r.z) || l_mtv.m_i_in_r.z >= 0) return a_tv;
        if (a_tv.m_closest != nullptr && l_mtv.m_i_in_r.z <= a_tv.m_intersect.z) return a_tv;
        a_tv.m_closest = this;
        a_tv.m_mtv = l_mtv;
        return a_tv;
    }

    inline trace_var &mesh::gen(trace_var &a)
    {
        a.m_mtv.m_refl = vector3(0, 0, 1);
        return a;
    }
}

#endif // __RENDERER_MESH_H
