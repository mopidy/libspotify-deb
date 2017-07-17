libspotify Debian package
=========================

This is the source for the Mopidy project's Debian package of libspotify. It is
in no way specific to Mopidy and may be used with any application to gain
access to the Spotify music streaming service.


Install from APT archive
------------------------

If you want to install the package, you can do so from the Mopidy APT archive
at https://apt.mopidy.com/.

#. Add the archive's GPG key::

       wget -q -O - https://apt.mopidy.com/mopidy.gpg | sudo apt-key add -

#. Add the following to ``/etc/apt/sources.list``, or if you have the directory
   ``/etc/apt/sources.list.d/``, add it to a file called ``mopidy.list`` in that
   directory::

       sudo wget -q -O /etc/apt/sources.list.d/mopidy.list https://apt.mopidy.com/stretch.list

#. Install packages::

       sudo apt-get update
       sudo apt-get install libspotify12 libspotify-dev
