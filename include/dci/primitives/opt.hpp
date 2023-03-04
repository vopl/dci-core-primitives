/* This file is part of the the dci project. Copyright (C) 2013-2023 vopl, shtoba.
   This program is free software: you can redistribute it and/or modify it under the terms of the GNU Affero General Public
   License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.
   This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty
   of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU Affero General Public License for more details.
   You should have received a copy of the GNU Affero General Public License along with this program. If not, see <https://www.gnu.org/licenses/>. */

#pragma once

#include <optional>

namespace dci::primitives
{
    template <class T>
    struct Opt : std::optional<T>
    {
        using Base = std::optional<T>;

        using Base::Base;
        using Base::operator=;

        Opt() = default;
        Opt(const Opt&) = default;
        Opt(Opt&&) = default;

        Opt& operator=(const Opt&) = default;
        Opt& operator=(Opt&&) = default;

              Base&  std()       & {return *this;}
        const Base&  std() const & {return *this;}
              Base&& std()       &&{return std::move(*this);}
        const Base&& std() const &&{return std::move(*this);}

        friend bool operator==(const Opt& lhs, const Opt& rhs) = default;
        friend auto operator<=>(const Opt& lhs, const Opt& rhs) = default;

        friend bool operator==(const Opt& lhs, std::nullptr_t)
        {
            return bool(lhs) == false;
        }

        friend auto operator<=>(const Opt& lhs, std::nullptr_t)
        {
            return bool(lhs) <=> false;
        }

        friend bool operator==(std::nullptr_t, const Opt& rhs)
        {
            return false == bool(rhs);
        }

        friend auto operator<=>(std::nullptr_t, const Opt& rhs)
        {
            return false <=> bool(rhs);
        }

        friend bool operator==(const Opt& lhs, const T& rhs)
        {
            return bool(lhs) ? *lhs == rhs : false;
        }

        friend auto operator<=>(const Opt& lhs, const T& rhs)
        {
            return bool(lhs) ? *lhs <=> rhs : std::strong_ordering::less;
        }

        friend bool operator==(const T& lhs, const Opt& rhs)
        {
            return bool(rhs) ? lhs == *rhs : false;
        }

        friend auto operator<=>(const T& lhs, const Opt& rhs)
        {
            return bool(rhs) ? lhs <=> *rhs : std::strong_ordering::greater;
        }
    };
}

#if defined(__GNUC__) && defined(_GLIBCXX_OPTIONAL)
namespace std
{
    template<typename _Tp>
      inline constexpr bool __is_optional_v<dci::primitives::Opt<_Tp>> = true;
}
#endif
