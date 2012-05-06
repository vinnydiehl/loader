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
