# Prototype user .login file
#
# $Id: .login,v 1.16 1991/08/21 19:08:30 jik Exp $

# This file sources a system-wide .login file, which:
#      - presumes that the .cshrc file has been sourced
#      - performs standard setups appropriate for tty session
#      - runs standard startup activities (e.g., check mail)
#      - source user file ~/.startup.tty, if it exists

if (-e /usr/athena/lib/init) then
	set initdir=/usr/athena/lib/init
else
	set initdir=/usr/lib/init
endif

if (-r $initdir/login) then
        source $initdir/login
else
	echo "Warning: System-wide initialization files not found."
       	echo "Login initialization has not been performed."
endif


# If you want to ADJUST the login initialization sequence, create a
# .startup.tty file in your home directory, with commands to run activities
# once the environment has been set up (znol, emacs, etc.).

# To adjust the environment initialization sequence, see the instructions in
# the .cshrc file.

# If you want to CHANGE the login initialization sequence, revise this .login
# file (the one you're reading now).  You may want to copy the contents of
# the system-wide login file as a starting point.
#
# WARNING: If you revise this .login file, you will not automatically
# get any changes that Project Athena may make to the system-wide file at 
# a later date.  Be sure you know what you are doing.
