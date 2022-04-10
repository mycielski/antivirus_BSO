#!/bin/bash
echo -n "-- Rendering manpage "
(pandoc manpage.md -s -t man > ./manpage && echo "done")|| echo "failed"
