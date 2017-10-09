#ifndef PROTOCOL_HPP__
# define PROTOCOL_HPP__

# ifndef RD_SIZE_SIZE
#  define RD_SIZE_SIZE sizeof(uint16_t)
# endif /* !RD_SIZE_SIZE */

# ifndef RD_SIZE_MODIFIER
#  define RD_SIZE_MODIFIER sizeof(uint8_t)
# endif /* !RD_SIZE_MODIFIER */

enum Modifiers {
    Shift       = 1,
    Ctrl        = 2,
    Alt         = 4,
    Super       = 8,
    AltGr       = 16,
    Arrow       = 32,
    FunctionKey = 64,
    MouseButton = 128
};

struct Packet {
    uint16_t size;
    uint8_t modifier;
    uint8_t value;

    uint16_t mouseX;
    uint16_t mouseY;

    uint64_t timestamp;
    char process_name[0];
}; //__attribute__((__packed__));

#endif /* end of include guard: PROTOCOL_HPP__ */
