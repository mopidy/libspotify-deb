libspotify Debian package
=========================

This is the source for the Mopidy project's Debian package of libspotify. It is
in no way specific to Mopidy and may be used with any application to gain
access to the Spotify music streaming service.


Install from APT archive
------------------------

If you want to install the package, you can do so from the Mopidy APT archive
at http://apt.mopidy.com/.

#. Add the archive's GPG key::

       wget -q -O - http://apt.mopidy.com/mopidy.gpg | sudo apt-key add -

#. Add the following to ``/etc/apt/sources.list``, or if you have the directory
   ``/etc/apt/sources.list.d/``, add it to a file called ``mopidy.list`` in that
   directory::

       # Mopidy APT archive
       deb http://apt.mopidy.com/ stable main contrib non-free
       deb-src http://apt.mopidy.com/ stable main contrib non-free

#. Install packages::

       sudo apt-get update
       sudo apt-get install libspotify6 libspotify-dev

   As most releases of libspotify increases the ``SONAME``, the latest package
   may be named ``libspotify7`` instead of ``libspotify6``. To check what
   packages you can choose from, run::

       apt-cache search libspotify
