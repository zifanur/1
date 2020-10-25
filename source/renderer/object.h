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

#ifndef __RENDERER_OBJECT_H
#define __RENDERER_OBJECT_H

#include "trace_var.h"
#include "func.h"

namespace zifanur
{
    class object
    {
    public:
        object() {}

        object(const object &a) = delete;
        object &operator =(const object &a) = delete;

        virtual ~object() {}

        virtual bool hit(trace_var &a) { return false; }
    };
}

#endif // __RENDERER_OBJECT_H
