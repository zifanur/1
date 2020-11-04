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

#ifndef __RENDERER_TRIANGLE_H
#define __RENDERER_TRIANGLE_H

#include "matrix4.h"

namespace zifanur
{
    struct triangle
    {
        union
        {
            struct { vector3 p1, p2, p3; };
            vector3 v3[3];
        };

        explicit triangle(const vector3 &a_p1 = vector3(),
                            const vector3 &a_p2 = vector3(), const vector3 &a_p3 = vector3()):
            v3{a_p1, a_p2, a_p3}
        {}
    };

    inline triangle operator *(const matrix4 &a_m, const triangle &a_t)
    {
        triangle l_t;
        for (int i = 0; i < 3; i++) l_t.v3[i] = a_m * a_t.v3[i];
        return l_t;
    }

    //https://stackoverflow.com/a/2049593/5634114
    inline float sign(const vector3 &a_p, const vector3 &a_from, const vector3 &a_to)
    {
        return (a_p.x - a_to.x) * (a_from.y - a_to.y) - (a_from.x - a_to.x) * (a_p.y - a_to.y);
    }

    inline bool inside(const vector3 &a_p, const triangle &a_t)
    {
        for (int i = 0; i < 3; i++)
            if (sign(a_p, a_t.v3[i], a_t.v3[(1 + i) % 3]) < 0) return false;
        return true;
    }
}

#endif // __RENDERER_TRIANGLE_H
