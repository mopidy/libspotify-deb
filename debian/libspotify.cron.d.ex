#
# Regular cron jobs for the libspotify package
#
0 4	* * *	root	[ -x /usr/bin/libspotify_maintenance ] && /usr/bin/libspotify_maintenance
