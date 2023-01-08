DESCRIPTION = "AML libion"
MAINTAINER = "Pure2"
SECTION = "base"
LICENSE = "proprietary"
PACKAGE_ARCH = "${MACHINE_ARCH}"


require conf/license/license-gplv2.inc

PV = "0.1"
PR = "r1"

###  git clone https://github.com/numbqq/aml_libion.git

#inherit autotools-brokensep lib_package pkgconfig
inherit lib_package pkgconfig



SRC_URI = "file://aml_libion/ \
            \
"

S = "${WORKDIR}/aml_libion/"


#EXTRA_OECMAKE += "-DBUILD_SHARED_LIBS=ON \
#		-DENABLE_WEBM_PARSER=ON \
#		-DCMAKE_BUILD_TYPE=Release \
#		"

#EXTRA_OECMAKE += "-DOPENJPEG_INSTALL_LIB_DIR=${@d.getVar('baselib').replace('/', '')}"

##-I${STAGING_KERNEL_DIR}/arm64/include
## CFLAGS_append = "  -I${STAGING_KERNEL_DIR}/include "
#do_compile () {
#    ${CXX} ${CFLAGS}  ${LDFLAGS} ${WORKDIR}/main.c -o ge2dgrey
#}


do_install () {
	install -d ${D}${libdir}
	install ${S}/libion.so ${D}${libdir}
#(cd ${D}/${libdir} && ln -sf libion.so libion.so.0)

	install -d ${D}${includedir}/libion
	cp -r ${S}/include/ion/* ${D}/${includedir}/libion/
#	cp -r ${S}/kernel-headers/* ${D}${includedir}/libion/

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

