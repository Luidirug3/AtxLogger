# AtxLogger
A simple spdlog wrapper

# Installation with vcpkg 
To consume the library as a vcpkg package, copy the atx-logger folder to the vcpkg/ports path. 
Inside the portfile.cmake file, replace the REF hash with the hash of the commit you want to refer to or with the corresponding TAG.
SHA512 is obtained following the failure of the first compilation. 
Replace the SHA512 with the correct value.
Now you can install the library either from the command line or in manifest mode as if it were any other vcpkg package.
