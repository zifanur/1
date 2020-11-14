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

#ifndef __RENDERER_F_RGB_H
#define __RENDERER_F_RGB_H

namespace zifanur
{
    struct f_rgb
    {
        union
        {
            struct { float r, g, b; };
            float f[3];
        };

        f_rgb(float a_r = 0, float a_g = 0, float a_b = 0): r(a_r), g(a_g), b(a_b) {}
    };

    inline f_rgb &operator +=(f_rgb &a_o, const f_rgb &a_a)
    {
        for (int i = 0; i < 3; i++) a_o.f[i] += a_a.f[i];
        return a_o;
    }

    inline f_rgb operator +(f_rgb a_o, const f_rgb &a_a) { return a_o += a_a; }

    inline f_rgb &operator *=(f_rgb &a_o, const f_rgb &a_a)
    {
        for (int i = 0; i < 3; i++) a_o.f[i] *= a_a.f[i];
        return a_o;
    }

    inline f_rgb operator *(f_rgb a_o, const f_rgb &a_a) { return a_o *= a_a; }

    inline f_rgb &operator /=(f_rgb &a_rgb, float a_div)
    {
        for (int i = 0; i < 3; i++) a_rgb.f[i] /= a_div;
        return a_rgb;
    }

    inline f_rgb operator /(f_rgb a_rgb, float a_div) { return a_rgb /= a_div; }
}

#endif // __RENDERER_F_RGB_H
