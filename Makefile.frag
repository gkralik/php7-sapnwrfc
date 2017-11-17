extclean: clean
	find . -name \*.c.i -o -name \*.c.ii | xargs rm -f

extdistclean: extclean distclean

.PHONY: extclean extdistclean
