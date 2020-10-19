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

#ifndef __RENDERER_RENDERER_INLINE_H
#define __RENDERER_RENDERER_INLINE_H

#include "renderer.h"

namespace zifanur
{
    inline matrix4 renderer::look_at(const vector3 &a_from, const vector3 &a_to, const vector3 &a_up)
    {
        //https://docs.microsoft.com/en-us/windows/win32/direct3d9/d3dxmatrixlookatlh
        const vector3 l_z(normalized(a_to - a_from));
        const vector3 l_x(normalized(cross(l_z, a_up)));
        const vector3 l_y(cross(l_x, l_z));
        return matrix4(vector4(l_x, -dot(l_x, a_from)),
                        vector4(l_y, -dot(l_y, a_from)),
                        vector4(l_z, -dot(l_z, a_from)));
    }
}

#endif //__RENDERER_RENDERER_INLINE_H
