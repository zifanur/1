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

#ifndef __RENDERER_MESH_FROM_OBJ_H
#define __RENDERER_MESH_FROM_OBJ_H

#include "mesh.h"
#include <array>
#include <vector>
#include <filesystem>
#include <fstream>
#include <sstream>

namespace zifanur
{
    void remove_utf8_bom(std::string &a)
    {
        if (static_cast<unsigned char>(a[0]) != 0xef) return;
        if (a.size() <= 3) { a.clear(); return; }
        a.erase(std::begin(a), std::begin(a) + 3);
    }

    std::unique_ptr<mesh> from_obj(const std::filesystem::path &a_filepath, material *a_material)
    {
        using index_triple = std::array<size_t, 3>;

        std::ifstream l_ifs(a_filepath, std::ios::in);
        if (!l_ifs.is_open()) return std::unique_ptr<mesh>();

        std::vector<vector3> l_vertices;
        std::vector<index_triple> l_faces;
        bool l_first_line = true;
        for (std::string l_line; std::getline(l_ifs, l_line); )
        {
            if (l_line.empty()) continue;
            if (l_first_line) { l_first_line = false; remove_utf8_bom(l_line); }
            std::stringstream l_lss(l_line);
            std::string l_op;
            if (!std::getline(l_lss, l_op, ' ')) continue;
            if (l_op == "v")
            {
                vector3 l_v;
                for (size_t i = 0; i < 3; i++) if (!(l_lss >> l_v.m[i])) return std::unique_ptr<mesh>();
                l_vertices.emplace_back(l_v);
            }
            else if (l_op == "f")
            {
                index_triple l_face;
                std::string l_rec;
                for (size_t i = 0; i < 3 && std::getline(l_lss, l_rec, ' '); i++)
                {
                    std::stringstream l_rss(l_rec);
                    if (!(l_rss >> l_face[i])) return std::unique_ptr<mesh>();
                }
                l_faces.emplace_back(l_face);
            }
        }

        l_ifs.close();

        std::unique_ptr<zifanur::triangle []> l_t(new zifanur::triangle [l_faces.size()]);
        for (size_t i = 0; i < l_faces.size(); i++)
        {
            const auto &l_face = l_faces[i];
            for (size_t j = 0; j < 3; j++)
            {
                const size_t l_index = l_face[j] - 1;
                if (l_index >= l_vertices.size()) return std::unique_ptr<mesh>();
                l_t[i].v3[j] = l_vertices[l_index];
            }
        }

        auto l_r(std::make_unique<mesh>(unsigned(l_faces.size()), l_t.get(), a_material));
        l_t.release();
        return l_r;
    }
}

#endif // __RENDERER_MESH_FROM_OBJ_H
