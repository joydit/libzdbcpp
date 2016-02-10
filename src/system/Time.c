/* Generated by re2c 0.16 on Wed Feb 10 08:24:32 2016 */
#line 1 "src/system/Time.re"
/*
 * Copyright (C) Tildeslash Ltd. All rights reserved.
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 3.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 * In addition, as a special exception, the copyright holders give
 * permission to link the code of portions of this program with the
 * OpenSSL library under certain conditions as described in each
 * individual source file, and distribute linked combinations
 * including the two.
 *
 * You must obey the GNU General Public License in all respects
 * for all of the code used other than OpenSSL.
 */


#include "Config.h"

#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <time.h>
#include <sys/time.h>
#include <sys/types.h>
#include <sys/select.h>
#include <limits.h>

#include "Str.h"
#include "system/System.h"
#include "system/Time.h"


/**
 * Implementation of the Time interface
 *
 * ISO 8601: http://en.wikipedia.org/wiki/ISO_8601
 * @file
 */


/* ----------------------------------------------------------- Definitions */

#ifndef HAVE_TIMEGM
/*
 * Spdylay - SPDY Library
 *
 * Copyright (c) 2013 Tatsuhiro Tsujikawa
 *
 * Permission is hereby granted, free of charge, to any person obtaining
 * a copy of this software and associated documentation files (the
 * "Software"), to deal in the Software without restriction, including
 * without limitation the rights to use, copy, modify, merge, publish,
 * distribute, sublicense, and/or sell copies of the Software, and to
 * permit persons to whom the Software is furnished to do so, subject to
 * the following conditions:
 *
 * The above copyright notice and this permission notice shall be
 * included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE
 * LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION
 * OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION
 * WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */


/* Counter the number of leap year in the range [0, y). The |y| is the
 year, including century (e.g., 2012) */
static int count_leap_year(int y)
{
        y -= 1;
        return y/4-y/100+y/400;
}


/* Returns nonzero if the |y| is the leap year. The |y| is the year,
 including century (e.g., 2012) */
static int is_leap_year(int y)
{
        return y%4 == 0 && (y%100 != 0 || y%400 == 0);
}


/* The number of days before ith month begins */
static int daysum[] = {
        0, 31, 59, 90, 120, 151, 181, 212, 243, 273, 304, 334
};


/* Based on the algorithm of Python 2.7 calendar.timegm. */
time_t timegm(struct tm *tm)
{
        int days;
        int num_leap_year;
        int64_t t;
        if(tm->tm_mon > 11) {
                return -1;
        }
        num_leap_year = count_leap_year(tm->tm_year + 1900) - count_leap_year(1970);
        days = (tm->tm_year - 70) * 365 +
        num_leap_year + daysum[tm->tm_mon] + tm->tm_mday-1;
        if(tm->tm_mon >= 2 && is_leap_year(tm->tm_year + 1900)) {
                ++days;
        }
        t = ((int64_t)days * 24 + tm->tm_hour) * 3600 + tm->tm_min * 60 + tm->tm_sec;
        if(sizeof(time_t) == 4) {
                if(t < INT_MIN || t > INT_MAX) {
                        return -1;
                }
        }
        return t;
}
#endif /* !HAVE_TIMEGM */

#if HAVE_STRUCT_TM_TM_GMTOFF
#define TM_GMTOFF tm_gmtoff
#else
#define TM_GMTOFF tm_wday
#endif

#define _i2a(i) (x[0] = ((i) / 10) + '0', x[1] = ((i) % 10) + '0')


/* --------------------------------------------------------------- Private */


static inline int _a2i(const char *a, int l) {
        int n = 0;
        for (; *a && l--; a++)
                n = n * 10 + (*a) - '0';
        return n;
}


/* ----------------------------------------------------- Protected methods */


#ifdef PACKAGE_PROTECTED
#pragma GCC visibility push(hidden)
#endif


time_t Time_toTimestamp(const char *s) {
        if (STR_DEF(s)) {
                struct tm t = {};
                if (Time_toDateTime(s, &t)) {
                        t.tm_year -= 1900;
                        time_t offset = t.TM_GMTOFF;
                        return timegm(&t) - offset;
                }
        }
	return 0;
}


