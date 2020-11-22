# get current version string
GIT_VERSION := "$(shell git describe --abbrev --dirty --always --tag)"

# make all shared objects depend on the version header
$(shared_objects_sapnwrfc): version.h

# update the version header if version changed
.PHONY: force
version.h: force
#	echo "Generating version.h for $(GIT_VERSION)"
	@echo '#define GIT_VERSION $(GIT_VERSION)' | cmp -s - $@ \
		|| (echo '#define GIT_VERSION $(GIT_VERSION)' > $@; \
			echo "Updated version.h for $(GIT_VERSION)")

