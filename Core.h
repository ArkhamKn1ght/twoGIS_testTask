#ifndef CORE_H
#define CORE_H

#include <QObject>
#include <QDebug>
#include <QFile>
#include <unordered_map>
class Core : public QObject
{
    Q_OBJECT
public:
    Core() {}
    ~Core() {}
public slots:
    int readFile(const QString& _path) {
        QFile file(_path); // Replace with your file path
        if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
            qDebug() << "Cannot open file!";
            return -1;
        }

        QTextStream in(&file);
        while (!in.atEnd()) {
            QString line = in.readLine();
            QStringList words = line.split(' ');
            for (const QString& word : words) {
                if(word.size() == 0) continue;

                auto it = wordMap.find(word);

                if(it != wordMap.end())
                    it->second += 1;
                else
                    wordMap.insert( std::pair<QString, int>(word, 1) );
            }
        }

        file.close();
        return 0;
    }
private:
    std::unordered_map<QString, int> wordMap;
};

#endif // CORE_H
