/* This file is part of the the dci project. Copyright (C) 2013-2021 vopl, shtoba.
   This program is free software: you can redistribute it and/or modify it under the terms of the GNU Affero General Public
   License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.
   This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty
   of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU Affero General Public License for more details.
   You should have received a copy of the GNU Affero General Public License along with this program. If not, see <https://www.gnu.org/licenses/>. */

#pragma once

#include <string>
#include <type_traits>

namespace dci::primitives
{
    //using String    = std::string;
    struct String : std::string
    {
        using Base = std::string;

        using Base::Base;
        String(const Base& b) : Base{b} {}
        String(Base&& b) : Base{std::move(b)} {}

        using Base::operator=;

        String() = default;
        String(const String&) = default;
        String(String&&) = default;

        String& operator=(const String&) = default;
        String& operator=(String&&) = default;

        template <class S>
        requires (std::is_assignable_v<S, Base>)
        String& operator=(const S& s) noexcept(std::is_nothrow_assignable_v<S, Base>)
        {
            Base::operator=(s);
            return *this;
        }

        template <class S>
        requires (std::is_assignable_v<S, Base>)
        String& operator=(S&& s) noexcept(std::is_nothrow_assignable_v<S, Base>)
        {
            Base::operator=(std::move(s));
            return *this;
        }

              Base&  std()       & {return *this;}
        const Base&  std() const & {return *this;}
              Base&& std()       &&{return std::move(*this);}
        const Base&& std() const &&{return std::move(*this);}

        friend bool operator==(const String& lhs, const String& rhs)
        {
            return lhs.std() == rhs.std();
        }

        friend auto operator<=>(const String& lhs, const String& rhs)
        {
            return lhs.std() <=> rhs.std();
        }

        template <class Rhs> requires(!std::is_same_v<Rhs, String>)
        friend bool operator==(const String& lhs, const Rhs& rhs)
        {
            return lhs.std() == rhs;
        }

        template <class Rhs> requires(!std::is_same_v<Rhs, String>)
        friend auto operator<=>(const String& lhs, const Rhs& rhs)
        {
            return lhs.std() <=> rhs;
        }

        template <class Lhs> requires(!std::is_same_v<Lhs, String>)
        friend bool operator==(const Lhs& lhs, const String& rhs)
        {
            return lhs == rhs.std();
        }

        template <class Lhs> requires(!std::is_same_v<Lhs, String>)
        friend auto operator<=>(const Lhs& lhs, const String& rhs)
        {
            return lhs <=> rhs.std();
        }
    };
}
