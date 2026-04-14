// std::function()

#pragma once

template <typename>
class function;

template <typename R, typename... Args>
class function<R(Args...)> {
};
