### Makefile for pmmnew 
#  CFLAGS  = -O3 -ggdb
#  CC  = cc for nomal life, c++ for good debugging comments 

# -lm links the math library, libm.a .
# "lib" and ".a" are automatically added.

CFLAGS	= -O3 -lm  
CC 	= c++ 
SRCS 	= llist.c choose.c show_choose.c fileio.c\
	  filldatastrs.c pprint.c ranks.c main.c\
	  fillcueorders.c getsiminfo.c pmmutils.c linutils.c\
          takethebest.c weightedlinear.c unitlinear.c\
	  weightedtally.c unittally.c minimalist.c\
	  takethelast.c allalgutils.c crossval.c\
	  regression.c mlreg.c statlib.c arrays.c\
	  stats.c simple_bayes.c 
HEADRS	= llist.h choose.h show_choose.h fileio.h \
	  filldatastrs.h pprint.h ranks.h main.h \
	  fillcueorders.h getsiminfo.h pmmutils.h linutils.h\
	  takethebest.h weightedlinear.h unitlinear.h\
	  weightedtally.h unittally.h umacros.h\
	  minimalist.h takethelast.h allalgutils.h\
	  variables.h crossval.h\
	  regression.h mlreg.h statlib.h arrays.h global.h\
	  stats.h simple_bayes.h
OBJECTS = $(SRCS:.c=.o)

pmmnew: $(OBJECTS) 
	$(CC) $(CFLAGS) $(OBJECTS) -o pmmnew 

depend:
	makedepend -- $(CFLAGS) -- $(SRCS) $(HEADRS)

clean:
	rm *.o pmmnew



# DO NOT DELETE THIS LINE -- make depend depends on it.

