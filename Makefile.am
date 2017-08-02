## Process this file with automake to produce Makefile.in

SUBDIRS = src examples

AUTOMAKE_OPTIONS = 1.7

ACLOCAL_AMFLAGS = -I m4

EXTRA_DIST = \
	autogen.sh \
	libstylagps.pc.in

if YOCTO
uninstall-local:
	rm -rf $(DESTDIR)$(pkgdatadir);
	rm -rf $(DESTDIR)$(includedir)/libstylagps;
else
stylagps_datadir = /etc/stylagps
uninstall-local:
	rm -rf $(DESTDIR)$(pkgdatadir);
	rm -rf $(stylagps_datadir);
	rm -rf $(DESTDIR)$(includedir)/libstylagps;

install-data-local: install-data-only
	@$(NORMAL_INSTALL)

install-data-only:
	@$(NORMAL_INSTALL)
	$(mkinstalldirs) $(stylagps_datadir); \
	for file in $(builddir)/data/*; do \
	  if test -f $$file; then \
	    $(INSTALL_DATA) $$file $(stylagps_datadir)/; \
	  fi \
	done
endif

pkgconfig_DATA = libstylagps.pc
pkgconfigdir = $(libdir)/pkgconfig
