/* This file is part of the the dci project. Copyright (C) 2013-2022 vopl, shtoba.
   This program is free software: you can redistribute it and/or modify it under the terms of the GNU Affero General Public
   License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.
   This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty
   of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU Affero General Public License for more details.
   You should have received a copy of the GNU Affero General Public License along with this program. If not, see <https://www.gnu.org/licenses/>. */

#pragma once

#include <map>

namespace dci::primitives
{
    template <class K, class V>
    struct Map : std::map<K, V>
    {
        using Base = std::map<K, V>;

        using Base::Base;
        using Base::operator=;

        Map() = default;
        Map(const Map&) = default;
        Map(Map&&) = default;

        Map& operator=(const Map&) = default;
        Map& operator=(Map&&) = default;

              Base&  std()       & {return *this;}
        const Base&  std() const & {return *this;}
              Base&& std()       &&{return std::move(*this);}
        const Base&& std() const &&{return std::move(*this);}

        auto operator<=>(const Map& rhs) const;
        bool operator==(const Map& rhs) const;
    };

    /////////0/////////1/////////2/////////3/////////4/////////5/////////6/////////7
    template <class K, class V>
    auto Map<K, V>::operator<=>(const Map& rhs) const
    {
        return std() <=> rhs.std();
    }

    /////////0/////////1/////////2/////////3/////////4/////////5/////////6/////////7
    template <class K, class V>
    bool Map<K, V>::operator==(const Map& rhs) const
    {
        return std() == rhs.std();
    }
}
