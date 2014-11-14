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

#ifndef _SHELLAPPLICATION_H_
#define _SHELLAPPLICATION_H_

#include <QGuiApplication>
#include <QQmlEngine>
#include <QStringList>

class ShellApplication : public QGuiApplication
{
    Q_OBJECT

public:
    ShellApplication(int argc, char **argv);
    virtual ~ShellApplication();

    bool create(const QString& name);

private:
    QQmlEngine mEngine;
    QStringList mShellStorageDirs;

    bool load(const QString& path);
};

#endif /* _SHELLAPPLICATION_H_ */
