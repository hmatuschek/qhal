#include "qhal.hh"
#include <QCoreApplication>
#include <QFile>
#include <QIODevice>
#include <QDebug>
#include <QTextStream>
#include <QString>
#include <random>
#include <time.h>

int main(int argc, char *argv[]) {
  QCoreApplication app(argc, argv);

  srand(time(0));
  QHalModel hal;

  if (argc > 1) {
    QFile file(argv[1]);
    file.open(QIODevice::ReadOnly);
    QTextStream stream(&file);
    while (true) {
      QString line = stream.readLine();
      if (line.startsWith("#")) { continue; }
      if (line.isNull()) { break; }
      hal.learn(line);
    }
  }
  qDebug() << "Learned" << argv[1];

  QTextStream in(stdin, QIODevice::ReadOnly);
  QTextStream out(stdout, QIODevice::WriteOnly);
  while (true) {
    out << "< "; out.flush();
    QString line = in.readLine();
    if (line.isNull()) { continue; }
    out << "> " << hal.reply(line) << "\n"; out.flush();
  }
  return 0;
}
