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
        mesh(unsigned a_count, triangle *a_t = nullptr) :m_count(a_count), m_t(a_t) {}

        ~mesh() override { delete []m_t; }

        virtual bool hit(trace_var &a);

    private:
        bool hit(trace_var &a_tv, const triangle &a_t);

        unsigned m_count = 0;
        triangle *m_t = nullptr;
    };

    inline bool mesh::hit(trace_var &a)
    {
        for (unsigned q = 0; q < m_count; q++)
            if (hit(a, m_t[q])) { a.m_spectrum.g = 1; return true; }
        return false;
    }

    inline bool mesh::hit(trace_var &a_tv, const triangle &a_t)
    {
        triangle l_t;
        for (int i = 0; i < 3; i++) l_t.v3[i] = a_tv.m_world_to_ray * a_t.v3[i];
        return inside(vector3(), l_t);
    }
}

#endif // __RENDERER_MESH_H
