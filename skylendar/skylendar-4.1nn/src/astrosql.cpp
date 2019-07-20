/***************************************************************************
                          astrosql.cpp  -  description
                             -------------------
    begin                : Wed Nov 7 2001
    copyright            : (C) 2000 by Christophe Gros
    email                : skylendar@yahoo.com
 ***************************************************************************/

/***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/

#include "astrosql.h"
#include "astroresources.h"
#include "astroutils.h"
#include <cstdlib>
#include <cstring>
#include <cstdio>
#include <cstdarg>
#include <iostream>
#include <QDebug>

AstroSQL::AstroSQL()
{
#ifndef NATIVE
    Ok = false;
    Sdb = QSqlDatabase::addDatabase("QPSQL");
    if (!Sdb.isValid())
    {
        AstroMessage(i18n("Sorry, Can't find the PostgreSQL Qt Driver !"));
        return;
    }
    Ok = true;
// #else
//   char buf[80];
//   Ok = true;
//   sprintf(buf, "dbname = %s user = %s", dbname.Data(), user.Data());
//   conn = PQconnectdb(buf);
//   if(!conn)
//   {
//     Ok = false;
//     return;
//   }
//   enum ConnStatusType cst = PQstatus(conn);
//   if(cst != CONNECTION_OK)
//   Ok = false;
#endif
}

bool AstroSQL::Login(const QString& DataBase, const QString& UserName, const QString& Password, const QString& HostName)
{
#ifndef NATIVE
    Sdb.setDatabaseName(DataBase);
    Sdb.setUserName(UserName);
    Sdb.setPassword(Password);
    Sdb.setHostName(HostName);
    if (Sdb.open() && !Sdb.isOpenError())
    {
        Asr->DbHost = HostName;
        Asr->DbName = DataBase;
        Asr->DbUser = UserName;
        Asr->DbPass = Password;
        return true;
    }
    return false;
#else
    char buf[80];
    Ok = true;
    sprintf(buf, "dbname = %s user = %s host = %s", DataBase.toUtf8().data(), UserName.toUtf8().data(), HostName.toUtf8().data());
    conn = PQconnectdb(buf);
    if (!conn)
    {
        Ok = false;
        return false;
    }
    ConnStatusType cst = PQstatus(conn);
    if (cst != CONNECTION_OK)
        Ok = false;
    return Ok;
#endif
}

bool AstroRequest::SetComment(const AstroString& as, Index idx)
{
#ifdef NATIVE
    ExecStatusType est;
#endif
    AstroString as1 = as;
    as1.Replace("'", "''");
    AstroString r("UPDATE Data SET Comment = '");
    r += as1;
    r += "' WHERE Idx = ";
    r += (int)idx;
    Ok = true;
    Clear();
#ifndef NATIVE
    *SC(QSqlQuery*, this) = Asql->Sdb.exec(r);
    if (!isValid())
    {
        Ok = false;
        return Ok;
    }
    Sr = Asql->Sdb.record("Data");
    first();
#else
    Result = PQexec(Asql->conn, r.toUtf8().data());
    if (!Result)
    {
        Ok = false;
        return false;
    }
    est = PQresultStatus(Result);
    if (est == PGRES_FATAL_ERROR || est == PGRES_NONFATAL_ERROR || est == PGRES_BAD_RESPONSE)
    {
        Ok = false;
        return false;
    }
#endif
    tuple = 0;
    return true;
}

AstroString AstroRequest::operator < (const char* c) const
{
#ifndef NATIVE
    return value(Sr.indexOf(c)).toString();
#else
    return AstroString((Get(GetIndex(c))));
#endif
}

int AstroRequest::GetInt(const char *c, const int defval) const
{
	int i;
#ifndef NATIVE
    i = Sr.indexOf(c);
    const QVariant qv = value(i);
    return (qv.isValid() && !isNull(i)) ? qv.toInt() : defval;
#else
		bool ok;
    i = AstroString(Get(GetIndex(c))).toInt(&ok);
    return ok ? i : defval;
#endif
}

double AstroRequest::GetDouble(const char *c, const double& defval) const
{
#ifndef NATIVE
    int i = Sr.indexOf(c);
    const QVariant qv = value(i);
    return (qv.isValid() && !isNull(i)) ? qv.toDouble() : defval;
#else
		bool ok;
    double d = AstroString(Get(GetIndex(c))).toDouble(&ok);
		return ok ? d : defval;
#endif
}

char AstroRequest::GetChar(const char *c, const char defval) const
{
#ifndef NATIVE
    int i = Sr.indexOf(c);
    const QVariant qv = value(i);
    const QString s = qv.toString().left(1);
    return (qv.isValid() && !isNull(i)) ? s.constData()->toLatin1()/*char(*s.toUtf8().data())*/ : defval;
#else
		const char *c1 = Get(GetIndex(c));
    return (c1 && *c1) ? *c1 : defval;
#endif
}

