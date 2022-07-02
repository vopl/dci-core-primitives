/* This file is part of the the dci project. Copyright (C) 2013-2022 vopl, shtoba.
   This program is free software: you can redistribute it and/or modify it under the terms of the GNU Affero General Public
   License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.
   This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty
   of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU Affero General Public License for more details.
   You should have received a copy of the GNU Affero General Public License along with this program. If not, see <https://www.gnu.org/licenses/>. */

#pragma once

#include <set>

namespace dci::primitives
{
    template <class T>
    struct Set : std::set<T>
    {
        using Base = std::set<T>;

        using Base::Base;
        using Base::operator=;

        Set() = default;
        Set(const Set&) = default;
        Set(Set&&) = default;

        Set& operator=(const Set&) = default;
        Set& operator=(Set&&) = default;

              Base&  std()       & {return *this;}
        const Base&  std() const & {return *this;}
              Base&& std()       &&{return std::move(*this);}
        const Base&& std() const &&{return std::move(*this);}

        auto operator<=>(const Set& rhs) const;
        bool operator==(const Set& rhs) const;
    };

    /////////0/////////1/////////2/////////3/////////4/////////5/////////6/////////7
    template <class T>
    auto Set<T>::operator<=>(const Set& rhs) const
    {
        return std() <=> rhs.std();
    }

    /////////0/////////1/////////2/////////3/////////4/////////5/////////6/////////7
    template <class T>
    bool Set<T>::operator==(const Set& rhs) const
    {
        return std() == rhs.std();
    }
}
