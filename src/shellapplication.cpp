/*
 * Copyright (C) 2013 Simon Busch <morphis@gravedo.de>
 * Copyright (c) 2014 Yen-Chin, Lee <coldnew.tw@gmail.com>
 *
 * Licensed to the Apache Software Foundation (ASF) under one or more
 * contributor license agreements. See the NOTICE file distributed with
 * this work for additional information regarding copyright ownership.
 * The ASF licenses this file to You under the Apache License, Version 2.0
 * (the "License"); you may not use this file except in compliance with
 * the License. You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include <QDebug>
#include <QDir>
#include <QFile>
#include <QQmlComponent>
#include <QJsonDocument>
#include <QJsonObject>
#include <QFont>

#include "shellapplication.h"

ShellApplication::ShellApplication(int argc, char **argv) :
    QGuiApplication(argc, argv),
    mEngine(this)
{
    mShellStorageDirs << "/usr/share/copycat/shells";

    connect(&mEngine, &QQmlEngine::quit, [=]() {
            this->quit();
        });
}

ShellApplication::~ShellApplication()
{
}

bool ShellApplication::create(const QString& name)
{
    QByteArray manifestData;
    QString shellPath;

    foreach (QString dir, mShellStorageDirs) {
        QFile manifestFile(QString("%1/%2/manifest.json").arg(dir).arg(name));
        if (!manifestFile.exists())
            continue;

        if (!manifestFile.open(QIODevice::ReadOnly))
            continue;

        manifestData = manifestFile.readAll();

        QFileInfo manifestFileInfo(manifestFile);
        shellPath = manifestFileInfo.absoluteDir().absolutePath();
    }

    if (shellPath.isEmpty()) {
        qWarning() << "Could not find manifest for shell" << name;
        return false;
    }

    QJsonDocument manifest = QJsonDocument::fromJson(manifestData);
    if (!manifest.isObject()) {
        qWarning() << "Manifest for shell" << name << "is invalid!";
        return false;
    }

    QJsonObject root = manifest.object();
    if (!(root.contains("name") && root.value("name").toString() == name) || !root.contains("main")) {
        qWarning() << "Failed to load shell" << name << "cause of a invalid manifest";
        return false;
    }

    if (root.contains("defaultFont") && root.value("defaultFont").isString()) {
        QFont defaultFont(root.value("defaultFont").toString());
        setFont(defaultFont);
    }

    QString mainPath(QString("%1/%2").arg(shellPath).arg(root.value("main").toString()));
    return load(mainPath);
}

bool ShellApplication::load(const QString& path)
{
    if (path.isEmpty()) {
        qWarning() << "Invalid shell path:" << path;
        return false;
    }

    QQmlComponent shellComponent(&mEngine, QUrl(path));
    if (shellComponent.isError()) {
        qWarning() << "Errors while loading shell from" << path;
        qWarning() << shellComponent.errors();
        return false;
    }

    QObject *shell = shellComponent.beginCreate(mEngine.rootContext());
    if (!shell) {
        qWarning() << "Error creating shell from" << path;
        qWarning() << shellComponent.errors();
        return false;
    }

    shellComponent.completeCreate();

    return true;
}
