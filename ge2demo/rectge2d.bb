DESCRIPTION = "AML rectge2d"
MAINTAINER = "Pure2"
SECTION = "base"
LICENSE = "proprietary"
PACKAGE_ARCH = "${MACHINE_ARCH}"


require conf/license/license-gplv2.inc

PV = "0.1"
PR = "r1"

### https://github.com/OtherCrashOverride/HelloGE2D
### https://forum.odroid.com/viewtopic.php?f=112&t=9412
### X11:  https://forum.odroid.com/viewtopic.php?f=112&t=8315
### GE2D: https://forum.odroid.com/viewtopic.php?f=111&t=27587

SRC_URI = "file://main.c \
           file://ge2d.h \
           file://ion.h \
           file://meson_ion.h \
           file://capture.bmp \
"

S = "${WORKDIR}"


##-I${STAGING_KERNEL_DIR}/arm64/include
## CFLAGS_append = "  -I${STAGING_KERNEL_DIR}/include "

do_compile () {
    ${CXX} ${CFLAGS}  ${LDFLAGS} ${WORKDIR}/main.c -o rectge2d
}

do_install () {
    install -d ${D}${bindir}
    install -m 0755 rectge2d  ${D}${bindir}/
}


#sysroot_stage_all() {
#    :
#}


do_qa_staging() {
}

do_rm_work() {
}

