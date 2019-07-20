/***************************************************************************
                          astrosql.h  -  description
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

#ifndef ASTROSQL_H
#define ASTROSQL_H

#include "../config.h"
#include "astrodefs.h"
#include "astrostring.h"

#ifdef NATIVE
extern "C"
{
# include <libpq-fe.h>
};
#else
# include <QSqlDatabase>
# include <QSqlQuery>
# include <QSqlRecord>
# include <QSqlError>
# include <QtCore>
#endif

class AstroSQL
{

	Q_DECLARE_TR_FUNCTIONS(AstroSQL)

	friend class AstroRequest;

public:

    AstroSQL();
    ~AstroSQL();
    bool Login(const QString& DataBase, const QString& UserName, const QString& Password, const QString& HostName);

    inline bool IfOk() const {
        return Ok;
    };

    inline AstroString Error() const
    {
#ifdef NATIVE
			  return PQerrorMessage(conn);
#else
        return AstroString(Sdb.lastError().text());
#endif
    }

private:

#ifdef NATIVE
		PGconn* conn;
#else
    QSqlDatabase Sdb;
#endif
    bool Ok;
};

extern AstroSQL* Asq;

class AstroRequest
#ifndef NATIVE
            : public QSqlQuery
#endif
{
public:

    /** Constructor */
    inline AstroRequest(AstroSQL* asql = Asq, bool exception = false)
    {
        Asql = asql;
        Exception = exception;
#ifdef NATIVE
        Result = 0;
#endif
    }

    /** Destructor */
    ~AstroRequest() {
        Clear();
    };

    /** Returns true if good request */
    inline bool IfOk() const {
        return Ok;
    }

    /** Sets the exception flag */
    inline void SetException(bool exception) {
        Exception = exception;
    }

    /** Gets the excpetion flag */
    inline bool GetException() const {
        return Exception;
    }

    /** Clears the current request buffer */
    inline void Clear()
    {
#ifdef NATIVE
        if (Result) PQclear(Result);
        Result = 0;
				tuple = 0;
#endif
    }

    /** Executes a SQL request
        @param c the sql request with a printf like syntax,
        where only the %c %s %d and %f are processed.
        It also exists a %b for boolean, which admits 0 or 1 as input and
        produces 'f' or 't' into the final sql string
    */
    bool Exec(const char *c, ...);

    /** true if points on a valid record 
		 @param is effective if true, Effective must be also true */
    bool Valid(bool iseffective = false) const;

    /** Points on the first item. */
    void First();

    /** Informs the request to pass to the next row. Returns false if no next */
    bool Next();

		/** true if the request has been effective, i.e. affected at least 1 tuple */
		bool Effective() const;

    /** Updates the comment field of a Data table of index idx
        @param comment the comment itself (Saved as Utf8)
        @param idx the row Idx
    */
    bool SetComment(const AstroString& comment, Index idx);

    /** Returns the AstroString v
      @param c value of the field whose the name is c */
    AstroString operator < (const char* c) const ;

    /** Returns the integer value of the field whose the name is c */
    int GetInt(const char *c, const int defval = 0) const;

    /** Returns the double value of the field whose the name is c */
    double GetDouble(const char *, const double& defval = 0.0) const;

    /** Returns the character value of the field whose the name is c */
    char GetChar(const char *, const char defval = 0) const;

    /** Returns the boolean value of the field whose the name is c */
    bool GetBool(const char *, const bool defval = false) const;

    Long GetLong(const char *, const Long defval = 0) const;

    /** Return the index of the next available id for the table 'table'
    @param table the table name
    @return Index id
    */
    Index NextId(const char *table) const;

    /** Begin a transaction */
    inline void Begin() {
        Exec("BEGIN");
    }

    /** Commits a transaction */
    inline void Commit() {
        Exec("COMMIT");
    }

    /** Roobacks a transaction */
    inline void Rollback() {
        Exec("ROLLBACK");
    }

private:

    AstroSQL* Asql;
#ifndef NATIVE
    QSqlRecord Sr;
#else
    inline int GetIndex(const char *c) const {
        return Ok ? PQfnumber(Result, c) : -1;
    }
    inline const char* Get(Index idx) const
    {
			if (int(idx) == -1)
        {
            printf("Invalid index\n");
            return 0;
        }
			if(PQntuples(Result) == 0) return 0;
        return Ok ? PQgetvalue(Result, tuple, idx) : 0;
    }
    PGresult* Result;
#endif
    int tuple;
    bool Ok, Exception;
};

#endif
