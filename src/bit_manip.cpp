#include "bit_manip.h"
#include <cstring>
#include <fstream>
#include <iostream>
#include <istream>
#include <stdexcept>
#include <exception>

namespace manip
{
    // write_le_int32 implementation

    write_le_int32::write_le_int32(int32_t x) : _x(x) {}

    std::ostream &operator<<(std::ostream &out, const write_le_int32 &manip)
    {
        char bytes[4];
        bytes[0] = manip._x & 0xFF;
        bytes[1] = (manip._x >> 8) & 0xFF;
        bytes[2] = (manip._x >> 16) & 0xFF;
        bytes[3] = (manip._x >> 24) & 0xFF;
        out.write(bytes, 4);
        return out;
    }

    // read_le_int32 implementation

    read_le_int32::read_le_int32(int32_t &x) : _x(&x) {}

    std::istream &operator>>(std::istream &in, read_le_int32 manip)
    {
        char bytes[4];
        in.read(bytes, 4);
        *manip._x = ((unsigned char)bytes[3] << 24) + ((unsigned char)bytes[2] << 16) + ((unsigned char)bytes[1] << 8) + (unsigned char)bytes[0];
        return in;
    }

    // write_bool implementation

    write_bool::write_bool(bool x) : _x(x) {}

    std::ostream &operator<<(std::ostream &out, const write_bool &manip)
    {
        char byte = manip._x ? 1 : 0;
        out.write(&byte, 1);
        return out;
    }

    // read_bool implementation

    read_bool::read_bool(bool &x) : _x(&x) {}

    std::istream &operator>>(std::istream &in, read_bool manip)
    {
        char byte;
        in.read(&byte, 1);
        *manip._x = byte;
        return in;
    }

    // write_c_str implementation

    write_c_str::write_c_str(const char *s) { strcpy(_s, s); }

    std::ostream &operator<<(std::ostream &out, const write_c_str &manip)
    {
        out.write(manip._s, strlen(manip._s) + 1);
        return out;
    }

    // read_c_str implementation

    read_c_str::read_c_str(char *s, size_t size) : _s(s), _size(size) {}

    std::istream &operator>>(std::istream &in, const read_c_str &manip)
    {
        size_t i = 0;
        while (in.get(manip._s[i]) && i < manip._size)
        {
            if (manip._s[i] == 0)
                break;
            i += 1;
        }
        if (i >= manip._size && manip._s[i - 1] != 0)
        {
            std::string exceptionMessage = "Format exception: expected to have at most " + std::to_string(manip._size) + " characters in a file";
            throw std::invalid_argument(exceptionMessage);
        }
        return in;
    }
}