struct tm *Time_toDateTime(const char *s, struct tm *t) {
        assert(t);
        assert(s);
        struct tm tm = {.tm_isdst = -1}; 
        int has_date = false, has_time = false;
        const char *limit = s + strlen(s), *marker, *token, *cursor = s;
	while (true) {
		if (cursor >= limit) {
                        if (has_date || has_time) {
                                *(struct tm*)t = tm;
                                return t;
                        }
                        THROW(SQLException, "Invalid date or time");
                }
                token = cursor;
                
#line 187 "<stdout>"
{
	unsigned char yych;
	unsigned int yyaccept = 0;
	static const unsigned char yybm[] = {
		  0,   0,   0,   0,   0,   0,   0,   0, 
		  0,   0,   0,   0,   0,   0,   0,   0, 
		  0,   0,   0,   0,   0,   0,   0,   0, 
		  0,   0,   0,   0,   0,   0,   0,   0, 
		  0,   0,   0,   0,   0,   0,   0,   0, 
		  0,   0,   0,   0,   0,   0,   0,   0, 
		128, 128, 128, 128, 128, 128, 128, 128, 
		128, 128,   0,   0,   0,   0,   0,   0, 
		  0,   0,   0,   0,   0,   0,   0,   0, 
		  0,   0,   0,   0,   0,   0,   0,   0, 
		  0,   0,   0,   0,   0,   0,   0,   0, 
		  0,   0,   0,   0,   0,   0,   0,   0, 
		  0,   0,   0,   0,   0,   0,   0,   0, 
		  0,   0,   0,   0,   0,   0,   0,   0, 
		  0,   0,   0,   0,   0,   0,   0,   0, 
		  0,   0,   0,   0,   0,   0,   0,   0, 
		  0,   0,   0,   0,   0,   0,   0,   0, 
		  0,   0,   0,   0,   0,   0,   0,   0, 
		  0,   0,   0,   0,   0,   0,   0,   0, 
		  0,   0,   0,   0,   0,   0,   0,   0, 
		  0,   0,   0,   0,   0,   0,   0,   0, 
		  0,   0,   0,   0,   0,   0,   0,   0, 
		  0,   0,   0,   0,   0,   0,   0,   0, 
		  0,   0,   0,   0,   0,   0,   0,   0, 
		  0,   0,   0,   0,   0,   0,   0,   0, 
		  0,   0,   0,   0,   0,   0,   0,   0, 
		  0,   0,   0,   0,   0,   0,   0,   0, 
		  0,   0,   0,   0,   0,   0,   0,   0, 
		  0,   0,   0,   0,   0,   0,   0,   0, 
		  0,   0,   0,   0,   0,   0,   0,   0, 
		  0,   0,   0,   0,   0,   0,   0,   0, 
		  0,   0,   0,   0,   0,   0,   0,   0, 
	};
	yych = *cursor;
	if (yych <= ',') {
		if (yych == '+') goto yy4;
	} else {
		if (yych <= '-') goto yy4;
		if (yych <= '/') goto yy2;
		if (yych <= '9') goto yy5;
	}
yy2:
	++cursor;
yy3:
#line 243 "src/system/Time.re"
	{
                        continue;
                 }
#line 240 "<stdout>"
yy4:
	yyaccept = 0;
	yych = *(marker = ++cursor);
	if (yych <= '/') goto yy3;
	if (yych <= '9') goto yy6;
	goto yy3;
yy5:
	yyaccept = 0;
	yych = *(marker = ++cursor);
	if (yych <= '/') goto yy3;
	if (yych <= '9') goto yy8;
	goto yy3;
yy6:
	yych = *++cursor;
	if (yych <= '/') goto yy7;
	if (yych <= '9') goto yy9;
yy7:
	cursor = marker;
	if (yyaccept <= 1) {
		if (yyaccept == 0) {
			goto yy3;
		} else {
			goto yy10;
		}
	} else {
		if (yyaccept == 2) {
			goto yy26;
		} else {
			goto yy32;
		}
	}
yy8:
	yych = *++cursor;
	if (yych <= '/') goto yy11;
	if (yych <= '9') goto yy12;
	goto yy11;
yy9:
	yyaccept = 1;
	yych = *(marker = ++cursor);
	if (yych == '\n') goto yy10;
	if (yych <= '/') goto yy13;
	if (yych <= '9') goto yy14;
	goto yy13;
yy10:
#line 230 "src/system/Time.re"
	{ // Timezone: +-HH:MM, +-HH or +-HHMM is offset from UTC in seconds
                        if (has_time) { // Only set timezone if time has been seen
                                tm.TM_GMTOFF = _a2i(token + 1, 2) * 3600;
                                if (isdigit(token[3]))
                                        tm.TM_GMTOFF += _a2i(token + 3, 2) * 60;
                                else if (isdigit(token[4]))
                                        tm.TM_GMTOFF += _a2i(token + 4, 2) * 60;
                                if (token[0] == '-')
                                        tm.TM_GMTOFF *= -1;
                        }
                        continue;
                 }
#line 298 "<stdout>"
yy11:
	yych = *++cursor;
	if (yych <= '/') goto yy7;
	if (yych <= '9') goto yy15;
	goto yy7;
yy12:
	yych = *++cursor;
	if (yych <= '/') goto yy7;
	if (yych <= '9') goto yy16;
	goto yy7;
yy13:
	yych = *++cursor;
	if (yych <= '/') goto yy7;
	if (yych <= '9') goto yy17;
	goto yy7;
yy14:
	yych = *++cursor;
	if (yych <= '/') goto yy7;
	if (yych <= '9') goto yy18;
	goto yy7;
yy15:
	yych = *++cursor;
	if (yych <= '/') goto yy7;
	if (yych <= '9') goto yy19;
	goto yy7;
yy16:
	yych = *++cursor;
	if (yych <= '/') goto yy20;
	if (yych <= '9') goto yy21;
	goto yy20;
yy17:
	yych = *++cursor;
	if (yych <= '/') goto yy7;
	if (yych <= '9') goto yy22;
	goto yy7;
yy18:
	yych = *++cursor;
	if (yych <= '/') goto yy10;
	if (yych <= '9') goto yy22;
	goto yy10;
yy19:
	yych = *++cursor;
	if (yych <= '/') goto yy23;
	if (yych <= '9') goto yy7;
	goto yy23;
yy20:
	yych = *++cursor;
	if (yych <= '/') goto yy7;
	if (yych <= '9') goto yy24;
	goto yy7;
yy21:
	yych = *++cursor;
	if (yych <= '/') goto yy7;
	if (yych <= '9') goto yy25;
	goto yy7;
yy22:
	yych = *++cursor;
	goto yy10;
yy23:
	yych = *++cursor;
	if (yych <= '/') goto yy7;
	if (yych <= '9') goto yy27;
	goto yy7;
yy24:
	yych = *++cursor;
	if (yych <= '/') goto yy7;
	if (yych <= '9') goto yy28;
	goto yy7;
yy25:
	yyaccept = 2;
	yych = *(marker = ++cursor);
	if (yych <= '-') {
		if (yych == ',') goto yy29;
	} else {
		if (yych <= '.') goto yy29;
		if (yych <= '/') goto yy26;
		if (yych <= '9') goto yy30;
	}
yy26:
#line 222 "src/system/Time.re"
	{ // Compressed Time: HHMMSS
                        tm.tm_hour = _a2i(token, 2);
                        tm.tm_min  = _a2i(token + 2, 2);
                        tm.tm_sec  = _a2i(token + 4, 2);
                        has_time = true;
                        continue;
                 }
#line 386 "<stdout>"
yy27:
	yych = *++cursor;
	if (yych <= '/') goto yy7;
	if (yych <= '9') goto yy31;
	goto yy7;
yy28:
	yych = *++cursor;
	if (yych <= '/') goto yy33;
	if (yych <= '9') goto yy7;
	goto yy33;
yy29:
	yych = *++cursor;
	if (yybm[0+yych] & 128) {
		goto yy34;
	}
	goto yy7;
yy30:
	yych = *++cursor;
	if (yych <= '/') goto yy7;
	if (yych <= '9') goto yy36;
	goto yy7;
yy31:
	yyaccept = 3;
	yych = *(marker = ++cursor);
	if (yych == ',') goto yy38;
	if (yych == '.') goto yy38;
yy32:
#line 214 "src/system/Time.re"
	{ // Time: HH:MM:SS
                        tm.tm_hour = _a2i(token, 2);
                        tm.tm_min  = _a2i(token + 3, 2);
                        tm.tm_sec  = _a2i(token + 6, 2);
                        has_time = true;
                        continue;
                 }
#line 422 "<stdout>"
yy33:
	yych = *++cursor;
	if (yych <= '/') goto yy7;
	if (yych <= '9') goto yy39;
	goto yy7;
yy34:
	++cursor;
	yych = *cursor;
	if (yybm[0+yych] & 128) {
		goto yy34;
	}
	goto yy26;
yy36:
	++cursor;
#line 206 "src/system/Time.re"
	{ // Compressed Date: YYYYMMDD
                        tm.tm_year  = _a2i(token, 4);
                        tm.tm_mon   = _a2i(token + 4, 2) - 1;
                        tm.tm_mday  = _a2i(token + 6, 2);
                        has_date = true;
                        continue;
                 }
#line 445 "<stdout>"
yy38:
	yych = *++cursor;
	if (yych <= '/') goto yy7;
	if (yych <= '9') goto yy40;
	goto yy7;
yy39:
	yych = *++cursor;
	if (yych <= '/') goto yy7;
	if (yych <= '9') goto yy42;
	goto yy7;
yy40:
	++cursor;
	yych = *cursor;
	if (yych <= '/') goto yy32;
	if (yych <= '9') goto yy40;
	goto yy32;
yy42:
	++cursor;
#line 198 "src/system/Time.re"
	{ // Date: YYYY-MM-DD
                        tm.tm_year  = _a2i(token, 4);
                        tm.tm_mon   = _a2i(token + 5, 2) - 1;
                        tm.tm_mday  = _a2i(token + 8, 2);
                        has_date = true;
                        continue;
                 }
#line 472 "<stdout>"
}
#line 246 "src/system/Time.re"

        }
	return NULL;
}


