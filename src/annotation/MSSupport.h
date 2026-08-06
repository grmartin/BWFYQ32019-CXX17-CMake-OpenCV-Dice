#ifndef CVDICE_MSSUPPORT_H
#define CVDICE_MSSUPPORT_H

// Marks an intentionally-unused variable (e.g. a caught exception whose
// value isn't needed) to silence unused-variable warnings across MSVC/GCC/Clang.
#define UNUSED_REF(x) (void)(x)

// Documents which aggregate-initializer field a positional value belongs to,
// e.g. `STRUKEY(index) 3` reads like a named/designated `.index = 3` without
// depending on C++20 designated initializers (this project targets strict
// C++17, built with CMAKE_CXX_EXTENSIONS OFF). Expands to nothing -- the
// value list must still be in the struct's declared field order.
#define STRUKEY(name)

#endif //CVDICE_MSSUPPORT_H
