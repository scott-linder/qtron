#ifndef CLAMP_H
#define CLAMP_H

template <typename T>
inline auto clamp(T val, T min, T max) -> T
{
    return std::min(std::max(min, val), max);
}

#endif // CLAMP_H
