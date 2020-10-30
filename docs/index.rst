Overview
========

Netlify Aegis is a C++ wrapper around OpenSSL's C API. It's goal is to use
modern C++ features to permit not only a more expressive API, but a less error
prone experience so that users can focus *less* on lifetimes and copying and
more on what they need which is the security APIs provided by OpenSSL.

The top-level namespace is simply :expr:`aegis`, and all headers are
available via the :file:`<aegis/{filename}.hpp>` naming convention.

Netlify Aegis currently depends on `netlify::apex
<https://github.com/netlify/apex>`_. It is automatically fetched during the
build process.

The documentation also provides an :ref:`index <genindex>`

.. toctree::
   connection
   context
   errors
   stack
   x509
   bio
   ssl

