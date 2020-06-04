# Overview

This is a C++ wrapper around OpenSSL's C API. It's goal is to use modern C++
features to permit a more expressive API, so that users can focus less on
lifetimes and copying and more on what they need, which is the security aspect
of C++.

Currently the top-level namespace is simply `aegis`, however this might be
changed to `ssl` at some point. Additionally, the library name might be changed
at some point as well. These are all in flux

`aegis` currently depends on [`netlify::apex`](https://github.com/netlify/apex)

Please note, this library has not been tested in every aspect of its
development. Expect high churn/API changes.
