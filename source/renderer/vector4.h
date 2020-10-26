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

#ifndef __RENDERER_VECTOR4_H
#define __RENDERER_VECTOR4_H

#include "vector3.h"

namespace zifanur
{
    struct vector4
    {
        union
        {
            float m[4];
            struct
            {
                union
                {
                    vector3 v3;
                    struct { float x, y, z; };
                };
                float w;
            };
        };

        vector4(float a_x = 0, float a_y = 0, float a_z = 0, float a_w = 1):
            v3(a_x, a_y, a_z), w(a_w)
        {}

        vector4(const vector3 &a_v3, float a_w = 1):
            v3(a_v3), w(a_w)
        {}

        operator vector3() const { return v3; }
    };
}

#endif // __RENDERER_VECTOR4_H
