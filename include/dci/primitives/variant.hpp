/* This file is part of the the dci project. Copyright (C) 2013-2022 vopl, shtoba.
   This program is free software: you can redistribute it and/or modify it under the terms of the GNU Affero General Public
   License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.
   This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty
   of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU Affero General Public License for more details.
   You should have received a copy of the GNU Affero General Public License along with this program. If not, see <https://www.gnu.org/licenses/>. */

#pragma once

#include "integral.hpp"
#include <variant>
#include <cstdint>

namespace dci::primitives
{
    template <class... Ts>
    class Variant
        : public std::variant<Ts...>
    {
    public:
        using std::variant<Ts...>::variant;

              std::variant<Ts...>&  std()       &;
        const std::variant<Ts...>&  std() const &;
              std::variant<Ts...>&& std()       &&;
        const std::variant<Ts...>&& std() const &&;

        template <class T> static constexpr bool canHold();

        template <class T> constexpr bool holds() const;
        constexpr uint32 index() const;
        static constexpr uint32 size();

        decltype(auto) visit(auto&& f)       &;
        decltype(auto) visit(auto&& f) const &;
        decltype(auto) visit(auto&& f)       &&;
        decltype(auto) visit(auto&& f) const &&;

        template <class T>       T&  get()       &;
        template <class T> const T&  get() const &;
        template <class T>       T&& get()       &&;
        template <class T> const T&& get() const &&;

        template <class T> const T&  getOr(const T& def = T{}) const &;

        template <class T> T&  sget() &;
        template <class T> T&& sget() &&;

        auto operator<=>(const Variant& rhs) const;
        bool operator==(const Variant& rhs) const;
    };

    /////////0/////////1/////////2/////////3/////////4/////////5/////////6/////////7
    template <class... Ts>
    std::variant<Ts...>& Variant<Ts...>::std() &
    {
        return static_cast<std::variant<Ts...>&>(*this);
    }

    /////////0/////////1/////////2/////////3/////////4/////////5/////////6/////////7
    template <class... Ts>
    const std::variant<Ts...>& Variant<Ts...>::std() const &
    {
        return static_cast<const std::variant<Ts...>&>(*this);
    }

    /////////0/////////1/////////2/////////3/////////4/////////5/////////6/////////7
    template <class... Ts>
    std::variant<Ts...>&& Variant<Ts...>::std() &&
    {
        return static_cast<std::variant<Ts...>&&>(*this);
    }

    /////////0/////////1/////////2/////////3/////////4/////////5/////////6/////////7
    template <class... Ts>
    const std::variant<Ts...>&& Variant<Ts...>::std() const &&
    {
        return static_cast<const std::variant<Ts...>&&>(*this);
    }

    /////////0/////////1/////////2/////////3/////////4/////////5/////////6/////////7
    template <class... Ts>
    template <class T> constexpr bool Variant<Ts...>::canHold()
    {
        return (std::is_same_v<T, Ts> || ...);
    }

    /////////0/////////1/////////2/////////3/////////4/////////5/////////6/////////7
    template <class... Ts>
    template <class T> constexpr bool Variant<Ts...>::holds() const
    {
        return std::holds_alternative<T>(std());
    }

    /////////0/////////1/////////2/////////3/////////4/////////5/////////6/////////7
    template <class... Ts>
    constexpr uint32 Variant<Ts...>::index() const
    {
        return static_cast<uint32>(std().index());
    }

    /////////0/////////1/////////2/////////3/////////4/////////5/////////6/////////7
    template <class... Ts>
    constexpr uint32 Variant<Ts...>::size()
    {
        return std::variant_size_v<std::variant<Ts...>>;
    }

    /////////0/////////1/////////2/////////3/////////4/////////5/////////6/////////7
    template <class... Ts>
    decltype(auto) Variant<Ts...>::visit(auto&& f) &
    {
        return std::visit(std::forward<decltype(f)>(f), std());
    }

    /////////0/////////1/////////2/////////3/////////4/////////5/////////6/////////7
    template <class... Ts>
    decltype(auto) Variant<Ts...>::visit(auto&& f) const &
    {
        return std::visit(std::forward<decltype(f)>(f), std());
    }

    /////////0/////////1/////////2/////////3/////////4/////////5/////////6/////////7
    template <class... Ts>
    decltype(auto) Variant<Ts...>::visit(auto&& f) &&
    {
        return std::visit(std::forward<decltype(f)>(f), std::move(std()));
    }

    /////////0/////////1/////////2/////////3/////////4/////////5/////////6/////////7
    template <class... Ts>
    decltype(auto) Variant<Ts...>::visit(auto&& f) const &&
    {
        return std::visit(std::forward<decltype(f)>(f), std::move(std()));
    }

    /////////0/////////1/////////2/////////3/////////4/////////5/////////6/////////7
    template <class... Ts>
    template <class T>
    T& Variant<Ts...>::get() &
    {
        return std::get<T>(std());
    }

    /////////0/////////1/////////2/////////3/////////4/////////5/////////6/////////7
    template <class... Ts>
    template <class T>
    const T& Variant<Ts...>::get() const &
    {
        return std::get<T>(std());
    }

    /////////0/////////1/////////2/////////3/////////4/////////5/////////6/////////7
    template <class... Ts>
    template <class T>
    T&& Variant<Ts...>::get() &&
    {
        return std::get<T>(std::move(std()));
    }

    /////////0/////////1/////////2/////////3/////////4/////////5/////////6/////////7
    template <class... Ts>
    template <class T>
    const T&& Variant<Ts...>::get() const &&
    {
        return std::get<T>(std::move(std()));
    }

    /////////0/////////1/////////2/////////3/////////4/////////5/////////6/////////7
    template <class... Ts>
    template <class T>
    const T& Variant<Ts...>::getOr(const T& def) const &
    {
        if(!holds<T>())
        {
            return def;
        }

        return get<T>();
    }

    /////////0/////////1/////////2/////////3/////////4/////////5/////////6/////////7
    template <class... Ts>
    template <class T> T&
    Variant<Ts...>::sget() &
    {
        if(!std::holds_alternative<T>(std()))
        {
            std() = T();
        }
        return get<T>();
    }

    /////////0/////////1/////////2/////////3/////////4/////////5/////////6/////////7
    template <class... Ts>
    template <class T> T&&
    Variant<Ts...>::sget() &&
    {
        if(!std::holds_alternative<T>(std()))
        {
            std() = T();
        }
        return std::move(get<T>());
    }

    /////////0/////////1/////////2/////////3/////////4/////////5/////////6/////////7
    template <class... Ts>
    auto Variant<Ts...>::operator<=>(const Variant& rhs) const
    {
        return std() <=> rhs.std();
    }

    /////////0/////////1/////////2/////////3/////////4/////////5/////////6/////////7
    template <class... Ts>
    bool Variant<Ts...>::operator==(const Variant& rhs) const
    {
        return std() == rhs.std();
    }
}
