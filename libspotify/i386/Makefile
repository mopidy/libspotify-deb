prefix ?= /usr/local

all:
	$(error "Usage: make [prefix=/install/me/here] install | uninstall")

install:
	mkdir -p $(prefix)/include/libspotify
	install include/libspotify/api.h $(prefix)/include/libspotify

	mkdir -p $(prefix)/lib
	install -T lib/libspotify.so.10 $(prefix)/lib/libspotify.so.10.1.11

	cd $(prefix)/lib && ln -sf libspotify.so.10.1.11 libspotify.so.10 && ln -sf libspotify.so.10.1.11 libspotify.so

	mkdir -p $(prefix)/lib/pkgconfig
	sed -e s:PKG_PREFIX:$(prefix):g <lib/pkgconfig/libspotify.pc >$(prefix)/lib/pkgconfig/libspotify.pc

	ldconfig

uninstall:
	rm -rf $(prefix)/include/libspotify
	rm -f  $(prefix)/lib/libspotify.so.10.1.11
	rm -f  $(prefix)/lib/libspotify.so.10
	rm -f  $(prefix)/lib/libspotify.so
	rm -f  $(prefix)/lib/pkgconfig/libspotify.pc
