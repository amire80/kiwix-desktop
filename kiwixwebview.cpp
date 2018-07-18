#include "kiwixwebview.h"

#include <QWebEngineProfile>
#include <iostream>
#include "kiwixapp.h"

KiwixWebView::KiwixWebView(QWidget *parent)
    : QWebEngineView(parent)
{
    auto profile = page()->profile();
    auto app = KiwixApp::instance();
    profile->installUrlSchemeHandler("zim", app->getSchemeHandler());
    profile->setRequestInterceptor(app->getRequestInterceptor());
    QObject::connect(this, &QWebEngineView::urlChanged, this, &KiwixWebView::onUrlChanged);
}

KiwixWebView::~KiwixWebView()
{}

QWebEngineView* KiwixWebView::createWindow(QWebEnginePage::WebWindowType type)
{
    if ( type==QWebEnginePage::WebBrowserBackgroundTab
      || type==QWebEnginePage::WebBrowserTab )
    {
        auto tabWidget = KiwixApp::instance()->getTabWidget();
        return tabWidget->createNewTab(type==QWebEnginePage::WebBrowserTab);
    }
    return nullptr;
}

void KiwixWebView::onUrlChanged(const QUrl& url) {
    if (currentHost != url.host() ) {
        currentHost = url.host();
        auto app = KiwixApp::instance();
        auto reader = app->getLibrary()->getReader(currentHost);
        std::string favicon, _mimetype;
        reader->getFavicon(favicon, _mimetype);
        QPixmap pixmap;
        pixmap.loadFromData((const uchar*)favicon.data(), favicon.size());
        _icon = QIcon(pixmap);
        emit iconChanged(_icon);
    }
}
