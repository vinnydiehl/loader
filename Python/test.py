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

from loader import Loader

print 'With DisplayProgress enabled:\n'

progress = Loader()

while not progress.Finished():
    progress.Increment(10)
    progress.Display()

print '\nWith DisplayProgress disabled:\n'

progress.DisplayProgress = False
progress.Reset()

while not progress.Finished():
    progress.Increment(10)
    progress.Display()
