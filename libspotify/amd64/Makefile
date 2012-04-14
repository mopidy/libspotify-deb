prefix ?= /usr/local

all:
	$(error "Usage: make [prefix=/install/me/here] install | uninstall")

install:
	mkdir -p $(prefix)/include/libspotify
	install include/libspotify/api.h $(prefix)/include/libspotify

	mkdir -p $(prefix)/lib
	install -T lib/libspotify.so.11 $(prefix)/lib/libspotify.so.11.1.60

	cd $(prefix)/lib && ln -sf libspotify.so.11.1.60 libspotify.so.11 && ln -sf libspotify.so.11.1.60 libspotify.so

	mkdir -p $(prefix)/lib/pkgconfig
	sed -e s:PKG_PREFIX:$(prefix):g <lib/pkgconfig/libspotify.pc >$(prefix)/lib/pkgconfig/libspotify.pc

	ldconfig

uninstall:
	rm -rf $(prefix)/include/libspotify
	rm -f  $(prefix)/lib/libspotify.so.11.1.60
	rm -f  $(prefix)/lib/libspotify.so.11
	rm -f  $(prefix)/lib/libspotify.so
	rm -f  $(prefix)/lib/pkgconfig/libspotify.pc
