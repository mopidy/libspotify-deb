TARGET=spshell
LDLIBS += -lreadline
CFLAGs += -Werror

include ../common.mk

$(TARGET): spshell.o spshell_posix.o appkey.o cmd.o browse.o search.o toplist.o inbox.o star.o social.o playlist.o
	$(CC) $(CFLAGS) $(LDFLAGS) $(LDLIBS) $^ -o $@
ifdef DEBUG
ifeq ($(shell uname),Darwin)
	install_name_tool -change @loader_path/../Frameworks/libspotify.framework/libspotify @rpath/libspotify.so $@
endif
endif