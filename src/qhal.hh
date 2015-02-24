#ifndef __QHAL_HH__
#define __QHAL_HH__

#include <QVector>
#include <QHash>
#include <QStringList>

/** The N-gram tree. */
class QHalTree
{
protected:
  explicit QHalTree(size_t symbol);

public:
  explicit QHalTree();
  ~QHalTree();

  bool empty() const;
  size_t size() const;
  size_t usage() const;
  size_t count() const;
  size_t symbol() const;

  QHalTree *addSymbol(size_t symbol);
  QHalTree *findSymbol(size_t symbol);
  QHalTree *random() const;
  QHalTree *branch(size_t idx) const;

protected:
  QHalTree *findSymbolAdd(size_t symbol);

protected:
  size_t _symbol;
  size_t _usage;
  size_t _count;
  QVector<QHalTree *> _branches;
};


/** Symbol <-> String dictionary. */
class QHalDict
{
public:
  explicit QHalDict();
  ~QHalDict();

  size_t addWord(const QString &word);
  bool contains(size_t symbol) const;
  bool contains(const QString &word) const;
  size_t search(const QString &word) const;
  QString search(size_t symbol) const;

protected:
  QHash<QString, size_t> _table;
  QVector<QString> _symbols;
};


/** The actual model. */
class QHalModel
{
public:
  QHalModel(uint8_t order=5);
  ~QHalModel();

  void learn(const QString &sentence);
  QString reply(const QString &sentence);

protected:
  void reset_context();
  void learn(const QStringList &sentence);
  void update(size_t symbol);
  void updateContext(size_t symbol);

  QString reply(const QStringList &words);
  QStringList makeKeywords(const QStringList &words);
  QStringList makeReply(const QStringList &keywords);
  size_t seed(const QStringList &keywords);
  size_t babble(const QStringList &keywords, const QStringList &replies);
  float evaluateReply(const QStringList &keywords, const QStringList &replies);
  QString makeOutput(const QStringList &words);

protected:
  uint8_t  _order;
  QHalTree _forward;
  QHalTree _backward;
  /** Current context. */
  QVector<QHalTree *> _context;
  QHalDict _dictionary;
};


#endif
