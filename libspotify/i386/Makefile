prefix ?= /usr/local

all:
	$(error "Usage: make [prefix=/install/me/here] install | uninstall")

install:
	mkdir -p $(prefix)/include/libspotify
	install include/libspotify/api.h $(prefix)/include/libspotify

	mkdir -p $(prefix)/lib
	install -T lib/libspotify.so.12 $(prefix)/lib/libspotify.so.12.1.51

	cd $(prefix)/lib && ln -sf libspotify.so.12.1.51 libspotify.so.12 && ln -sf libspotify.so.12.1.51 libspotify.so

	mkdir -p $(prefix)/lib/pkgconfig
	sed -e s:PKG_PREFIX:$(prefix):g <lib/pkgconfig/libspotify.pc >$(prefix)/lib/pkgconfig/libspotify.pc

	ldconfig

uninstall:
	rm -rf $(prefix)/include/libspotify
	rm -f  $(prefix)/lib/libspotify.so.12.1.51
	rm -f  $(prefix)/lib/libspotify.so.12
	rm -f  $(prefix)/lib/libspotify.so
	rm -f  $(prefix)/lib/pkgconfig/libspotify.pc
