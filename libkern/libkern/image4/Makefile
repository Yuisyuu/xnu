export MakeInc_cmd=${SRCROOT}/makedefs/MakeInc.cmd
export MakeInc_def=${SRCROOT}/makedefs/MakeInc.def
export MakeInc_rule=${SRCROOT}/makedefs/MakeInc.rule
export MakeInc_dir=${SRCROOT}/makedefs/MakeInc.dir

include $(MakeInc_cmd)
include $(MakeInc_def)

DATAFILES =
PRIVATE_DATAFILES =
KERNELFILES =
PRIVATE_KERNELFILES = api.h dlxk.h interface.h

INSTALL_MI_LIST = ${DATAFILES}
INSTALL_SF_MI_LCL_LIST = ${DATAFILES} ${PRIVATE_DATAFILES}
INSTALL_KF_MI_LIST = ${KERNELFILES}
INSTALL_KF_MI_LCL_LIST = ${PRIVATE_KERNELFILES}
EXPORT_MI_LIST = ${INSTALL_KF_MI_LCL_LIST}

INSTALL_MI_DIR = libkern/image4
EXPORT_MI_DIR = libkern/image4

include $(MakeInc_rule)
include $(MakeInc_dir)
