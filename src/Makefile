PWD     	:= $(shell pwd)
TARGET      ?= arm-linux
CROSS_COMPILE   ?= $(TARGET)-
CPP     	:= $(CROSS_COMPILE)g++
CC      	:= $(CROSS_COMPILE)gcc
AR      	:= $(CROSS_COMPILE)ar
RANLIB      := $(CROSS_COMPILE)ranlib
INSTALL_DIR	?= ../rootfs/usr/bin
INSTALL_DIR_CGI	?= ../rootfs/usr/web/cgi-bin

INC     	= -I $(KERNEL_DIR)/src/include
INC		+= -I $(MIDDLEWARE_INS_DIR)/include
INC			+= -I $(PWD)/include
INC		+= -I $(AUTOCONF_DIR)
INC 		+= -I$(PWD)

LIB		= -L $(MIDDLEWARE_INS_DIR)/lib

CFLAGS      := -Wall -g -O2 $(EXTRA_CFLAGS) $(INC) $(LIB)

LDFLAGS	:= -lsnx_isp -lsnx_vc -lpthread -lgpio
LDFLAGS     += $(EXTRA_LDFLAGS) -Wl,--as-needed -lm


targets = snx_isp_ctl isp_gain pan_tilt_up.cgi pan_tilt_down.cgi pan_tilt_right.cgi pan_tilt_left.cgi pan_tilt_center.cgi uart_ctl

.PHONY : clean distclean all
%.o : %.c
	$(CC) $(CFLAGS) -c $<

all: $(targets)


snx_isp_ctl: snx_isp_ctl.o 
	$(CC) $(CFLAGS) -o $@ $+ $(LDFLAGS)

isp_gain: isp_gain.o
	$(CC) $(CFLAGS) -o $@ $+ $(LDFLAGS)

pan_tilt_up.cgi: pan_tilt_up.o
	$(CC) $(CFLAGS) -o $@ $+ $(LDFLAGS)

pan_tilt_down.cgi: pan_tilt_down.o
	$(CC) $(CFLAGS) -o $@ $+ $(LDFLAGS)

pan_tilt_right.cgi: pan_tilt_right.o
	$(CC) $(CFLAGS) -o $@ $+ $(LDFLAGS)

pan_tilt_left.cgi: pan_tilt_left.o
	$(CC) $(CFLAGS) -o $@ $+ $(LDFLAGS)

pan_tilt_center.cgi: pan_tilt_center.o
	$(CC) $(CFLAGS) -o $@ $+ $(LDFLAGS)

uart_ctl: uart_ctl.o
	$(CC) $(CFLAGS) -o $@ $+ $(LDFLAGS)


.PHONY: install
install:
	@ if [ ! -d $(INSTALL_DIR) ]; \
	then \
	install -d $(INSTALL_DIR); \
	fi
	install -c $(targets) $(INSTALL_DIR)
	cp pan_tilt_up.cgi ~/PartronIPCAM/app/web-admin/rootfs/usr/web/cgi-bin/
	cp pan_tilt_down.cgi ~/PartronIPCAM/app/web-admin/rootfs/usr/web/cgi-bin/
	cp pan_tilt_right.cgi ~/PartronIPCAM/app/web-admin/rootfs/usr/web/cgi-bin/
	cp pan_tilt_left.cgi ~/PartronIPCAM/app/web-admin/rootfs/usr/web/cgi-bin/
	cp pan_tilt_center.cgi ~/PartronIPCAM/app/web-admin/rootfs/usr/web/cgi-bin/


clean:
	rm -f *.o *.yuv *.bak *.a *.out *.so $(targets)

distclean : clean
	rm -f $(targets)


