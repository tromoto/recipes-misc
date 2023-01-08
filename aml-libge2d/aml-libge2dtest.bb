DESCRIPTION = "AML libge2dtest"
MAINTAINER = "Pure2"
SECTION = "base"
LICENSE = "proprietary"
PACKAGE_ARCH = "${MACHINE_ARCH}"

require conf/license/license-gplv2.inc

PV = "0.1"
PR = "r0"

###  git clone https://github.com/numbqq/aml_libge2d.git

#inherit autotools-brokensep lib_package pkgconfig
#inherit lib_package pkgconfig

DEPENDS = "aml-libion aml-libge2d"

SRC_URI = "file://aml_libge2d/ \
            \
"

S = "${WORKDIR}/aml_libge2d/"


#CFLAGS += " -I${STAGING_INCDIR}/libion "

do_install () {
	install -d ${D}${bindir}
	install -m 0755 ${S}/ge2d_feature_test  ${D}${bindir}/
	install -m 0755 ${S}/ge2d_chip_check  ${D}${bindir}/
}


FILES_${PN} += "${bindir}/* "


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

