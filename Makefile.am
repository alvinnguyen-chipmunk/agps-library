## Process this file with automake to produce Makefile.in

SUBDIRS = po src examples

AUTOMAKE_OPTIONS = 1.7

ACLOCAL_AMFLAGS = -I m4

EXTRA_DIST = \
	autogen.sh \
	libstylagps.pc.in


uninstall-local:
	rm -rf $(DESTDIR)$(pkgdatadir);

install-data-local: install-data-only
	@$(NORMAL_INSTALL)

install-data-only:
	@$(NORMAL_INSTALL)
	$(mkinstalldirs) $(DESTDIR)$(pkgdatadir); \
	for file in $(builddir)/data/*; do \
	  if test -f $$file; then \
	    $(INSTALL_DATA) $$file $(DESTDIR)$(pkgdatadir)/; \
	  fi \
	done

pkgconfig_DATA = libstylagps.pc
pkgconfigdir = $(libdir)/pkgconfig

@INTLTOOL_DESKTOP_RULE@
