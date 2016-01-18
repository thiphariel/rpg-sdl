/**
 * @author Thiphariel - 14/01/2016
 */

#ifndef BINARY_H_INCLUDED
#define BINARY_H_INCLUDED

#include <fstream>

template<typename T>
std::ostream& binary_write(std::ostream& stream, const T& value)
{
    return stream.write(reinterpret_cast<const char*>(&value), sizeof(T));
}

template<typename T>
std::istream& binary_read(std::istream& stream, T& value)
{
    return stream.read(reinterpret_cast<char*>(&value), sizeof(T));
}

#endif // BINARY_H_INCLUDED
