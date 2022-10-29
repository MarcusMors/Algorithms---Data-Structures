// Copyright (C) 2022 José Enrique Vilca Campana
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU Affero General Public License as
// published by the Free Software Foundation, either version 3 of the
// License, or (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU Affero General Public License for more details.
//
// You should have received a copy of the GNU Affero General Public License
// along with this program.  If not, see <http://www.gnu.org/licenses/>.


//-----------------------------------------------------------------------------
// What errors Can it detect?
// Heap buffer overflow
// Stack buffer overflow
// Global buffer overflow
// Use after free
// Use after return
// Use after scope
// Initialization order bugs
// Memory leaks

// How does it work?
// creates shadow memory by compiler instrumentation.
// if shadow_is_poisoned(ptr) : Report error
//-----------------------------------------------------------------------------

#include <iostream>
#include <string>
#include <vector>

//-----------------------------------------------------------------------------
volatile char *global_ptr;

__attribute__((noinline)) void FunctionThatEscapesLocalObject()
{
  char local[100];
  global_ptr = &local[0];
}

char global_array[10];

//-----------------------------------------------------------------------------

int main(int argc, char **argv)
{
  if (argc != 2) {
    std::cout << "Usage: main_address_sanitize <choice>" << std::endl;
    return -1;
  }

  int choice = std::stoi(argv[1]);
  std::cout << "choice: " << choice << std::endl;

  switch (choice) {
  case 0: {
    //  SEGV on unknown address.
    char *ptr = nullptr;
    *ptr = 5;
    break;
  }

  case 1: {
    // SEGV on unknown address.
    char *ptr = (char *)1;
    *ptr = 5;
    break;
  }

  case 2: {
    // SEGV on unknown address.
    std::vector<char> v;
    std::cout << v[100] << std::endl;
    break;
  }

  case 3: {
    // Heap buffer overflow (Example 1).
    std::vector<char> v(1);
    std::cout << v[100] << std::endl;
    break;
  }

  case 4: {
    // Heap buffer overflow (Example 2).
    char *array = new char[16];
    array[16] = 1;// BOOM!
    break;
  }

  case 5: {
    // Heap buffer overflow (Example 3).
    char *ptr = new char;
    *ptr = 'a';
    std::cout << *(ptr + 1) << std::endl;
    break;
  }

  case 6: {
    // Heap use after free.
    char *p = new char;
    delete p;
    std::cout << *p << std::endl;
    break;
  }

  case 7: {
    // Double-free.
    char *p = new char;
    delete p;
    delete p;
    break;
  }

  case 8: {
    // Stack buffer overflow.
    char array[16];
    array[20] = 1;// BOOM!
    break;
  }

  case 9: {
    // stack-use-after-scope
    volatile char *ptr = nullptr;
    {
      char x = 0;
      ptr = &x;
    }
    *ptr = 5;
    break;
  }
  case 10: {
    // stack-use-after-return
    // Set this env variable before running:
    // export g++ ASAN_OPTIONS=detect_stack_use_after_return=1
    // export clang -fsanitize-address-use-after-return=never/runtime/always
    FunctionThatEscapesLocalObject();
    return global_ptr[0];
  }

  case 11: {
    // global-buffer-overflow
    // char global_array[10]; // global variable.
    global_array[11] = 1;// Boom!
    break;
  }

  case 12: {
    // global-buffer-overflow
    static char array[10];
    array[11] = 1;// Boom!
    break;
  }

  case 13: {
    // Leak detection (Doesn't work on Mac?)
    // Set this env variable before running:
    // export ASAN_OPTIONS=detect_leaks=1
    // Or with bazel:
    /*
      bazel run --config=asan //src/main:main_address_sanitize \
      --run_under='export ASAN_OPTIONS=detect_leaks=1 &&' -- 13
    */
    char *p = new char;
    *p = 10;
    std::cout << "*p: " << *p << std::endl;
    break;
  }

  default:
    std::cout << "Error: Invalid choice value: " << choice << std::endl;
  }

  return 0;
}

//-----------------------------------------------------------------------------
// Limitations
// Memory corruption must happen in your program trace
// Doesn't detect uninitialized memory reads (use memory sanitizer)
// Memory and runtime overhead
//-----------------------------------------------------------------------------

// tutorial: https://youtu.be/hhpzDFvXopk
// author: Ari Saif
// repository: https://github.com/ourarash/cpp-template/blob/master/src/main/main_address_sanitize.cc
