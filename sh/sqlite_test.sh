#!/bin/bash

sqlite_cmd=sqlite3
dbfile=/tmp/testdb

queries=(
 "select idx, uri, val from testtbl order by idx;"
 "select idx, uri, val from testtbl order by idx;"
)

query=$(for line in "${queries[@]}"; do echo "$line"; done)

$sqlite_cmd $dbfile <<< "${query}" | while IFS="|" read idx uri val
do
  echo d: $idx, $uri, $val
done

s='\
select "idx", uri, val from testtbl order by idx;
select idx, uri, val from testtbl order by idx;
'

echo "d${s}d"