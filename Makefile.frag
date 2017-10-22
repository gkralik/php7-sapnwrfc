clean-ext: clean
	find . -name \*.c.i -o -name \*.c.ii | xargs rm -f

distclean-ext: clean-ext distclean

.PHONY: clean-ext distclean-ext