bool AstroRequest::GetBool(const char *c, const bool defval) const
{
#ifndef NATIVE
    int i = Sr.indexOf(c);
    const QVariant qv = value(i);
    return (qv.isValid() && !isNull(i)) ? qv.toBool() : defval;
#else
    const char *c1 = Get(GetIndex(c));
    return c1 ? *c1 == 't' : defval;
#endif
}

Long AstroRequest::GetLong(const char *c, const Long defval) const
{
#ifndef NATIVE
    int i = Sr.indexOf(c);
    const QVariant qv = value(i);
    return (qv.isValid() && !isNull(i)) ? qv.toLongLong() : defval;
#else
    bool ok;
    FlagType f = AstroString(Get(GetIndex(c))).tolonglong(&ok);
    return ok ? f : defval;
#endif
}

AstroSQL::~AstroSQL()
{
#ifndef NATIVE
    Sdb.close();
#else
    PQfinish(conn);
#endif
}

bool AstroRequest::Exec(const char *c, ...)
{
    QString buf, conv;
    va_list vl;
    va_start(vl, c);
    for (; *c; c++)
    {
        if (*c != '%')
        {
            if (*c == '\\')
                c++;
            buf += *c;
        }
        else
        {
            c++;
            switch (*c)
            {
            case 'c' :
                buf += char(va_arg(vl, int));
                break;
            case 's' :
                buf += va_arg(vl, char*);
                break;
            case 'd' :
                buf += conv.setNum(va_arg(vl, int));
                break;
            case 'b' :
                buf += va_arg(vl, int) ? "'t'" : "'f'";
                break;
            case 'f' :
                buf += conv.setNum(va_arg(vl, double));
                break;
            case 'a' :
                conv = *va_arg(vl, AstroString*);
                buf += conv.replace("'", "''");
                break;
            case 'A' :
                buf += *va_arg(vl, AstroString*);
                break;
            case 'l' :
#if __SIZEOF_LONG__ == 8

                buf += conv.setNum(qlonglong(va_arg(vl, long)));
#else
                buf += conv.setNum(va_arg(vl, qlonglong(long long)));
#endif
                break;
            };
        }
    }
    Ok = true;
    va_end(vl);
    Clear();
    if (Asr->IfDebug) std::cout << buf.toUtf8().data() << std::endl;
#ifndef NATIVE
    *SC(QSqlQuery*, this) = Asql->Sdb.exec(buf);
    if (lastError().type() != QSqlError::NoError)
    {
        Ok = false;
        AstroString as = AstroString(lastError().text());
#ifdef IFEXCEPT
        if (Exception)
            throw AstroException(DbException, as);
        else
#endif
            AstroMessage(as);
        return Ok;
    }
		//std::cout << numRowsAffected() << std::endl;
    first();
    Sr = record();
#else
    ExecStatusType est;
    Result = PQexec(Asql->conn, buf.toUtf8().data());
    if (!Result)
    {
        Ok = false;
        return false;
    }
    est = PQresultStatus(Result);
    if (est == PGRES_FATAL_ERROR || est == PGRES_NONFATAL_ERROR || est == PGRES_BAD_RESPONSE)
    {
			AstroString as = PQresultErrorMessage(Result);
#ifdef IFEXCEPT
        if (Exception)
					throw AstroException(DbException, as);
        else
#endif
				AstroMessage(as);
        Ok = false;
        return false;
    }
#endif
    tuple = 0;
    return true;
}

void AstroRequest::First()
{
#ifndef NATIVE
    first();
#else
		tuple = 0;
#endif
}

bool AstroRequest::Next()
{
#ifndef NATIVE
    return next();
#else
		if((tuple + 1) >= PQntuples(Result)) return false;
		tuple++;
		return true;
#endif
}

bool AstroRequest::Effective() const
{
#ifndef NATIVE
	return numRowsAffected() > 0;
#else
	bool ok;
	int i = AstroString(PQcmdTuples(Result)).toInt(&ok);
	return (ok && i);
#endif
}

bool AstroRequest::Valid(bool iseffective) const
{
#ifndef NATIVE
	return iseffective ? isValid() && Effective() : isValid();
#else
	return iseffective ? (PQntuples(Result) > 0) && Effective() : (PQntuples(Result) > 0);
#endif
}

Index AstroRequest::NextId(const char *table) const
{
	AstroString as;
#ifndef NATIVE
    QSqlQuery qs = Asql->Sdb.exec(Sprintf("SELECT NEXTVAL('%s_Idx_Seq')", &as, table));
    if (qs.lastError().number() != -1)
        return 0;
    qs.first();
    return qs.value(0).toInt();
#else
		Sprintf("SELECT NEXTVAL('%s_Idx_Seq')", &as, table);
		PGresult *res1 = PQexec(Asql->conn, as.toUtf8().data());
		as = PQgetvalue(res1, 0, 0);
		PQclear(res1);
		return as.toInt();
#endif
}


