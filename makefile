#==============================================================================
INSTALL_PATH?=/usr/local
# find this somewhere
VERSION=$(shell cat Version.txt)
# This could be buggy, see http://stackoverflow.com/a/2359849 but can't do
# better
PKG_CONFIG_PATH?=$(shell pkg-config --debug 2>&1 | sed -ne '/Scanning directory /{s///p;q;}')

UNITCPP_PC = Scripts/unitcpp.pc

include common.mk

.DEFAULT_GOAL := $(UNITCPP_FILE)

#==============================================================================
install:
	@echo "Installing version $(VERSION) to $(INSTALL_PATH)."
	@mkdir -p $(INSTALL_PATH)/include/unitcpp_$(VERSION)
	@cp $(UNITCPP_FILE) $(INSTALL_PATH)/include/unitcpp_$(VERSION)
	@echo "Making pkg-config aware of the installation."
	@cat $(UNITCPP_PC) | sed -e "s:\$$(INSTALL_PATH):$(INSTALL_PATH):" -e "s:\$$(VERSION):$(VERSION):" \
      > $(PKG_CONFIG_PATH)/unitcpp.pc
	@cat $(UNITCPP_PC) | sed -e "s:\$$(INSTALL_PATH):$(INSTALL_PATH):" -e "s:\$$(VERSION):$(VERSION):" \
      > $(PKG_CONFIG_PATH)/unitcpp-$(VERSION).pc
	@echo "Installed successfully."

