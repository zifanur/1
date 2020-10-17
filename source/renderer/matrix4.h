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

#ifndef __RENDERER_MATRIX4_H
#define __RENDERER_MATRIX4_H

#include "vector4.h"

namespace zifanur
{
    struct matrix4
    {
        union
        {
            float m[4][4];
            struct { float m11, m12, m13, m14, m21, m22, m23, m24, m31, m32, m33, m34, m41, m42, m43, m44; };
        };

        matrix4(float a11 = 1, float a12 = 0, float a13 = 0, float a14 = 0,
                float a21 = 0, float a22 = 1, float a23 = 0, float a24 = 0,
                float a31 = 0, float a32 = 0, float a33 = 1, float a34 = 0,
                float a41 = 0, float a42 = 0, float a43 = 0, float a44 = 1):
            m11(a11), m12(a12), m13(a13), m14(a14),
            m21(a21), m22(a22), m23(a23), m24(a24),
            m31(a31), m32(a32), m33(a33), m34(a34),
            m41(a41), m42(a42), m43(a43), m44(a44)
        {}
    };

    template <int t_l, int t_m, int t_n>
    inline void multiply(const float *a_1, const float *a_2, float *a_r)
    {
        for (int i = 0; i < t_l; i++)
            for (int j = 0; j < t_n; j++)
            {
                float s = 0;
                for (int k = 0; k < t_m; k++) s += a_1[i * t_m + k] * a_2[k * t_n + j];
                a_r[i * t_n + j] = s;
            }
    }

    inline matrix4 operator *(const matrix4 &o, const matrix4 &a)
    {
        matrix4 l;
        multiply<4, 4, 4>(reinterpret_cast<const float *>(o.m),
                            reinterpret_cast<const float *>(a.m), reinterpret_cast<float *>(l.m));
        return l;
    }

    inline vector4 operator *(const matrix4 &a_m, const vector4 &a_v)
    {
        vector4 l;
        multiply<4, 4, 1>(reinterpret_cast<const float *>(a_m.m),
                            reinterpret_cast<const float *>(a_v.m), reinterpret_cast<float *>(l.m));
        return l;
    }
}

#endif // __RENDERER_MATRIX4_H
