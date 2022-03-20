#ifndef QLOG_HPP
#define QLOG_HPP

#include <QDebug>
#include <QDir>
#include <QFile>
#include <QObject>

class qlog : public QObject {
  Q_OBJECT
public:
  explicit qlog(QObject *parent = nullptr);
  qlog(QString const &, QObject *parent = nullptr);
  ~qlog();
  static void attach();
  static void set_path(QString const &) noexcept;
  static QString const &path() noexcept;
  static void deattach() noexcept;
  static void handler(QtMsgType, QMessageLogContext const &, QString const &);

private:
  Q_DISABLE_COPY(qlog);
  static inline const QtMessageHandler default_msg_handler =
      qInstallMessageHandler(nullptr);

  static inline const QString _DefaultPath{QDir::currentPath() +
                                           QDir::separator() + "qlog.txt"};

  static inline QString _LogPath;
  static inline bool _LogStatus = false;
  static inline QFile _File;
signals:
};

#endif // QLOG_HPP
