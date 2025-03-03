#include "pwmController.h"
#include <QFile>
#include <QTextStream>
#include <QDebug>
#include <QThread>

PwmControl::PwmControl(QObject *parent) : QObject(parent)
{
    // Automatically export the default PWM channel upon object creation.
    if (!exportPWM(pwmChip, pwmChannel)) {
        qWarning() << "Failed to export PWM channel" << pwmChannel << "on chip" << pwmChip;
    } else {
        setPWMPeriod(pwmChip, pwmChannel, PERIOD);
        enablePWM(pwmChip, pwmChannel, true);
        qDebug() << "Successfully exported PWM channel" << pwmChannel << "on chip" << pwmChip;
    }
}

PwmControl::~PwmControl()
{
    // Unexport the PWM channel on destruction.
    if (!unexportPWM(pwmChip, pwmChannel)) {
        qWarning() << "Failed to unexport PWM channel" << pwmChannel << "on chip" << pwmChip;
    } else {
        qDebug() << "Successfully unexported PWM channel" << pwmChannel << "on chip" << pwmChip;
    }
}

bool PwmControl::exportPWM(int pwmChip, int pwmChannel)
{
    QString exportPath = QString("/sys/class/pwm/pwmchip%1/export").arg(pwmChip);
    QFile file(exportPath);
    if (!file.open(QIODevice::WriteOnly)) {
        qWarning() << "Failed to open" << exportPath;
        return false;
    }
    QTextStream out(&file);
    out << pwmChannel;
    file.close();
    return true;
}

bool PwmControl::unexportPWM(int pwmChip, int pwmChannel)
{
    QString unexportPath = QString("/sys/class/pwm/pwmchip%1/unexport").arg(pwmChip);
    QFile file(unexportPath);
    if (!file.open(QIODevice::WriteOnly)) {
        qWarning() << "Failed to open" << unexportPath;
        return false;
    }
    QTextStream out(&file);
    out << pwmChannel;
    file.close();
    return true;
}

bool PwmControl::setPWMPeriod(int pwmChip, int pwmChannel, int periodNs)
{
    QString periodPath = QString("/sys/class/pwm/pwmchip%1/pwm%2/period")
                        .arg(pwmChip)
                        .arg(pwmChannel);
    QFile file(periodPath);
    if (!file.open(QIODevice::WriteOnly)) {
        qWarning() << "Failed to open" << periodPath;
        return false;
    }
    QTextStream out(&file);
    out << periodNs;
    file.close();
    return true;
}

bool PwmControl::setPWMDutyCycle(int pwmChip, int pwmChannel, int dutyCycleNs)
{
    QString dutyPath = QString("/sys/class/pwm/pwmchip%1/pwm%2/duty_cycle")
                        .arg(pwmChip)
                        .arg(pwmChannel);
    QFile file(dutyPath);
    if (!file.open(QIODevice::WriteOnly)) {
        qWarning() << "Failed to open" << dutyPath;
        return false;
    }
    QTextStream out(&file);
    out << dutyCycleNs;
    file.close();
    return true;
}

bool PwmControl::enablePWM(int pwmChip, int pwmChannel, bool enable)
{
    QString enablePath = QString("/sys/class/pwm/pwmchip%1/pwm%2/enable")
                         .arg(pwmChip)
                         .arg(pwmChannel);
    QFile file(enablePath);
    if (!file.open(QIODevice::WriteOnly)) {
        qWarning() << "Failed to open" << enablePath;
        return false;
    }
    QTextStream out(&file);
    out << (enable ? "1" : "0");
    file.close();
    return true;
}

void PwmControl::rampUpPWM(int pwmChip, int pwmChannel, int periodNs)
{
    // Calculate a 5% step.
    int step = periodNs * 2 / 100;
    if (step <= 0)
        step = 1;
    // Ramp up the duty cycle.
    for (int duty = 0; duty <= periodNs; duty += step) {
        if (!setPWMDutyCycle(pwmChip, pwmChannel, duty)) {
            qWarning() << "Failed to set duty cycle to" << duty;
            return;
        }
        QThread::msleep(50); // delay for a visible transition
    }
}

void PwmControl::rampDownPWM(int pwmChip, int pwmChannel, int periodNs)
{
    // Calculate a 5% step.
    int step = periodNs * 2 / 100;
    if (step <= 0)
        step = 1;
    // Ramp down the duty cycle.
    for (int duty = periodNs; duty >= 0; duty -= step) {
        if (!setPWMDutyCycle(pwmChip, pwmChannel, duty)) {
            qWarning() << "Failed to set duty cycle to" << duty;
            return;
        }
        QThread::msleep(50);
    }
}

void PwmControl::asyncRampUpPWM(int pwmChip, int pwmChannel, int periodNs)
{
    // Run rampUpPWM in a separate thread.
    QThread *thread = QThread::create([=]() {
        rampUpPWM(pwmChip, pwmChannel, periodNs);
    });
    connect(thread, &QThread::finished, thread, &QObject::deleteLater);
    thread->start();
}

void PwmControl::asyncRampDownPWM(int pwmChip, int pwmChannel, int periodNs)
{
    // Run rampDownPWM in a separate thread.
    QThread *thread = QThread::create([=]() {
        rampDownPWM(pwmChip, pwmChannel, periodNs);
    });
    connect(thread, &QThread::finished, thread, &QObject::deleteLater);
    thread->start();
}
