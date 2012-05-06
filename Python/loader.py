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

import sys

# Cross-platform terminal size

def getTerminalSize():
   import platform
   current_os = platform.system()
   tuple_xy = None
   if current_os == 'Windows':
       tuple_xy = _getTerminalSize_windows()
       if tuple_xy is None:
          tuple_xy = _getTerminalSize_tput()
   if current_os == 'Linux' or current_os == 'Darwin' \
      or  current_os.startswith('CYGWIN'):
       tuple_xy = _getTerminalSize_linux()
   if tuple_xy is None:
       print "default"
       tuple_xy = (80, 25)
   return tuple_xy

def _getTerminalSize_windows():
    res = None
    try:
        from ctypes import windll, create_string_buffer

        h = windll.kernel32.GetStdHandle(-12)
        csbi = create_string_buffer(22)
        res = windll.kernel32.GetConsoleScreenBufferInfo(h, csbi)
    except:
        return None
    if res:
        import struct

        (bufx, bufy, curx, cury, wattr,
         left, top, right, bottom, maxx, maxy) = \
            struct.unpack("hhhhHhhhhhh", csbi.raw)
        sizex = right - left + 1
        sizey = bottom - top + 1

        return sizex, sizey
    else:
        return None

def _getTerminalSize_tput():
    try:
       import subprocess

       proc = subprocess.Popen(["tput", "cols"], 
                             stdin=subprocess.PIPE, stdout=subprocess.PIPE)
       output = proc.communicate(input=None)
       cols = int(output[0])
       proc = subprocess.Popen(["tput", "lines"],
                               stdin=subprocess.PIPE, stdout=subprocess.PIPE)
       output = proc.communicate(input=None)
       rows = int(output[0])

       return (cols,rows)
    except:
       return None

def _getTerminalSize_linux():
    def ioctl_GWINSZ(fd):
        try:
            import fcntl, termios, struct, os
            cr = struct.unpack('hh', fcntl.ioctl(fd, termios.TIOCGWINSZ,'1234'))
        except:
            return None
        return cr
    cr = ioctl_GWINSZ(0) or ioctl_GWINSZ(1) or ioctl_GWINSZ(2)
    if not cr:
        try:
            fd = os.open(os.ctermid(), os.O_RDONLY)
            cr = ioctl_GWINSZ(fd)
            os.close(fd)
        except:
            pass
    if not cr:
        try:
            cr = (env['LINES'], env['COLUMNS'])
        except:
            return None
    return int(cr[1]), int(cr[0])

CWIDTH = getTerminalSize()[0]

class Loader:
    def __init__(self, displayProgress=True):
        self.progress = 0
        self.DisplayProgress = displayProgress

        self.DefaultBody, self.DefaultEnd = '=', '>'
        self.DefaultLeft, self.DefaultRight = '[', ']'
        self.DefaultWhitespace = ' '
    
    def Display(self, body='=', end='>', left='[', right=']', ws=' '):
        '''
           Displays the loading bar. It will fill the entire console and look
           like the ones displayed below. | represents the ends of the console
           screen and are not actually printed.

           DisplayProgress
|[====================================================================>] 100% |
           !DisplayProgress
|[==========================================================================>]|

           This is the default style; it can be modified in the parameters.
           Defaults:
             Body: =
             End: >
             Left: [
             Right: ]
             Whitespace: <Space>
        '''

        builder = left
        maxBarLength = CWIDTH - 9 if self.DisplayProgress else CWIDTH - 3
        
        for i in range(int(maxBarLength * self.progress / 100.0)):
            builder += body
        builder += end
        while len(builder) < maxBarLength + 2:
            builder += ws
        builder += right

        if self.DisplayProgress:
            if self.progress < 100:
                builder += ' '
            if self.progress < 10:
                builder += ' '
            builder += ' %d%%' % self.progress

            while len(builder) < CWIDTH:
                builder += ' '
        
        sys.stdout.write(builder)

    def GetProgress(self):
        return self.progress
    def SetProgress(self, n):
        self.progress = 0 if n < 0 else 100 if n > 100 else n

    def Finished(self):
        return self.progress == 100;

    def Increment(self, n):
        added = self.progress + n
        self.progress = 0 if added < 0 else 100 if added > 100 else added
    def Decrement(self, n):
        subtracted = self.progress + n
        self.progress = 0 if subtracted < 0 else \
                   100 if subtracted > 100 else subtracted
    
    def Reset(self):
        self.progress = 0
    def Complete(self):
        self.progress = 100
