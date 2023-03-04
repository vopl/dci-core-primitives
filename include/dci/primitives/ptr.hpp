/* This file is part of the the dci project. Copyright (C) 2013-2023 vopl, shtoba.
   This program is free software: you can redistribute it and/or modify it under the terms of the GNU Affero General Public
   License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.
   This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty
   of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU Affero General Public License for more details.
   You should have received a copy of the GNU Affero General Public License along with this program. If not, see <https://www.gnu.org/licenses/>. */

#pragma once

#include <memory>

namespace dci::primitives
{
    template <class T>
    struct Ptr : std::shared_ptr<T>
    {
        using Base = std::shared_ptr<T>;

        using Base::Base;
        using Base::operator=;

        Ptr() = default;
        Ptr(const Ptr&) = default;
        Ptr(Ptr&&) = default;

        Ptr& operator=(const Ptr&) = default;
        Ptr& operator=(Ptr&&) = default;

              Base&  std()       & {return *this;}
        const Base&  std() const & {return *this;}
              Base&& std()       &&{return std::move(*this);}
        const Base&& std() const &&{return std::move(*this);}

        auto operator<=>(const Ptr& rhs) const = default;
    };
}
