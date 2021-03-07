| ![LOGO](http://i.imgur.com/uBd4iIz.png) | <h1>Libevhtp</h1> |
| :------------- | -------------: |

## Changes in This Branch
* Integrated and currently working on completing the websocket impementation from [an old fork](https://github.com/zerotao/libevhtp/tree/libevhtp2).
* SSL slowdown hack/fix [issue 160](https://github.com/criticalstack/libevhtp/issues/160).
* Scheduling fix when thread is in a callback.
* Onig regular expression matcher now uses native instead of posix compatible calls [issue 162](https://github.com/criticalstack/libevhtp/issues/162).
* Some behavioral changes when matching urls.

## Required Dependencies
* [gcc](http://gcc.gnu.org/) or [clang](https://clang.llvm.org/)
* [Libevent2](http://libevent.org)
* [CMake](http://cmake.org)

## Optional Dependencies
* [OpenSSL](http://openssl.org)
* pthreads
* [onig (regex)](https://github.com/kkos/oniguruma)

## Building
* cd build
* cmake ..
* make
* make examples
