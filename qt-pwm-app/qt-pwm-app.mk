################################################################################
#
# qt-pwm-app by Petooooooooooooo
#
################################################################################

QT_PWM_APP_VERSION = 1.0
QT_PWM_APP_SITE = package/qt-pwm-app
QT_PWM_APP_SITE_METHOD = local

QT_PWM_APP_DEPENDENCIES = qt6base qt6declarative

define QT_PWM_APP_BUILD_CMDS
    cmake -S $(@D) -B $(@D)/build \
        -DCMAKE_TOOLCHAIN_FILE=/home/youssef/mydata/study/embedded_linux_kitchen/buildroot/output/host/share/buildroot/toolchainfile.cmake
    $(MAKE) -C $(@D)/build
endef

define QT_PWM_APP_INSTALL_TARGET_CMDS
    $(INSTALL) -D -m 0755 $(@D)/build/qt-pwm-app $(TARGET_DIR)/usr/bin/qt-pwm-app
endef
$(eval $(generic-package))

