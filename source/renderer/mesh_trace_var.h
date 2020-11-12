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

#ifndef __RENDERER_MESH_TRACE_VAR_H
#define __RENDERER_MESH_TRACE_VAR_H

#include "triangle.h"

namespace zifanur
{
    struct mesh_tv
    {
        vector3 m_i_in_r;

        unsigned m_index = 0;
        triangle m_in_ray;
        vector3 m_sides[2];
        vector3 m_normal;
        vector3 m_i_in_t;
        vector3 m_incident;
        vector3 m_prop;
    };
}

#endif // __RENDERER_MESH_TRACE_VAR_H
