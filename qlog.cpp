#include "qlog.hpp"
#include <QDateTime>
#include <QDebug>
#include <QTextStream>

qlog::qlog(QObject *parent) : QObject{parent} {
  _LogPath = _DefaultPath;
  _File.setFileName(_LogPath);
}

qlog::qlog(const QString &log_path, QObject *parent) : QObject{parent} {
  _LogPath = log_path;
  _File.setFileName(_LogPath);
}

qlog::~qlog() { _File.close(); }

void qlog::attach() {

  _LogStatus = true;

  if (!_File.isOpen()) {
    if (!_File.open(QIODevice::Append))
      qCritical() << "Can not open the file : " << _File.fileName();
  }
  qInstallMessageHandler(handler);
}

void qlog::set_path(QString const &path) noexcept {
  qlog::_LogPath = path;
  _File.setFileName(_LogPath);
}

QString const &qlog::path() noexcept { return _LogPath; }

void qlog::deattach() noexcept { _LogStatus = false; }

void qlog::handler(QtMsgType type, QMessageLogContext const &info,
                   QString const &msg) {
  if (_LogStatus) {
    QString log;
    switch (type) {
      break;
    case QtInfoMsg:
      log = QString("info: %1").arg(msg);
      break;
    case QtDebugMsg:
      log = QString("Debug: %1").arg(msg);
      break;
    case QtWarningMsg:
      log = QString("Warning: %1").arg(msg);
      break;
    case QtCriticalMsg:
      log = QString("Critical: %1").arg(msg);
      break;
    case QtFatalMsg:
      log = QString("Fatal: %1").arg(msg);
    }

    static QTextStream file(&_File);
    file << QDateTime::currentDateTime().toString() << " - " << log << " - "
         << "file : " << info.file << " function : " << info.function
         << " line : " << info.line << Qt::endl;
  }
  (*default_msg_handler)(type, info, msg); // also print to default streams
}
