#include <QGuiApplication>
#include <QScreen>
#include <QRect>
#include <QSurfaceFormat>
#include "mainwindow.h"

MainWindow::MainWindow(QWindow *parent)
    : QWindow(parent)
{
    QSurfaceFormat format;
    format.setSamples(16);
    this->setFormat(format);
    this->setSurfaceType(QWindow::OpenGLSurface);
    QScreen *screen = QGuiApplication::primaryScreen();
    QRect rect = screen->availableGeometry();
    this->setGeometry((rect.width() - 400) / 2, (rect.height() - 400) / 2, 400, 400);

    ESContext esContext;
    memset(&esContext, 0, sizeof(esContext));
    esContext.eglNativeDisplay = EGL_DEFAULT_DISPLAY;
    esContext.eglNativeWindow = (EGLNativeWindowType)this->winId();
    esContext.width = this->width();
    esContext.height = this->height();
    //m_pIGlesHandle = new HelloTriangle();
    m_pIGlesHandle = new MatrixTransform();
    //m_pIGlesHandle = new Illumination();
    m_pIGlesHandle->initialize(esContext);

    m_timer.setInterval(10);
    connect(&m_timer, &QTimer::timeout, this, &MainWindow::onTimeout);
    m_timer.start();

    m_pIGlesHandle->updateData();
    this->requestUpdate();
}

MainWindow::~MainWindow()
{
    m_timer.stop();
    delete m_pIGlesHandle;
}

void MainWindow::onTimeout()
{
    m_pIGlesHandle->updateData();
    this->requestUpdate();
}

bool MainWindow::event(QEvent *event)
{
    switch(event->type())
    {
    case QEvent::UpdateRequest:
        m_pIGlesHandle->render();
        return true;
    default:
        return QWindow::event(event);
    }
}
