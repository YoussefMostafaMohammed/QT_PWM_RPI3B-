#ifndef PWMCONTROLLER_H
#define PWMCONTROLLER_H

#include <QObject>
#define PERIOD 20000000

class PwmControl : public QObject
{
    Q_OBJECT
public:
    explicit PwmControl(QObject *parent = nullptr);
    ~PwmControl();

    bool exportPWM(int pwmChip, int pwmChannel);
    bool unexportPWM(int pwmChip, int pwmChannel);
    bool setPWMPeriod(int pwmChip, int pwmChannel, int periodNs);
    bool setPWMDutyCycle(int pwmChip, int pwmChannel, int dutyCycleNs);
    bool enablePWM(int pwmChip, int pwmChannel, bool enable);

    // Blocking functions that adjust the PWM signal.
    Q_INVOKABLE void rampUpPWM(int pwmChip, int pwmChannel, int periodNs);
    Q_INVOKABLE void rampDownPWM(int pwmChip, int pwmChannel, int periodNs);

    // Asynchronous wrappers for QML to call without blocking the GUI.
    Q_INVOKABLE void asyncRampUpPWM(int pwmChip, int pwmChannel, int periodNs);
    Q_INVOKABLE void asyncRampDownPWM(int pwmChip, int pwmChannel, int periodNs);

    // Default PWM chip and channel.
    int pwmChip = 0;
    int pwmChannel = 0;
};

#endif // PWMCONTROLLER_HPP