char *Time_toString(time_t time, char result[20]) {
        assert(result);
        char x[2];
        struct tm ts = {.tm_isdst = -1};
        gmtime_r(&time, &ts);
        memcpy(result, "YYYY-MM-DD HH:MM:SS\0", 20);
        /*              0    5  8  11 14 17 */
        _i2a((ts.tm_year+1900)/100);
        result[0] = x[0];
        result[1] = x[1];
        _i2a((ts.tm_year+1900)%100);
        result[2] = x[0];
        result[3] = x[1];
        _i2a(ts.tm_mon + 1); // Months in 01-12
        result[5] = x[0];
        result[6] = x[1];
        _i2a(ts.tm_mday);
        result[8] = x[0];
        result[9] = x[1];
        _i2a(ts.tm_hour);
        result[11] = x[0];
        result[12] = x[1];
        _i2a(ts.tm_min);
        result[14] = x[0];
        result[15] = x[1];
        _i2a(ts.tm_sec);
        result[17] = x[0];
        result[18] = x[1];
	return result;
}


time_t Time_now(void) {
	struct timeval t;
	if (gettimeofday(&t, NULL) != 0)
                THROW(AssertException, "%s", System_getLastError());
	return t.tv_sec;
}


long long Time_milli(void) {
	struct timeval t;
	if (gettimeofday(&t, NULL) != 0)
                THROW(AssertException, "%s", System_getLastError());
	return (long long)t.tv_sec * 1000  +  (long long)t.tv_usec / 1000;
}


int Time_usleep(long u) {
        struct timeval t;
        t.tv_sec = u / USEC_PER_SEC;
        t.tv_usec = (suseconds_t)(u % USEC_PER_SEC);
        select(0, 0, 0, 0, &t);
        return true;
}


#ifdef PACKAGE_PROTECTED
#pragma GCC visibility pop
#endif