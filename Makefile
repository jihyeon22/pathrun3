
###############################################################################
# Path

DESTDIR		:= $(CURDIR)/out

PREFIX		:= /system
BINDIR		:= $(PREFIX)/sbin
INITRCDIR	:= /etc/init.d

###############################################################################
# Compile

CC	:= $(CROSS_COMPILE)gcc

CFLAGS	:= $(EXTRA_CFLAGS)
LDFLAGS	:= $(EXTRA_LDFLAGS)

###############################################################################
# Options

#AUTOSTART	:= y

###############################################################################
# Board

BOARD	:= 
CFLAGS	+= -DBOARD_$(BOARD)

###############################################################################
# Target rules

CFLAGS	+= -lpthread
LDFLAGS	+=

OBJS	:= src/pathrun.o
APP	:= pathrun3

all: all-before	$(APP)

all-before:
	$(eval $(call checkboard))


$(APP):		$(OBJS)
	$(Q)$(CC) $(CFLAGS) -o $@ $^

install:	install-binary

install-binary:	$(APP)
	$(Q)$(call check_install_dir, $(DESTDIR)$(BINDIR))
	$(Q)fakeroot cp -v $(APP) $(DESTDIR)$(BINDIR)/$(APP)

clean:
	$(Q)rm -vrf $(APP) $(OBJS) 

uninstall:
	$(Q)rm -vrf $(DESTDIR)$(BINDIR)/$(APP)


###############################################################################
# Functions

define check_install_dir
	if [ ! -d "$1" ]; then mkdir -p $1; fi
endef

define checkboard
ifeq ($(BOARD),)
$$(error BOARD is not found, BOARD=NEO_W100/NEO_W200)
endif
endef
