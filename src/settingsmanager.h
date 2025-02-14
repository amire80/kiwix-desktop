#ifndef SETTINGSMANAGER_H
#define SETTINGSMANAGER_H

#include <QObject>
#include <QSettings>
#include "settingsview.h"

class SettingsManager : public QObject
{
    Q_OBJECT
    Q_PROPERTY(int kiwixServerPort READ getKiwixServerPort NOTIFY portChanged)
    Q_PROPERTY(qreal zoomFactor MEMBER m_zoomFactor WRITE setZoomFactor NOTIFY zoomChanged)
    Q_PROPERTY(QString downloadDir MEMBER m_downloadDir WRITE setDownloadDir NOTIFY downloadDirChanged)

public:
    explicit SettingsManager(QObject *parent = nullptr);
    virtual ~SettingsManager() {};

    SettingsView* getView();
    void setSettings(const QString &key, const QVariant &value);
    void deleteSettings(const QString &key);
    bool settingsExists(const QString &key);
    QVariant getSettings(const QString &key);
    qreal getZoomFactorByZimId(const QString &id);

public slots:
    void setKiwixServerPort(int port);
    int getKiwixServerPort() { return m_kiwixServerPort; };
    void setKiwixServerIpAddress(QString ipAddress);
    QString getKiwixServerIpAddress() { return m_kiwixServerIpAddress; };
    void setZoomFactor(qreal zoomFactor);
    qreal getZoomFactor() { return m_zoomFactor; };
    bool setDownloadDir(QString downloadDir);
    QString getDownloadDir() { return m_downloadDir; }
private:
    void initSettings();

signals:
    void portChanged(int port);
    void zoomChanged(qreal zoomFactor);
    void downloadDirChanged(QString downloadDir);

private:
    QSettings m_settings;
    SettingsView *m_view;
    int m_kiwixServerPort;
    QString m_kiwixServerIpAddress;
    qreal m_zoomFactor;
    QString m_downloadDir;
};

#endif // SETTINGSMANAGER_H
