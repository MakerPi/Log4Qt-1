/******************************************************************************
 *
 * package:     Log4Qt
 * file:        dispatcher.h
 * created:     February 2011
 * author:      Andreas Bacher
 *
 *
 * Copyright 2011 Andreas Bacher
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 ******************************************************************************/

#ifndef LOG4QTDISPATCHER_H
#define LOG4QTDISPATCHER_H

/******************************************************************************
 * Dependencies
 ******************************************************************************/

#include <QtCore/QThread>
#include <QtCore/QList>

#include "loggingevent.h"

/******************************************************************************
 * Declarations
 ******************************************************************************/

namespace Log4Qt
{

class AsyncAppender;

/*!
 * \brief The class Dispatcher does the actual logging to the attached appanders.
 *
 * The Dispatcher is the worker object which class the attached apperders in the
 * the context of the DispatcherThread.
 *
 * \note All the functions declared in this class are thread-safe.
 */
class Dispatcher : public QObject
{
    Q_OBJECT
public:
    explicit Dispatcher(QObject *parent = 0);

    void setAsyncAppender(AsyncAppender *pAsyncAppender);

protected:
    virtual void customEvent(QEvent* event);

private:
    AsyncAppender *mpAsyncAppender;
};

/*!
 * \brief The class DispatcherThread is the tread with logs events asynchronously.
 *
 * \note All the functions declared in this class are thread-safe.
 */
class DispatcherThread : public QThread
{
    Q_OBJECT
public:
    explicit DispatcherThread(QObject *parent = 0);
    virtual ~DispatcherThread();

    //! posts the log event to the dispatchers threads event loop
    void postLoggingEvent(const LoggingEvent &rEvent) const;
    //! set the async appender
    void setAsyncAppender(AsyncAppender *pAsyncAppender);

protected:
    //! reimpl
    virtual void run();

private:
    Dispatcher *mpDispatcher;
};

/**************************************************************************
 * Operators, Helper
 **************************************************************************/


/**************************************************************************
 * Inline
 **************************************************************************/
} // namespace Log4Qt

#endif // DISPATCHER_H