# Copyright (C) 2006 International Business Machines and others.
# All Rights Reserved.
# This file is distributed under the Eclipse Public License.
#
# Author:  Andreas Waechter           IBM    2006-04-13

SUBDIRS = Ipopt
if COIN_HAS_ASL
  SUBDIRS += Ampl
endif
if COIN_HAS_FILTERSQP
  SUBDIRS += Filter
endif

########################################################################
#                          libipoptinterface                           #
########################################################################

# Name of the library in this directory
noinst_LTLIBRARIES = libbonmininterfaces.la 

# List all source files, including headers
libbonmininterfaces_la_SOURCES = \
	BonAuxInfos.cpp \
	BonBoundsReader.cpp \
	BonColReader.cpp \
	BonCutStrengthener.cpp \
	BonStartPointReader.cpp \
	BonOsiTMINLPInterface.cpp \
	BonTMINLP2TNLP.cpp \
	BonTMINLP2OsiLP.cpp \
	BonTMINLP.cpp \
	BonTNLPSolver.cpp \
	BonTNLP2FPNLP.cpp \
	BonBranchingTQP.cpp \
	BonStrongBranchingSolver.cpp \
	BonRegisteredOptions.cpp
#BonStdCInterface.cpp
#BonStdInterfaceTMINLP.cpp

#sublibraries for various installed solvers
libbonmininterfaces_la_LIBADD = Ipopt/libipoptinterface.la 

if COIN_HAS_FILTERSQP
  libbonmininterfaces_la_LIBADD += Filter/libfilterinterface.la
endif

# Here list all include flags, relative to this "srcdir" directory.
AM_CPPFLAGS = \
	-I$(srcdir)/../Algorithms \
	-I$(srcdir)/../Algorithms/OaGenerators \
	-I$(srcdir)/../Algorithms/Branching \
	-I$(srcdir)/../CbcBonmin \
	$(BONMINLIB_CFLAGS)

########################################################################
#                Headers that need to be installed                     #
########################################################################

# Here list all the header files that are required by a user of the library,
# and that therefore should be installed in 'include/coin-or'
includecoindir = $(includedir)/coin-or
includecoin_HEADERS = \
     BonOsiTMINLPInterface.hpp \
     BonTMINLP2TNLP.hpp \
     BonAuxInfos.hpp \
     BonTMINLP.hpp \
     BonTNLP2FPNLP.hpp \
     BonCutStrengthener.hpp \
     BonTNLPSolver.hpp \
     BonBranchingTQP.hpp \
     BonStrongBranchingSolver.hpp \
     BonTMINLP2OsiLP.hpp \
     BonTypes.hpp \
     BonRegisteredOptions.hpp \
     BonExitCodes.hpp
# BonStdCInterface.h

install-exec-local:
	$(install_sh_DATA) config_bonmin.h $(DESTDIR)$(includecoindir)/BonminConfig.h

uninstall-local:
	rm -f $(DESTDIR)$(includecoindir)/BonminConfig.h

########################################################################
#                            Astyle stuff                              #
########################################################################

# Here repeat all source files, with "bak" appended
ASTYLE_FILES = \
	BonAuxInfos.cppbak \
	BonAuxInfos.hppbak \
	BonBoundsReader.cppbak \
	BonBoundsReader.hppbak \
	BonBranchingTQP.cppbak \
	BonBranchingTQP.hppbak \
	BonColReader.cppbak \
	BonColReader.hppbak \
	BonCurvatureEstimator.cppbak \
	BonCurvatureEstimator.hppbak \
	BonCutStrengthener.cppbak \
	BonCutStrengthener.hppbak \
	BonExitCodes.hppbak \
	BonOsiTMINLPInterface.cppbak \
	BonOsiTMINLPInterface.hppbak \
	BonRegisteredOptions.cppbak \
	BonRegisteredOptions.hppbak \
	BonStartPointReader.cppbak \
	BonStartPointReader.hppbak \
	BonStrongBranchingSolver.cppbak \
	BonStrongBranchingSolver.hppbak \
	BonTMINLP2TNLP.cppbak \
	BonTMINLP2TNLP.hppbak \
	BonTMINLP.cppbak \
	BonTMINLP.hppbak \
	BonTNLP2FPNLP.cppbak \
	BonTNLP2FPNLP.hppbak \
	BonTNLPSolver.cppbak \
	BonTNLPSolver.hppbak \
	BonTypes.hppbak

#BonStdCInterface.cppbak
#BonStdInterfaceTMINLP.cppbak
#BonStdInterfaceTMINLP.hppbak

ASTYLE = @ASTYLE@
ASTYLEFLAGS = @ASTYLEFLAGS@

CLEANFILES = $(ASTYLE_FILES)

SUFFIXES = .cppbak .hppbak

astyle: $(ASTYLE_FILES)

.hpp.hppbak:
	mv $< $@
	$(ASTYLE) $(ASTYLEFLAGS) < $@ > $<
	touch $@

.cpp.cppbak:
	mv $< $@
	$(ASTYLE) $(ASTYLEFLAGS) < $@ > $<
	touch $@
