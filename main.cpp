#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QMutex>
#include <QFile>
#include <QDateTime>

void outputMessage(QtMsgType type, const QMessageLogContext &context, const QString &msg)
{
    static QMutex mutex;
    mutex.lock();
    QString text;

    switch(type)
    {
        case QtDebugMsg:
        text = QString("Debug:");
        break;
        case QtWarningMsg:
        text = QString("Warning:");
        break;
        case QtCriticalMsg:
        text = QString("Critical:");
        break;
        case QtFatalMsg:
        text = QString("Fatal:");
        break;
     }
     QString context_info = QString("File:(%1) Line:(%2)").arg(QString(context.file)).arg(context.line);
     QString current_date_time = QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss ddd");
     QString current_date = QString("(%1)").arg(current_date_time);
     QString message = QString("%1 %2 %3 %4").arg(text).arg(context_info).arg(msg).arg(current_date);

     QFile file("log.txt");
     file.open(QIODevice::WriteOnly | QIODevice::Append);
     QTextStream text_stream(&file);
     text_stream << message << "rn";
     file.flush();
     file.close();

     mutex.unlock();
}

int main(int argc, char *argv[])
{
#if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
#endif

    QGuiApplication app(argc, argv);

    qInstallMessageHandler(outputMessage);

    QQmlApplicationEngine engine;
    const QUrl url(QStringLiteral("qrc:/main.qml"));
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                     &app, [url](QObject *obj, const QUrl &objUrl) {
        if (!obj && url == objUrl)
            QCoreApplication::exit(-1);
    }, Qt::QueuedConnection);
    engine.load(url);

    return app.exec();
}
