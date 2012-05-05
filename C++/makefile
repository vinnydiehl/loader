# Loader - A CLI progress bar.
# Copyright (C) 2012 Vinny Diehl
# 
# This program is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.
# 
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
# 
# You should have received a copy of the GNU General Public License
# along with this program.  If not, see <http://www.gnu.org/licenses/>.

VERSION = 1.0b1
OBJS = test.o Loader.o
CC = g++
DEBUG = -g
CFLAGS = -Wall -c $(DEBUG)
LFLAGS = -Wall $(DEBUG)

test : $(OBJS)
	$(CC) $(LFLAGS) $(OBJS) -o test

test.o : Loader.h
	$(CC) $(CFLAGS) test.cpp

Loader.o : Loader.h
	$(CC) $(CFLAGS) Loader.cpp

clean :
	rm $(OBJS) test.exe

tar :
	tar -czf Loader$(VERSION)_src.tar.gz test.cpp \
	    Loader.cpp Loader.h makefile
