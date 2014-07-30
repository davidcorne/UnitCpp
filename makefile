#==============================================================================
INSTALL_PATH?=/usr/local
# find this somewhere
VERSION=1.0.0

# This could be buggy, see http://stackoverflow.com/a/2359849 but can't do
# better
PKG_DIRECTORY=$(shell pkg-config --debug 2>&1 | sed -ne '/Scanning directory /{s///p;q;}')

PKG_CONFIG_FILE=

#==============================================================================
all:
	@echo "This is a header only library. To install try 'make install'"

#==============================================================================
install:
	@echo "Installing to $(INSTALL_PATH)."
	@mkdir -p $(INSTALL_PATH)
	@mkdir -p $(INSTALL_PATH)/include
	@mkdir -p $(INSTALL_PATH)/include/unitcpp_$(VERSION)
	@cp -r UnitCpp $(INSTALL_PATH)/include/unitcpp_$(VERSION)
	@cat unitcpp.pc | sed -e "s:\$$(INSTALL_PATH):$(INSTALL_PATH):" -e "s:\$$(VERSION):$(VERSION):" \
      > $(PKG_DIRECTORY)/unitcpp.pc
	@cat unitcpp.pc | sed -e "s:\$$(INSTALL_PATH):$(INSTALL_PATH):" -e "s:\$$(VERSION):$(VERSION):" \
      > $(PKG_DIRECTORY)/unitcpp-$(VERSION).pc
	@echo "Installed successfully."

