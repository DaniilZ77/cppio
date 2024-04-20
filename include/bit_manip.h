#include <cstdint>
#include <ostream>

namespace manip
{
    const int32_t MAX_NAME_LENGTH = 101;

    class write_le_int32
    {
    private:
        std::int32_t _x;

    public:
        write_le_int32(int32_t x);
        friend std::ostream &operator<<(std::ostream &out, const manip::write_le_int32 &manip);
    };

    class read_le_int32
    {
    private:
        std::int32_t *_x;

    public:
        read_le_int32(int32_t &x);
        friend std::istream &operator>>(std::istream &in, read_le_int32 manip);
    };

    class write_bool
    {
    private:
        bool _x;

    public:
        write_bool(bool x);
        friend std::ostream &operator<<(std::ostream &out, const write_bool &manip);
    };

    class read_bool
    {
    private:
        bool *_x;

    public:
        read_bool(bool &x);
        friend std::istream &operator>>(std::istream &in, read_bool manip);
    };

    class write_c_str
    {
    private:
        char _s[MAX_NAME_LENGTH];

    public:
        write_c_str(const char *s);
        friend std::ostream &operator<<(std::ostream &out, const write_c_str &manip);
    };

    class read_c_str
    {
    private:
        char *_s;
        size_t _size;

    public:
        read_c_str(char *s, size_t size);
        friend std::istream &operator>>(std::istream &in, const read_c_str &manip);
    };

}