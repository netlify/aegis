Object Stacks
=============

Within OpenSSL, there is the concept of a *stack*. In practice, these stacks
are actually dynamic arrays with a poorly chosen name. Despite this, aegis
provides a *generic* stack interface, though it requires an explicit
specialization for each type to be generated. These are currently generated
with macros as expecting users to define each one is unnecessary as all stacks
follow the same naming conventions within OpenSSL. However, because C++20 *does
not* currently support reflection, we must fallback on the C preprocessor.

That said, the *current* design of :struct:`stack\<T>` is to return a
:expr:`T*` directly. However, at some point the API will be extended such that
if `T*` is *not* an OpenSSL type, it will be a proxy wrapper around a `T*`,
such that values have correct lifetimes, and a wrapped API.

.. namespace:: aegis

.. struct:: template <class T> stack
