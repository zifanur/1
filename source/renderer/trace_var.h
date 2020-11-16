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

#ifndef __RENDERER_TRACE_VAR_H
#define __RENDERER_TRACE_VAR_H

#include <random>
#include "f_rgb.h"
#include "mesh_trace_var.h"

namespace zifanur
{
    class object;

    using random_seed = std::mt19937::result_type;

    struct trace_var
    {
        std::mt19937 m_random;

        matrix4 m_pix_to_cam;
        vector3 m_on_cam_plane;

        unsigned m_depth = 0;
        matrix4 m_world_to_ray;

        object *m_closest = nullptr;
        union
        {
            vector3 m_intersect;
            mesh_tv m_mtv;
        };

        vector3 m_inc_in_mat;
        vector3 m_prop_in_mat;

        matrix4 m_ray_to_prop;

        bool m_light_hit = false;
        f_rgb m_absorb;
        f_rgb m_accum;

        unsigned m_count = 0;
        f_rgb m_total;

        trace_var(random_seed a_seed, const matrix4 &a_pix_to_cam):
            m_random(a_seed), m_pix_to_cam(a_pix_to_cam), m_mtv() {}

        operator f_rgb() const { return m_count > 0? m_total / float(m_count): f_rgb(); }
    };
}

#endif // __RENDERER_TRACE_VAR_H
