prefix ?= /usr/local

all:
	$(error "Usage: make [prefix=/install/me/here] install | uninstall")

install:
	mkdir -p $(prefix)/include/libspotify
	install include/libspotify/api.h $(prefix)/include/libspotify

	mkdir -p $(prefix)/lib
	install -T lib/libspotify.so.9 \
		$(prefix)/lib/libspotify.so.9.1.32

	cd $(prefix)/lib && ln -sf libspotify.so.9.1.32 libspotify.so.9 && ln -sf libspotify.so.9.1.32 libspotify.so

	mkdir -p $(prefix)/lib/pkgconfig
	sed -e s:PKG_PREFIX:$(prefix):g \
		<lib/pkgconfig/libspotify.pc \
		>$(prefix)/lib/pkgconfig/libspotify.pc

uninstall:
	rm -rf $(prefix)/include/libspotify
	rm -f  $(prefix)/lib/libspotify.so.9.1.32
	rm -f  $(prefix)/lib/libspotify.so.9
	rm -f  $(prefix)/lib/libspotify.so
	rm -f  $(prefix)/lib/pkgconfig/libspotify.pc
