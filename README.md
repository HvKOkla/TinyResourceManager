TinyResourceManager Lightweight header-only C++20 resource manager for games and real-time apps.

Features:

•	Header-only: drop ResourceManager.hpp into your project

•	Smart caching: avoids duplicate disk loads

•	Modern C++20 (stdshared_ptr, stdfilesystem, concepts)

•	Automatic cleanup of unused resources

Quick start:

1.	Copy ResourceManager.hpp into your include path
2.	#include "ResourceManager.hpp"
3.	Use CoreResourceManager<T> to load resources:
4.	Example: available in ResourceManager/app/main.cpp


Requirement:
•	C++20 compiler (MSVC/Clang/GCC)
•	CMake >= 3.15 (if using provided build files)

License MIT See LICENCE for more information

Contributing
You can contribute to the project in several ways: by proposing new ideas, reporting bugs you encounter, or improving existing code. If you would like to submit a change, you can open a Pull Request so that we can review your changes and incorporate them into the project if necessary.
   