llist.o: /usr/include/stdio.h /usr/include/standards.h
llist.o: /usr/include/sys/seek.h /usr/include/va_list.h
llist.o: /usr/include/sys/types.h /usr/include/mach/machine/vm_types.h
llist.o: /usr/include/sys/select.h /usr/include/getopt.h
llist.o: /usr/include/sys/limits.h /usr/include/sys/machine/machlimits.h
llist.o: /usr/include/sys/syslimits.h /usr/include/sys/machine/machtime.h
llist.o: /usr/include/sys/rt_limits.h /usr/include/stdlib.h
llist.o: /usr/include/time.h /usr/include/sys/timers.h
llist.o: /usr/include/sys/sysmisc.h main.h llist.h umacros.h
choose.o: /usr/include/stdio.h /usr/include/standards.h
choose.o: /usr/include/sys/seek.h /usr/include/va_list.h
choose.o: /usr/include/sys/types.h /usr/include/mach/machine/vm_types.h
choose.o: /usr/include/sys/select.h /usr/include/getopt.h
choose.o: /usr/include/sys/limits.h /usr/include/sys/machine/machlimits.h
choose.o: /usr/include/sys/syslimits.h /usr/include/sys/machine/machtime.h
choose.o: /usr/include/sys/rt_limits.h /usr/include/stdlib.h choose.h
show_choose.o: main.h show_choose.h /usr/include/stdio.h
show_choose.o: /usr/include/standards.h /usr/include/sys/seek.h
show_choose.o: /usr/include/va_list.h /usr/include/sys/types.h
show_choose.o: /usr/include/mach/machine/vm_types.h /usr/include/sys/select.h
show_choose.o: /usr/include/getopt.h /usr/include/sys/limits.h
show_choose.o: /usr/include/sys/machine/machlimits.h
show_choose.o: /usr/include/sys/syslimits.h
show_choose.o: /usr/include/sys/machine/machtime.h
show_choose.o: /usr/include/sys/rt_limits.h /usr/include/stdlib.h
fileio.o: main.h fileio.h /usr/include/stdio.h /usr/include/standards.h
fileio.o: /usr/include/sys/seek.h /usr/include/va_list.h
fileio.o: /usr/include/sys/types.h /usr/include/mach/machine/vm_types.h
fileio.o: /usr/include/sys/select.h /usr/include/getopt.h
fileio.o: /usr/include/sys/limits.h /usr/include/sys/machine/machlimits.h
fileio.o: /usr/include/sys/syslimits.h /usr/include/sys/machine/machtime.h
fileio.o: /usr/include/sys/rt_limits.h /usr/include/stdlib.h
filldatastrs.o: /usr/include/stdlib.h /usr/include/standards.h
filldatastrs.o: /usr/include/getopt.h /usr/include/sys/types.h
filldatastrs.o: /usr/include/mach/machine/vm_types.h
filldatastrs.o: /usr/include/sys/select.h /usr/include/stdio.h
filldatastrs.o: /usr/include/sys/seek.h /usr/include/va_list.h
filldatastrs.o: /usr/include/sys/limits.h
filldatastrs.o: /usr/include/sys/machine/machlimits.h
filldatastrs.o: /usr/include/sys/syslimits.h
filldatastrs.o: /usr/include/sys/machine/machtime.h
filldatastrs.o: /usr/include/sys/rt_limits.h main.h filldatastrs.h umacros.h
filldatastrs.o: llist.h /usr/include/string.h /usr/include/strings.h pprint.h
pprint.o: /usr/include/stdio.h /usr/include/standards.h
pprint.o: /usr/include/sys/seek.h /usr/include/va_list.h
pprint.o: /usr/include/sys/types.h /usr/include/mach/machine/vm_types.h
pprint.o: /usr/include/sys/select.h /usr/include/getopt.h
pprint.o: /usr/include/sys/limits.h /usr/include/sys/machine/machlimits.h
pprint.o: /usr/include/sys/syslimits.h /usr/include/sys/machine/machtime.h
pprint.o: /usr/include/sys/rt_limits.h main.h pprint.h
ranks.o: /usr/include/stdlib.h /usr/include/standards.h /usr/include/getopt.h
ranks.o: /usr/include/sys/types.h /usr/include/mach/machine/vm_types.h
ranks.o: /usr/include/sys/select.h main.h ranks.h choose.h show_choose.h
ranks.o: llist.h /usr/include/stdio.h /usr/include/sys/seek.h
ranks.o: /usr/include/va_list.h /usr/include/sys/limits.h
ranks.o: /usr/include/sys/machine/machlimits.h /usr/include/sys/syslimits.h
ranks.o: /usr/include/sys/machine/machtime.h /usr/include/sys/rt_limits.h
ranks.o: umacros.h
main.o: /usr/include/stdio.h /usr/include/standards.h /usr/include/sys/seek.h
main.o: /usr/include/va_list.h /usr/include/sys/types.h
main.o: /usr/include/mach/machine/vm_types.h /usr/include/sys/select.h
main.o: /usr/include/getopt.h /usr/include/sys/limits.h
main.o: /usr/include/sys/machine/machlimits.h /usr/include/sys/syslimits.h
main.o: /usr/include/sys/machine/machtime.h /usr/include/sys/rt_limits.h
main.o: /usr/include/time.h /usr/include/sys/timers.h
main.o: /usr/include/sys/sysmisc.h /usr/include/stdlib.h variables.h main.h
main.o: getsiminfo.h ranks.h filldatastrs.h fileio.h pprint.h fillcueorders.h
main.o: takethebest.h weightedlinear.h unitlinear.h weightedtally.h
main.o: unittally.h minimalist.h takethelast.h arrays.h regression.h
main.o: crossval.h simple_bayes.h
fillcueorders.o: /usr/include/stdio.h /usr/include/standards.h
fillcueorders.o: /usr/include/sys/seek.h /usr/include/va_list.h
fillcueorders.o: /usr/include/sys/types.h
fillcueorders.o: /usr/include/mach/machine/vm_types.h
fillcueorders.o: /usr/include/sys/select.h /usr/include/getopt.h
fillcueorders.o: /usr/include/sys/limits.h
fillcueorders.o: /usr/include/sys/machine/machlimits.h
fillcueorders.o: /usr/include/sys/syslimits.h
fillcueorders.o: /usr/include/sys/machine/machtime.h
fillcueorders.o: /usr/include/sys/rt_limits.h /usr/include/stdlib.h main.h
fillcueorders.o: llist.h umacros.h fillcueorders.h
getsiminfo.o: /usr/include/stdio.h /usr/include/standards.h
getsiminfo.o: /usr/include/sys/seek.h /usr/include/va_list.h
getsiminfo.o: /usr/include/sys/types.h /usr/include/mach/machine/vm_types.h
getsiminfo.o: /usr/include/sys/select.h /usr/include/getopt.h
getsiminfo.o: /usr/include/sys/limits.h /usr/include/sys/machine/machlimits.h
getsiminfo.o: /usr/include/sys/syslimits.h
getsiminfo.o: /usr/include/sys/machine/machtime.h
getsiminfo.o: /usr/include/sys/rt_limits.h /usr/include/string.h
getsiminfo.o: /usr/include/strings.h /usr/include/stdlib.h main.h
getsiminfo.o: getsiminfo.h variables.h
pmmutils.o: /usr/include/stdio.h /usr/include/standards.h
pmmutils.o: /usr/include/sys/seek.h /usr/include/va_list.h
pmmutils.o: /usr/include/sys/types.h /usr/include/mach/machine/vm_types.h
pmmutils.o: /usr/include/sys/select.h /usr/include/getopt.h
pmmutils.o: /usr/include/sys/limits.h /usr/include/sys/machine/machlimits.h
pmmutils.o: /usr/include/sys/syslimits.h /usr/include/sys/machine/machtime.h
pmmutils.o: /usr/include/sys/rt_limits.h /usr/include/stdlib.h main.h
pmmutils.o: pmmutils.h umacros.h pprint.h
linutils.o: /usr/include/stdio.h /usr/include/standards.h
linutils.o: /usr/include/sys/seek.h /usr/include/va_list.h
linutils.o: /usr/include/sys/types.h /usr/include/mach/machine/vm_types.h
linutils.o: /usr/include/sys/select.h /usr/include/getopt.h
linutils.o: /usr/include/sys/limits.h /usr/include/sys/machine/machlimits.h
linutils.o: /usr/include/sys/syslimits.h /usr/include/sys/machine/machtime.h
linutils.o: /usr/include/sys/rt_limits.h /usr/include/stdlib.h main.h
linutils.o: umacros.h linutils.h
takethebest.o: /usr/include/stdio.h /usr/include/standards.h
takethebest.o: /usr/include/sys/seek.h /usr/include/va_list.h
takethebest.o: /usr/include/sys/types.h /usr/include/mach/machine/vm_types.h
takethebest.o: /usr/include/sys/select.h /usr/include/getopt.h
takethebest.o: /usr/include/sys/limits.h
takethebest.o: /usr/include/sys/machine/machlimits.h
takethebest.o: /usr/include/sys/syslimits.h
takethebest.o: /usr/include/sys/machine/machtime.h
takethebest.o: /usr/include/sys/rt_limits.h main.h allalgutils.h pmmutils.h
takethebest.o: umacros.h takethebest.h
weightedlinear.o: /usr/include/stdio.h /usr/include/standards.h
weightedlinear.o: /usr/include/sys/seek.h /usr/include/va_list.h
weightedlinear.o: /usr/include/sys/types.h
weightedlinear.o: /usr/include/mach/machine/vm_types.h
weightedlinear.o: /usr/include/sys/select.h /usr/include/getopt.h
weightedlinear.o: /usr/include/sys/limits.h
weightedlinear.o: /usr/include/sys/machine/machlimits.h
weightedlinear.o: /usr/include/sys/syslimits.h
weightedlinear.o: /usr/include/sys/machine/machtime.h
weightedlinear.o: /usr/include/sys/rt_limits.h /usr/include/stdlib.h main.h
weightedlinear.o: umacros.h allalgutils.h linutils.h weightedlinear.h
unitlinear.o: /usr/include/stdio.h /usr/include/standards.h
unitlinear.o: /usr/include/sys/seek.h /usr/include/va_list.h
unitlinear.o: /usr/include/sys/types.h /usr/include/mach/machine/vm_types.h
unitlinear.o: /usr/include/sys/select.h /usr/include/getopt.h
unitlinear.o: /usr/include/sys/limits.h /usr/include/sys/machine/machlimits.h
unitlinear.o: /usr/include/sys/syslimits.h
unitlinear.o: /usr/include/sys/machine/machtime.h
unitlinear.o: /usr/include/sys/rt_limits.h /usr/include/stdlib.h main.h
unitlinear.o: umacros.h allalgutils.h linutils.h unitlinear.h
weightedtally.o: /usr/include/stdio.h /usr/include/standards.h
weightedtally.o: /usr/include/sys/seek.h /usr/include/va_list.h
weightedtally.o: /usr/include/sys/types.h
weightedtally.o: /usr/include/mach/machine/vm_types.h
weightedtally.o: /usr/include/sys/select.h /usr/include/getopt.h
weightedtally.o: /usr/include/sys/limits.h
weightedtally.o: /usr/include/sys/machine/machlimits.h
weightedtally.o: /usr/include/sys/syslimits.h
weightedtally.o: /usr/include/sys/machine/machtime.h
weightedtally.o: /usr/include/sys/rt_limits.h /usr/include/stdlib.h main.h
weightedtally.o: umacros.h allalgutils.h linutils.h weightedtally.h
unittally.o: /usr/include/stdio.h /usr/include/standards.h
unittally.o: /usr/include/sys/seek.h /usr/include/va_list.h
unittally.o: /usr/include/sys/types.h /usr/include/mach/machine/vm_types.h
unittally.o: /usr/include/sys/select.h /usr/include/getopt.h
unittally.o: /usr/include/sys/limits.h /usr/include/sys/machine/machlimits.h
unittally.o: /usr/include/sys/syslimits.h /usr/include/sys/machine/machtime.h
unittally.o: /usr/include/sys/rt_limits.h /usr/include/stdlib.h main.h
unittally.o: umacros.h allalgutils.h linutils.h unittally.h
minimalist.o: /usr/include/stdio.h /usr/include/standards.h
minimalist.o: /usr/include/sys/seek.h /usr/include/va_list.h
minimalist.o: /usr/include/sys/types.h /usr/include/mach/machine/vm_types.h
minimalist.o: /usr/include/sys/select.h /usr/include/getopt.h
minimalist.o: /usr/include/sys/limits.h /usr/include/sys/machine/machlimits.h
minimalist.o: /usr/include/sys/syslimits.h
minimalist.o: /usr/include/sys/machine/machtime.h
minimalist.o: /usr/include/sys/rt_limits.h main.h allalgutils.h pmmutils.h
minimalist.o: umacros.h fillcueorders.h pprint.h minimalist.h
takethelast.o: /usr/include/stdio.h /usr/include/standards.h
takethelast.o: /usr/include/sys/seek.h /usr/include/va_list.h
takethelast.o: /usr/include/sys/types.h /usr/include/mach/machine/vm_types.h
takethelast.o: /usr/include/sys/select.h /usr/include/getopt.h
takethelast.o: /usr/include/sys/limits.h
takethelast.o: /usr/include/sys/machine/machlimits.h
takethelast.o: /usr/include/sys/syslimits.h
takethelast.o: /usr/include/sys/machine/machtime.h
takethelast.o: /usr/include/sys/rt_limits.h main.h allalgutils.h pmmutils.h
takethelast.o: takethelast.h fillcueorders.h
allalgutils.o: /usr/include/stdio.h /usr/include/standards.h
allalgutils.o: /usr/include/sys/seek.h /usr/include/va_list.h
allalgutils.o: /usr/include/sys/types.h /usr/include/mach/machine/vm_types.h
allalgutils.o: /usr/include/sys/select.h /usr/include/getopt.h
allalgutils.o: /usr/include/sys/limits.h
allalgutils.o: /usr/include/sys/machine/machlimits.h
allalgutils.o: /usr/include/sys/syslimits.h
allalgutils.o: /usr/include/sys/machine/machtime.h
allalgutils.o: /usr/include/sys/rt_limits.h /usr/include/stdlib.h main.h
allalgutils.o: allalgutils.h umacros.h
crossval.o: /usr/include/stdlib.h /usr/include/standards.h
crossval.o: /usr/include/getopt.h /usr/include/sys/types.h
crossval.o: /usr/include/mach/machine/vm_types.h /usr/include/sys/select.h
crossval.o: /usr/include/stdio.h /usr/include/sys/seek.h
crossval.o: /usr/include/va_list.h /usr/include/sys/limits.h
crossval.o: /usr/include/sys/machine/machlimits.h
crossval.o: /usr/include/sys/syslimits.h /usr/include/sys/machine/machtime.h
crossval.o: /usr/include/sys/rt_limits.h main.h crossval.h llist.h umacros.h
crossval.o: pprint.h
regression.o: /usr/include/stdlib.h /usr/include/standards.h
regression.o: /usr/include/getopt.h /usr/include/sys/types.h
regression.o: /usr/include/mach/machine/vm_types.h /usr/include/sys/select.h
regression.o: /usr/include/stdio.h /usr/include/sys/seek.h
regression.o: /usr/include/va_list.h /usr/include/sys/limits.h
regression.o: /usr/include/sys/machine/machlimits.h
regression.o: /usr/include/sys/syslimits.h
regression.o: /usr/include/sys/machine/machtime.h
regression.o: /usr/include/sys/rt_limits.h main.h umacros.h
regression.o: /usr/include/math.h stats.h pprint.h mlreg.h arrays.h global.h
regression.o: regression.h llist.h
mlreg.o: /usr/include/stdlib.h /usr/include/standards.h /usr/include/getopt.h
mlreg.o: /usr/include/sys/types.h /usr/include/mach/machine/vm_types.h
mlreg.o: /usr/include/sys/select.h /usr/include/stdio.h
mlreg.o: /usr/include/sys/seek.h /usr/include/va_list.h
mlreg.o: /usr/include/sys/limits.h /usr/include/sys/machine/machlimits.h
mlreg.o: /usr/include/sys/syslimits.h /usr/include/sys/machine/machtime.h
mlreg.o: /usr/include/sys/rt_limits.h /usr/include/math.h global.h mlreg.h
mlreg.o: arrays.h statlib.h main.h
statlib.o: /usr/include/math.h /usr/include/standards.h /usr/include/stdlib.h
statlib.o: /usr/include/getopt.h /usr/include/sys/types.h
statlib.o: /usr/include/mach/machine/vm_types.h /usr/include/sys/select.h
statlib.o: statlib.h global.h
arrays.o: arrays.h /usr/include/stdio.h /usr/include/standards.h
arrays.o: /usr/include/sys/seek.h /usr/include/va_list.h
arrays.o: /usr/include/sys/types.h /usr/include/mach/machine/vm_types.h
arrays.o: /usr/include/sys/select.h /usr/include/getopt.h
arrays.o: /usr/include/sys/limits.h /usr/include/sys/machine/machlimits.h
arrays.o: /usr/include/sys/syslimits.h /usr/include/sys/machine/machtime.h
arrays.o: /usr/include/sys/rt_limits.h /usr/include/stdlib.h
stats.o: /usr/include/stdio.h /usr/include/standards.h
stats.o: /usr/include/sys/seek.h /usr/include/va_list.h
stats.o: /usr/include/sys/types.h /usr/include/mach/machine/vm_types.h
stats.o: /usr/include/sys/select.h /usr/include/getopt.h
stats.o: /usr/include/sys/limits.h /usr/include/sys/machine/machlimits.h
stats.o: /usr/include/sys/syslimits.h /usr/include/sys/machine/machtime.h
stats.o: /usr/include/sys/rt_limits.h /usr/include/math.h
stats.o: /usr/include/stdlib.h main.h stats.h
simple_bayes.o: /usr/include/stdio.h /usr/include/standards.h
simple_bayes.o: /usr/include/sys/seek.h /usr/include/va_list.h
simple_bayes.o: /usr/include/sys/types.h /usr/include/mach/machine/vm_types.h
simple_bayes.o: /usr/include/sys/select.h /usr/include/getopt.h
simple_bayes.o: /usr/include/sys/limits.h
simple_bayes.o: /usr/include/sys/machine/machlimits.h
simple_bayes.o: /usr/include/sys/syslimits.h
simple_bayes.o: /usr/include/sys/machine/machtime.h
simple_bayes.o: /usr/include/sys/rt_limits.h /usr/include/stdlib.h main.h
simple_bayes.o: allalgutils.h pmmutils.h umacros.h simple_bayes.h
llist.o: /usr/include/stdio.h /usr/include/standards.h
llist.o: /usr/include/sys/seek.h /usr/include/va_list.h
llist.o: /usr/include/sys/types.h /usr/include/mach/machine/vm_types.h
llist.o: /usr/include/sys/select.h /usr/include/getopt.h
llist.o: /usr/include/sys/limits.h /usr/include/sys/machine/machlimits.h
llist.o: /usr/include/sys/syslimits.h /usr/include/sys/machine/machtime.h
llist.o: /usr/include/sys/rt_limits.h /usr/include/stdlib.h umacros.h
mlreg.o: arrays.h
