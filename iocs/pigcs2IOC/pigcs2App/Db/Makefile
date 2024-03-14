TOP=../..
include $(TOP)/configure/CONFIG
#----------------------------------------
#  ADD MACRO DEFINITIONS AFTER THIS LINE

#----------------------------------------------------
#  Optimization of db files using dbst (DEFAULT: NO)
#DB_OPT = YES

### this module was built outside motor
DB_INSTALLS += $(TOP)/../../db/PI_SupportError.db
DB_INSTALLS += $(TOP)/../../db/PI_SupportCtrl.db
DB_INSTALLS += $(TOP)/../../db/PI_SupportCL.db
DB_INSTALLS += $(TOP)/../../db/PI_Support.db
DB_INSTALLS += $(TOP)/../../db/PI_SupportCS.db

#----------------------------------------------------
# Create and install (or just install) into <top>/db
# databases, templates, substitutions like this
#DB += xxx.db

#----------------------------------------------------
# If <anyname>.db template is not named <anyname>*.template add
# <anyname>_template = <templatename>

include $(TOP)/configure/RULES
#----------------------------------------
#  ADD RULES AFTER THIS LINE

