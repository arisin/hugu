#include <QtDeclarative>
#include <QApplication>

#include "qml_hugu.hxx"

int main(int ac, char** avs) {
  QScopedPointer<QApplication> a(new QApplication(ac, avs));

  qmlRegisterType<qml_hugu>("jp.arisin.hugu", 0, 1, "Hugu");

  auto v = new QDeclarativeView;
  v->setSource(QUrl::fromLocalFile("hugu.qml"));
  v->setStyleSheet("background: transparent; border: none;");
  v->setAttribute(Qt::WA_TranslucentBackground);
  v->setWindowFlags(Qt::FramelessWindowHint);
  v->show();

  return a->exec();
}
