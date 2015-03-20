## Process this file with automake to produce Makefile.in
## Created by Anjuta

SUBDIRS = src po

dist_doc_DATA = \
	README \
	COPYING \
	AUTHORS \
	ChangeLog \
	INSTALL \
	NEWS \
	lavalamp.desktop \
	lavalamp.png


INTLTOOL_FILES = intltool-extract.in \
	intltool-merge.in \
	intltool-update.in

EXTRA_DIST = \
	$(INTLTOOL_FILES)

desktop_filedir = /usr/share/applications
desktop_file_DATA = lavalamp.desktop

icon_filedir = /usr/share/pixmaps
icon_file_DATA = lavalamp.png


config_filedir =    $HOME
config_file_DATA = lavalamp.cfg



DISTCLEANFILES = intltool-extract \
	intltool-merge \
	intltool-update \
	po/.intltool-merge-cache


# Remove doc directory on uninstall
uninstall-local:
	-rm -r $(docdir)
