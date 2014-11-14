/*
 * Copyright (C) 2014 Yen-Chin Lee <coldnew.tw@gmail.com>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>
 */

#include <QtCore>
#include <QtGlobal>
#include <QString>

#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>

#include <systemd/sd-daemon.h>

#include "shellapplication.h"

#define DEFAULT_SHELL_NAME  "android"

static bool verbose = false;

void messageHandler(QtMsgType type, const QMessageLogContext &context, const QString &msg)
{
    QString timeStr = QTime::currentTime().toString("hh:mm:ss.zzz");

    switch(type) {
        case QtDebugMsg:
            if (verbose)
                fprintf(stdout, "DEBUG: %s: %s\n", timeStr.toUtf8().constData(), msg.toUtf8().constData());
            break;
        case QtWarningMsg:
            fprintf(stdout, "WARNING: %s: %s\n", timeStr.toUtf8().constData(), msg.toUtf8().constData());
            break;
        case QtCriticalMsg:
            fprintf(stdout, "CRITICAL: %s: %s\n", timeStr.toUtf8().constData(), msg.toUtf8().constData());
            break;
        case QtFatalMsg:
            fprintf(stdout, "FATAL: %s: %s\n", timeStr.toUtf8().constData(), msg.toUtf8().constData());
            break;
        default:
            fprintf(stdout, "INFO: %s: %s\n", timeStr.toUtf8().constData(), msg.toUtf8().constData());
            break;
    }
}

int main(int argc, char *argv[])
{
    qInstallMessageHandler(messageHandler);

    QString verboseMode = qgetenv("COPYCAT_DEBUG");
    if (verboseMode == "1")
        verbose = true;

    // Get XDG_RUNTIME_DIR from env
    QString xdgRuntimeDirName = qgetenv("XDG_RUNTIME_DIR");
    if (xdgRuntimeDirName.isEmpty()) {
        qFatal("Please set XDG_RUNTIME_DIR variable first.");
        exit(1);
    }

    // Cleanup old-session and recreate one
    QDir xdgRuntimeDir(xdgRuntimeDirName);
    if (xdgRuntimeDir.exists())
        xdgRuntimeDir.removeRecursively();

    mkdir(xdgRuntimeDirName.toStdString().c_str(), 0700);
    qDebug("Use XDG_RUNTIME_DIR=%s", xdgRuntimeDirName.toUtf8().constData());

    QString shellName = qgetenv("COPYCAT_SHELL");
    if (shellName.isEmpty())
        shellName = DEFAULT_SHELL_NAME;

    qDebug() << "Use shell: " << shellName;

    ShellApplication app(argc, argv);
    if (!app.create(shellName)) {
        qFatal("Can't create shell application.");
        exit(1);
    }

    // Notify systemd we are done
    sd_notify(0, "READY=1");

    return app.exec();
}

#include "main.moc"
