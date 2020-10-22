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

#include "object.h"
#include "triangle.h"

namespace zifanur
{
    class mesh: public object
    {
    public:
        mesh(triangle *a_t = nullptr) :m_t(a_t) {}

        mesh(const mesh &a) = delete;
        mesh &operator =(const mesh &a) = delete;

        ~mesh() override { delete []m_t; }

    private:
        triangle *m_t = nullptr;
    };
}

#endif // __RENDERER_MESH_H
