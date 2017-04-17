/****************************************************************************
**
** Copyright (C) 2016 The Qt Company Ltd.
** Contact: https://www.qt.io/licensing/
**
** This file is part of the Qt Data Visualization module of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:GPL$
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and The Qt Company. For licensing terms
** and conditions see https://www.qt.io/terms-conditions. For further
** information use the contact form at https://www.qt.io/contact-us.
**
** GNU General Public License Usage
** Alternatively, this file may be used under the terms of the GNU
** General Public License version 3 or (at your option) any later version
** approved by the KDE Free Qt Foundation. The licenses are as published by
** the Free Software Foundation and appearing in the file LICENSE.GPL3
** included in the packaging of this file. Please review the following
** information to ensure the GNU General Public License requirements will
** be met: https://www.gnu.org/licenses/gpl-3.0.html.
**
** $QT_END_LICENSE$
**
****************************************************************************/

#ifndef AUDIOLEVELSIODEVICE_H
#define AUDIOLEVELSIODEVICE_H

#include <QtDataVisualization/qbardataproxy.h>
#include <QtCore/QIODevice>
#include <QObject>
#include <QFile>
#include <QDateTime>
#include <QtMath>
#include "wavepaint.h"
#include <global.h>

using namespace QtDataVisualization;
class AudioLevels;
class SpeechRecognizer;
class AudioLevelsIODevice : public QIODevice
{
    Q_OBJECT
public:
    explicit AudioLevelsIODevice(QObject *parent = 0);
    ~AudioLevelsIODevice();

public:
    QTime qt;
    struct  Global:: speech_rec* getAudioData();
    static struct Global:: speech_rec* rec;
    void startSpeech(char*data,qint64 maxSize);
protected:
    qint64 readData(char *data, qint64 maxSize);
    qint64 writeData(const char *data, qint64 maxSize);


private:
    //! [0]
    QBarDataProxy *m_proxy;
    QBarDataArray *m_array;
    //! [0]
public slots:

};

#endif
