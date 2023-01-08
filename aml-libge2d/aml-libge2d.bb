DESCRIPTION = "AML libge2d"
MAINTAINER = "Pure2"
SECTION = "base"
LICENSE = "proprietary"
PACKAGE_ARCH = "${MACHINE_ARCH}"

require conf/license/license-gplv2.inc

PV = "0.1"
PR = "r0"

###  git clone https://github.com/numbqq/aml_libge2d.git

#inherit autotools-brokensep lib_package pkgconfig
inherit lib_package pkgconfig

DEPENDS = "aml-libion"

SRC_URI = "file://aml_libge2d/ \
            \
"

S = "${WORKDIR}/aml_libge2d/libge2d/"


CFLAGS += " -I${STAGING_INCDIR}/libion "

do_install () {
	install -d ${D}${libdir}
	install ${S}/libge2d.so ${D}${libdir}
#(cd ${D}/${libdir} && ln -sf libge2d.so libge2d.so.0)

	install -d ${D}${includedir}/libge2d
	cp -r ${S}/include/* ${D}/${includedir}/libge2d/
#	cp -r ${S}/kernel-headers/* ${D}${includedir}/libge2d/

#	install -d ${D}${bindir}
#	install -m 0755 ${S}/iontest  ${D}${bindir}/
}


FILES_${PN} += "${bindir}/*  ${libdir}/*"
#FILES_${PN}-dev += "${includedir}/*  ${libdir}/*"
FILES_${PN}-dev += "${includedir}/* "

SOLIBS = ".so"
FILES_SOLIBSDEV = ""


INSANE_SKIP_${PN} += "file-rdeps  dev-so"

#sysroot_stage_all() {
#    :
#}

#do_package_qa() {
#}


#do_qa_staging() {
#}

do_rm_work() {
}

