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

#ifndef __RENDERER_MATERIAL_H
#define __RENDERER_MATERIAL_H

#include "trace_var.h"
#include "def.h"

namespace zifanur
{
    class material
    {
    public:
        material() {}

        material(const material &a) = delete;
        material &operator =(const material &a) = delete;

        virtual ~material() {}

        virtual trace_var &hit(trace_var &a) { return a; }
        virtual trace_var &prop(trace_var &a);
    };

    inline trace_var &material::prop(trace_var &a)
    {
        const float l_alpha = std::uniform_real_distribution<float>(0, 2 * s_pi_f)(a.m_random),
                    l_beta = std::uniform_real_distribution<float>(0, s_pi_f / 2)(a.m_random);
        const float l_cos_beta = std::cos(l_beta);
        a.m_prop_in_mat = vector3(l_cos_beta * std::cos(l_alpha), l_cos_beta * std::sin(l_alpha), std::sin(l_beta));
        return a;
    }
}

#endif // __RENDERER_MATERIAL_H
