## Process this file with automake to produce Makefile.in

SUBDIRS = po src examples

AUTOMAKE_OPTIONS = 1.7

ACLOCAL_AMFLAGS = -I m4

EXTRA_DIST = \
	autogen.sh \
	libstylagps.pc.in

stylagps_datadir = /etc/stylagps

uninstall-local:
	rm -rf $(DESTDIR)$(pkgdatadir);
	rm -rf $(stylagps_datadir);

install-data-local: install-data-only
	@$(NORMAL_INSTALL)

install-data-only:
	@$(NORMAL_INSTALL)
	##$(mkinstalldirs) $(DESTDIR)$(pkgdatadir); \
	##for file in $(srcdir)/data/*; do \
	##  if test -f $$file; then \
	##    $(INSTALL_DATA) $$file $(DESTDIR)$(pkgdatadir)/; \
	##  fi \
	##done
	$(mkinstalldirs) $(stylagps_datadir)
	if test -f $(builddir)/data/stylagps.conf; then \
		$(INSTALL_DATA) $(builddir)/data/stylagps.conf $(stylagps_datadir)/; \
	fi
	

pkgconfig_DATA = libstylagps.pc
pkgconfigdir = $(libdir)/pkgconfig

@INTLTOOL_DESKTOP_RULE@
