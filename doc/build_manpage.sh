#!/bin/bash
echo -n "-- Rendering manpage "
(pandoc manpage.md -s -t man > ./manpage && echo "done")|| echo "failed"
if [ "$1" != "quiet" ]
then
	echo "Displaying rendered manpage..."
	man ./manpage
fi
