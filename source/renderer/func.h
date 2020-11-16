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

#ifndef __RENDERER_FUNC_H
#define __RENDERER_FUNC_H

#include "matrix4.h"

namespace zifanur
{
    inline vector3 perp(const vector3 &a)
    {
        //https://stackoverflow.com/a/38407105
        return std::abs(a.z) < std::abs(a.x)? vector3(a.y, -a.x): vector3(0, -a.z, a.y);
    }

    inline matrix4 transf(const vector3 &a_from, const vector3 &a_to, const vector3 &a_up)
    {
        //https://docs.microsoft.com/en-us/windows/win32/direct3d9/d3dxmatrixlookatlh
        const vector3 l_za(normalized(a_from - a_to)),
                        l_xa(normalized(cross(a_up, l_za))),
                        l_ya(cross(l_za, l_xa));
        return matrix4(vector4(l_xa, -dot(l_xa, a_from)),
                        vector4(l_ya, -dot(l_ya, a_from)),
                        vector4(l_za, -dot(l_za, a_from)));
    }

    inline matrix4 shifted(const matrix4 &a_m, const vector3 &m_v)
    {
        matrix4 l(a_m);
        for (int i = 0; i < 3; i++) l.m[i][3] += m_v.m[i];
        return l;
    }

    inline matrix4 scale_and_move(const vector3 &a_scale, const vector3 &a_shift)
    {
        matrix4 l;
        for (int i = 0; i < 3; i++) { l.m[i][i] = a_scale.m[i]; l.m[i][3] = a_shift.m[i]; }
        return l;
    }
}

#endif //__RENDERER_FUNC_H
