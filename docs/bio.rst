Binary I/O Operations
=====================

OpenSSL provides a fairly generic (for C) API for plugging binary io sources
into the OpenSSL API. Because OpenSSL must read/parse various amounts of data,
this pluggability does provide a quite flexible way of operating. *However*,
because of the design of the API it is quite difficult to operate on, and as
such providing even just a basic RAII wrapper around the API is useful.

.. namespace:: aegis::io

.. struct:: stream_view

   A :struct:`stream_view` acts as a non-owning reference around a byte stream
   of some kind. While the underlying :struct:`BIO` type itself is refcounted,
   the stream of data it *views* is not. The underlying API used is not
   documented as being a non-owning handle to the byte stream.

   .. danger::

      A :struct:`stream_view` MUST NOT outlive the byte stream it has been
      given

   .. function:: stream_view(apex::span<apex::byte> const& data) noexcept
                 stream_view(std::string_view const& data) noexcept
                 stream_view(std::string const& data) noexcept

      A :struct:`stream_view <aegis::io::stream_view>` will act as a view over
      any of the parameters provided above.

   .. function:: stream_view(apex::span<apex::byte>&&) = delete;
                 stream_view(std::string_view&&) = delete;
                 stream_view(std::string&&) = delete;

      These constructors are deleted to prevent rvalue references from being
      passed to a :struct:`stream_view <aegis::io::stream_view>`. However,
      because of limitations of C++, there is very little we can do to enforce
      that no temporaries are passed to construct a :struct:`stream_view
      <aegis::io::stream_view>`.

   .. function:: BIO* stream_view::get () const noexcept

      Inherited from the :struct:`retain_handle\<T>` to return the underlying
      :struct:`BIO`.
