/***************************************************************************
                          astrotimer.h  -  description
                             -------------------
    begin                : Sat Jan 10 2007
    copyright            : (C) 2007 by Christophe Gros
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

#ifndef ASTROTIMER_H
#define ASTROTIMER_H

#include <linux/rtc.h>
#include <sys/ioctl.h>
#include <fcntl.h>

class AstroTimer
{
public:

    /** Creates a timer with a tim-th time span (1/tim second) */
    inline AstroTimer(bool& ok, int tim = 8)
    {
        ok = true;
        fd = open("/dev/rtc", O_RDONLY);
        if (fd ==  -1)
        {
            ok = false;
            return;
        }
        int retval = ioctl(fd, RTC_IRQP_SET, tim);
        if (retval == -1)
        {
            ok = false;
            return;
        }
        retval = ioctl(fd, RTC_PIE_ON, 0);
        if (retval == -1)
        {
            ok = false;
            return;
        }
    }

    inline ~AstroTimer()
    {
        ioctl(fd, RTC_PIE_OFF, 0);
        close(fd);
    }

    /** Wait during the wanted time span */
    inline void Wait() const
    {
        unsigned long data;
        read(fd, &data, sizeof(unsigned long));
    }

private:

    int fd;
};

#endif
