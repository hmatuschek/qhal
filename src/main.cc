#include "qhal.hh"
#include <QCoreApplication>
#include <QFile>
#include <QIODevice>
#include <QDebug>
#include <QTextStream>
#include <QString>
#include <random>
#include <time.h>

static QTextStream in(stdin, QIODevice::ReadOnly);
static QTextStream out(stdout, QIODevice::WriteOnly);


void
processCommand(QHalModel &hal, const QString &line) {
  if (line.startsWith("#save ")) {
    // Save model
    QString filename = line.mid(6);
    QFile file(filename);
    if (!file.open(QIODevice::WriteOnly)) {
      out << "Can not open file " << filename << ".\n";
      out.flush();
      return;
    }
    hal.serialize(file);
    file.close();
  } else if (line.startsWith("#load ")) {
    // Load model
    QString filename = line.mid(6);
    QFile file(filename);
    if (!file.open(QIODevice::ReadOnly)) {
      out << "Can not open file " << filename << ".\n";
      out.flush();
      return;
    }
    hal.read(file);
    file.close();
  } else if (line.startsWith("#learn ")) {
    // Learn from file.
    QString filename = line.mid(7);
    QFile file(filename);
    if (!file.open(QIODevice::ReadOnly)) {
      out << "Can not open file " << filename << ".\n";
      out.flush();
      return;
    }
    QTextStream stream(&file);
    while (true) {
      QString l = stream.readLine();
      if (l.isNull()) { break; }
      if (l.startsWith('#')) { continue; }
      hal.learn(l);
    }
  }
  else if (line.startsWith("#quit")) {
    // Quit.
    exit(0);
  }
}

int main(int argc, char *argv[]) {
  QCoreApplication app(argc, argv);

  // Init RNG
  srand(time(0));
  // init model
  QHalModel hal;

  // Process command line areguments
  for (int i=1; i<argc; i++) {
    QFile file(argv[i]);
    if (! file.open(QIODevice::ReadOnly)) { continue; }
    QTextStream stream(&file);
    while (true) {
      QString line = stream.readLine();
      if (line.startsWith("#")) { continue; }
      if (line.isNull()) { break; }
      hal.learn(line);
    }
    out << "Learned sentences from " << argv[1] << ".\n";
  }

  // print greeting
  out << "*\n* Welcome to qHAL, a Qt implementation of MegaHAL.\n*\n"
      << "* Copyright 2015 by Hannes Matuschek, https://github.com/hmatuschek/qhal,\n"
      << "*  based on the original implementation by Jason Hutchens,\n"
      << "*  http://megahal.sourceforge.net.\n*\n"
      << "* Commands\n"
      << "*  #learn FILENAME : Learn from text file.\n"
      << "*  #save FILENAME  : Save model to file.\n"
      << "*  #load FILENAME  : Load model from file.\n"
      << "*  #quit           : Quit.\n*\n"; out.flush();

  while (true) {
    out << "< "; out.flush();
    QString line = in.readLine();
    if (line.isNull()) { continue; }
    if (line.startsWith('#')) {
      processCommand(hal, line);
    } else {
      out << "> " << hal.reply(line) << "\n"; out.flush();
    }
  }
  return 0;
}
