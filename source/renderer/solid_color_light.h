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

#ifndef __RENDERER_SOLID_COLOR_LIGHT_H
#define __RENDERER_SOLID_COLOR_LIGHT_H

#include "material.h"

namespace zifanur
{
    class solid_color_light: public material
    {
    public:
        solid_color_light(const f_rgb &a_fraction, const f_rgb &a_emission):
            m_fraction(a_fraction), m_emission(a_emission)
        {}

        solid_color_light(const solid_color_light &a) = delete;
        solid_color_light &operator =(const solid_color_light &a) = delete;

        virtual ~solid_color_light() {}

        virtual trace_var &hit(trace_var &a) override { return a; }
        virtual trace_var &prop(trace_var &a) override;

    private:
        f_rgb m_fraction, m_emission;
    };

    trace_var &solid_color_light::prop(trace_var &a)
    {
        a.m_mtv.m_prop = vector3(0, 0, 1);
        a.m_light_encounter = true;
        a.m_accum += a.m_absorb * m_emission;
        a.m_absorb *= m_fraction;
        return a;
    }
}

#endif // __RENDERER_SOLID_COLOR_LIGHT_H
