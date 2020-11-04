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

#ifndef __RENDERER_VECTOR3_H
#define __RENDERER_VECTOR3_H

#include <cmath>

namespace zifanur
{
    struct vector3
    {
        union
        {
            float m[3];
            struct { float x, y, z; };
        };

        vector3(float a_x = 0, float a_y = 0, float a_z = 0):
            x(a_x), y(a_y), z(a_z)
        {}
    };

    inline float length(const vector3 &a)
    {
        float l = 0;
        for (int i = 0; i < 3; i++) l += a.m[i] * a.m[i];
        return std::sqrt(l);
    }

    inline vector3 normalized(const vector3 &a)
    {
        vector3 l_n;
        const float l_l = length(a);
        for (int i = 0; i < 3; i++) l_n.m[i] = a.m[i] / l_l;
        return l_n;
    }

    inline vector3 operator +(const vector3 &a_o, const vector3 &a_a)
    {
        vector3 l;
        for (int i = 0; i < 3; i++) l.m[i] = a_o.m[i] + a_a.m[i];
        return l;
    }

    inline vector3 operator -(const vector3 &a_o, const vector3 &a_a)
    {
        vector3 l;
        for (int i = 0; i < 3; i++) l.m[i] = a_o.m[i] - a_a.m[i];
        return l;
    }

    inline float dot(const vector3 &a_o, const vector3 &a_a)
    {
        float l = 0;
        for (int i = 0; i < 3; i++) l += a_o.m[i] * a_a.m[i];
        return l;
    }

    inline vector3 cross(const vector3 &a_o, const vector3 &a_a)
    {
        vector3 l;
        for (int i = 0; i < 3; i++)
            l.m[i] = a_o.m[(i + 1) % 3] * a_a.m[(i + 2) % 3] - a_o.m[(i + 2) % 3] * a_a.m[(i + 1) % 3];
        return l;
    }
}

#endif // __RENDERER_VECTOR3_H
