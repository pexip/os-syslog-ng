SUBDIRS		= docs src tests examples

ACLOCAL_AMFLAGS	= -I m4 --install
EXTRA_DIST	= NEWS README.md m4/.placeholder

coverage:
	@echo "Making $@ in src"
	($(am__cd) src && $(MAKE) $(AM_MAKEFLAGS) $@)

doxygen:
	$(AM_V_GEN)doxygen
